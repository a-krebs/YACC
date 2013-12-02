#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Definitions.h"
#include "ElementArray.h"
#include "Error.h"
#include "Globals.h"
#include "Hash.h"
#include "Emit.h"
#include "PreDef.h"
#include "Type.h"
#include "SymbolAll.h"
#include "Utils.h"
#include "ActionsAll.h"

#ifndef TESTBUILD
#include "parser.tab.h"	/* token definitions used in operator compat checks */
#endif
#ifdef TESTBUILD
#include "tokens.h"
#endif

/*For error reporting:*/
extern int yylineno;
extern int colno;
static char *errMsg;


/*
 * Perform actions necessary once all declarations are finished.
 */
void exitDeclPart(void) {
	emitBlankLine();
	emitComment("Start of program, functions, or procedure:");
	emitLabel(STMT_LEN, "%s_%d",
	    USER_PROG_START_LABEL, peekLabelStackTop(mainLabelStack));

	/* done with label, so pop */
	popLabels(mainLabelStack);
}


/*
 * Capture program header definitions of input and output arguments.
 *
 * Arguments may be null if program contains errors.
 */
void doProgramDecl(char *prog_name, char *in_name, char *out_name) {
	incrementLexLevel(symbolTable);
}


/*
 * Perform actions necessary when exiting const decl part.
 */
void exitConstDeclPart(void) {
	// function does nothing.
}


/*
 * Create a new constant in the symbol table.
 * Extract the value and type information from the proxy.
 */
void doConstDecl(char *id, ProxySymbol *proxy) {
	Symbol *s = NULL;
	int lvl = getCurrentLexLevel(symbolTable);

	/* Perform lookup for identifier in current lexical level */
	s = getLocalSymbol(symbolTable, id);
	if (s) {
		alreadyDefinedError(id);
		return;
	}

	/* Else we can try to make new const  and add it to symbol table */	
	s = newConstSymFromProxy(lvl, id, proxy);		
	if (s) {
		addToSymbolTable(symbolTable, s);
		/* Consts have a value and thus need an offset, so we set it */
		setSymbolOffset(s, symbolTable);
		emitConstDecl(s);
	}
}


/*
 * Perform actions necessary when exiting type decl part.
 */
void exitTypeDeclPart(void) {
	// probably nothing to do here
}


/*
 * Create a new type identifier symbol in the symbol table.
 *
 * Parameters:
 * 	id: name of symbol
 * 	type: Symbol with TYPE_KIND from which to copy the type
 *
 * Does not return
 */
void doTypeDecl(char *id, Symbol *type) {
	Symbol * s = NULL;

	/* check that type with id is not already defined in scope */
	s = getLocalSymbol(symbolTable, id);
	if (s != NULL) {
		errMsg = customErrorString("The identifier %s is already "
		  "defined at this scope.", id);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		/* Assume first type decl is the one to use.
		 * See documentation PDF for details. */
		return;
	}
	
	// TODO this is a create and an insert. Maybe push the insert into
	// newTypeSymFromSym
	s = newTypeSymFromSym(id, type);
	if (s == NULL) {
		/* newTypeSymFromSym has already reported errors or
		 * exited when appropriate */
		return;
	}
		
	if (addToSymbolTable(symbolTable, s) != 0) {
		err(EXIT_FAILURE, "Could not insert symbol into symbol table");
	}
}


/*
 * Perform actions necessary when exiting variable dec section.
 */
void exitVarDeclPart(void) {
	/* reserve label for the next main */
	reserveLabels(mainLabelStack, 1);

	emitBlankLine();
	if (inMainDecls != 0) {
		emitComment("End of main var decls, call MAIN");
		emitStmt(STMT_LEN, "CALL 1, %s_%d",
		    USER_PROG_START_LABEL, peekLabelStackTop(mainLabelStack));
		/* clear flag */
		inMainDecls = 0;
	} else {
		emitComment("End of var decls, jump over any other proc or "
		    "func decls");
		emitStmt(STMT_LEN, "GOTO %s_%d",
		    USER_PROG_START_LABEL, peekLabelStackTop(mainLabelStack));
	}

	emitBlankLine();
}


/*
 * Declare a new variable with the given type.
 *
 * Return a pointer to type.
 */
Symbol *doVarDecl(char *id, Symbol *type) {
	Symbol *s = NULL;
	s = getLocalSymbol(symbolTable, id);
	if (s) {
		alreadyDefinedError(id);
		return NULL;
	}

	if ((!id) || !(type)) return NULL;

	s = newVariableSym(id, type);
	if (s) {
		addToSymbolTable(symbolTable, s);
		
		/* Set the variables offset */
		setSymbolOffset(s, symbolTable);
		emitVarDecl(s);

		/* If var is being declared to be a record type, then we know that
		 * it is the record head and set the appropriate flag */
		if (getType(type) == RECORD_T) s->isRecordHead = 1;
	}

	return type;
}


/*
 * Exit a procedure or function definition.
 *
 * This is a good time to pop lexical level.
 */
void exitProcOrFuncDecl(Symbol *symbol) {
#if DEBUG
	printf("Popping lex level at line %d, from %d to %d\n", yylineno,
	    getCurrentLexLevel(symbolTable), getCurrentLexLevel(symbolTable)-1);
#endif

	if (symbol != NULL) {
		if (symbol->kind == PROC_KIND) {	
		 	emitEndProc(symbol);
		}
		else if (symbol->kind == FUNC_KIND)  {
		 	emitEndFunc(symbol);
		}
	}

	popLexLevel(symbolTable);
}


/*
 * Declare a new procedure with given arguments and perform anything
 * necessary when entering the procedure body definition (like increasing
 * the lexical level).
 *
 * Both arguments can be NULL if the definition contains errors.
 *
 * Parameters:	
 *		id: name of procedure
 *		ea: element array of parameters to procedure
 *
 * Return a pointer to the procedure symbol.
 */
Symbol *enterProcDecl(char *id, struct ElementArray *ea) {
	Symbol *s = NULL;
	Symbol *var = NULL;
	
	if (!id) {
		/*Increament lex level to true to continue normally*/
		incrementLexLevel(symbolTable);
		return NULL;
	}

	s = getLocalSymbol(symbolTable, id);
	if (s) {
		errMsg = customErrorString("Name %s "
		    "is already defined.",id);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		
		/*Increament lex level to true to continue normally*/
		incrementLexLevel(symbolTable);

		return NULL;
	}

	if (!ea) {
		ea = newElementArray();
	}

	/*Make sure parameters in declaration do not have same names.*/
	if (hasDuplicateElement(ea)) {
		errMsg = customErrorString("Procedure %s has duplicate "
		   "argument names.", id);
		recordError(errMsg, yylineno, colno, SEMANTIC);
	}

	/*Create a symbol for the procedure in the symbolTable*/
	s = newProcSym(id, ea);	
	if (addToSymbolTable(symbolTable, s) != 0) {
		err(1, "Could not add element to symbol table.");
		exit(EXIT_FAILURE);
	}

	/*Increment lexical level for all the parameters*/
	incrementLexLevel(symbolTable);
	
	/* Push params as local variables on new lexical level */
	/* Note that this is for semantic analysis only, params will be vars
	 * without offsets since their offsets are implicit in the call frame */
	for (int i = 0; i < ea->nElements; i++) {
		/*Create variable symbol from parameter*/
		var = paramToVar(getElementAt(ea, i));

		if (!getLocalSymbol(symbolTable, var->name)) {
			addToSymbolTable(symbolTable, var);
			setParamOffset(var, ea);
		}
		else {
			errMsg = customErrorString("Name %s "
		    		"is already defined.",id);
			recordError(errMsg, yylineno, colno, SEMANTIC);
		}	
	}

	emitProcOrFuncDecl(s, ea);

	return s;
}


/*
 * Declare a new function with the given arguments and perform anything
 * necessary when entering the function body definition.
 *
 * Both arguments can be NULL if the definition contains errors.
 * 
 * Return a pointer to the procedure.
 */
Symbol *enterFuncDecl(char *id, struct ElementArray *ea, Symbol *typeSym) {
	Symbol *s = NULL, *var = NULL;
	int lvl = getCurrentLexLevel(symbolTable), i;

	s = getLocalSymbol(symbolTable, id);
	if (s) {
		errMsg = customErrorString("Function with name %s "
		    "is already defined.",id);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}

	if (!ea) {
		ea = newElementArray();
	}

	if (!typeSym) {
		errMsg = customErrorString("Function with name %s "
		    "has no return type, assuming INTEGER.",id);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		typeSym = getPreDefInt(preDefTypeSymbols);
	}

	if (hasDuplicateElement(ea)) {
		errMsg = customErrorString("Procedure %s has duplicate "
		   "argument names.", id);
		recordError(errMsg, yylineno, colno, SEMANTIC);
	}

	s = newFuncSym(lvl, id, typeSym, ea);
	if (addToSymbolTable(symbolTable, s) != 0) {
		// TODO error
	}
	incrementLexLevel(symbolTable);
	/* Push params as local variables on new lexical level */
	/* Note that this is for semantic analysis only, params will be vars
	 * without offsets since their offsets are implicit in the call frame */
	for (i = 0; i < ea->nElements; i++) {
		var = paramToVar(getElementAt(ea, i));
		if (!getLocalSymbol(symbolTable, var->name)) {
			// TODO error checking
			addToSymbolTable(symbolTable, var);
			setParamOffset(var, ea);
		}		
	}

	emitProcOrFuncDecl(s, ea);

	return s;
}


/*
 * Create a new parameter list from the given parameter.
 *
 * Return a pointer to the parameter list.
 */
struct ElementArray *createParmList(Symbol *parm) {
	struct ElementArray *ea = NULL;
	if (!parm) return NULL;

	ea = newElementArray();
	growElementArray(ea);
	appendElement(ea, parm);
	return ea;	
}


/*
 * Append the given parameter to the parameter list.
 *
 * Return a poinnter to the parameter list.
 */
struct ElementArray *appendParmToParmList(
    struct ElementArray *ea, Symbol *parm) {

	// TODO: see if parm already exists in element array
	if ( !(ea) || !(parm) ) return NULL;
	appendElement(ea, parm);	
	return ea;
}


/*
 * Create a new parameter with the given name and type.
 *
 * Return a pointer to the new parameter.
 */
Symbol *createNewParm(char *id, Symbol *type) {
	if ((!id) || (!type)) return NULL;
	return newParamSym(id, type);
}


/*
 * Create a new var parm with the given name and type.
 *
 * Return a pointer to the new parameter.
 */
Symbol *createNewVarParm(char *id, Symbol *type) {
	Symbol *s = createNewParm(id, type);
	if (s) s->kindPtr.ParamKind->byRef = 1;
	return s;
}
