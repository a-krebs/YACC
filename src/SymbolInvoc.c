#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ActionsExprs.h"
#include "ElementArray.h"
#include "Error.h"
#include "ErrorLL.h"
#include "Tree.h"
#include "Type.h"
#include "Hash.h"
#include "Kind.h"
#include "PreDef.h"
#include "SymbolAll.h"


/*For error reporting*/
extern int yylineno;
extern int colno;
static char *errMsg;
struct Error *e;


/*
 * Return 1 if valid invocation, 0 otherwise.
 */
int isValidProcInvocation(Symbol *s, struct ElementArray *ea)
{
	struct ElementArray *params = NULL;
	Symbol *passedParam, *expectedParam = NULL;
	int i;

	// make sure we're given a proc and not a func or any other symbol
	if (s->kind != PROC_KIND) {
		errMsg = customErrorString("Identifier %s cannot be called "
		    "as a procedure.", s->name);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}

	params = s->kindPtr.ProcKind->params;
	if (!params) {
		// special built-in proc that takes unlimited args
		// TODO for now just assuming all arguments are valid
		return 1;
	} else if (params->nElements != ea->nElements) {
		errMsg = customErrorString("Procedure %s expects %d "
		    "parameters, got %d", s->name, params->nElements,
		    ea->nElements);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;	
	}

	for (i = 0; (i < params->nElements) && (i < ea->nElements); i++) {
		passedParam = ((struct treeNode *)getElementAt(ea, i))->symbol;
		expectedParam = (Symbol *) getElementAt(params, i);
		if (!isAssignmentCompat(expectedParam, passedParam)) {
			errMsg = customErrorString("Procedure %s expects "
			    "argument of type %s at index %d, but got "
			    "argument of type %s", s->name,
			    typeToString(getType(expectedParam)), i,
			    typeToString(getType(passedParam)));
			e = recordError(errMsg, yylineno, colno,
			     SEMANTIC);
			return 0;
		}
	}
	return 1;
}


Symbol *
isValidFuncInvocation(Symbol *s, struct ElementArray *ea)
{
	struct ElementArray *params = NULL;
	Symbol *passedParam, *expectedParam = NULL;
	int i;

	// make sure we're given a func and not a proc
	if (s->kind != FUNC_KIND) {
		errMsg = customErrorString("Identifier %s cannot be "
 			"called as a function.", s->name);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}

	params = s->kindPtr.FuncKind->params;
	if (!params) {
		// special case of predefined-function
		// TODO check what types are acceptable,
		// for now assuming all types
		return getTypeSym(s);
	} else if (params->nElements != ea->nElements) {
		errMsg = customErrorString("Procedure %s expects %d "
		    "parameters, got %d", s->name, params->nElements,
		    ea->nElements);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;	
	}

	// TODO: should'nt call to is areSameType below be a call to
	// are assignment compatible? 
	for (i = 0; i < params->nElements; i++) {
		passedParam = ((struct treeNode *)getElementAt(ea, i))->symbol;
		expectedParam = (Symbol *) getElementAt(params, i);
		if (!isAssignmentCompat(expectedParam,passedParam)) {
			errMsg = customErrorString("Procedure %s expects "
			    "argument of type %s at index %d, but got "
			    "argument of type %s", s->name,
			    typeToString(getType(expectedParam)),i,
			    typeToString(getType(passedParam)));
			e = recordError(errMsg, yylineno, colno, SEMANTIC);
			return NULL;
		}
	}
	return getTypeSym(s);
}


int
isIOProc(Symbol *s) {
	if (!s) return 0;
	if (s->kind != PROC_KIND) return 0;

	if (  (	(strcmp(s->name, "read") == 0)	 	||
	    	(strcmp(s->name, "readln") == 0) 	||
	    	(strcmp(s->name, "write") == 0) 	||
	    	(strcmp(s->name, "writeln") == 0) )	&&
		(s->lvl == 0) ) {
		return 1;
	}
	return 0;

}


int isPreDefFunc(Symbol *s) {
	char *name = NULL;

	if (!s) return 0;
	if (s->kind != FUNC_KIND) return 0;

	name = s->name;

	if ( (	(strcmp(name, ABS) == 0) ||
		(strcmp(name, SQR) == 0) ||
		(strcmp(name, SIN) == 0) ||
		(strcmp(name, EXP) == 0) ||
		(strcmp(name, LN) == 0) ||
		(strcmp(name, SQRT) == 0) ||
		(strcmp(name, TRUNC) == 0) ||
		(strcmp(name, ROUND) == 0) ||
		(strcmp(name, CHR) == 0) ||
		(strcmp(name, ODD) == 0) ||
		(strcmp(name, ORD) == 0) ||
		(strcmp(name, SUCC) == 0) ||
		(strcmp(name, PRED) == 0) ) &&
			s->lvl == 0) {
	   	return 1;
	}
	return 0;
}


int
isValidIOProcInvocation(Symbol *s, struct ElementArray *ea)
{
	Symbol *param = NULL;
	type_t type;
	int i, nArgs, valid = 1;

	nArgs = ea->nElements;

	// TODO use is isElementArraySimple() to do type checking?
	for (i = 0; i < nArgs; i++) {
		param = ((struct treeNode *)getElementAt(ea, i))->symbol;
		type = getType(param);
		
		if (!isArgTypeValidInIOFunc(s, param)) {
			errMsg = customErrorString("Invalid argument "
			    "of type %s passed to procedure %s.",
			    typeToString(type), s->name);
			recordError(errMsg, yylineno, colno, SEMANTIC);
			valid = 0;
		}
	}
	if (!valid) return 0;
	return 1;
}

/* ea is an array of nodes now */
ProxySymbol *isValidPreDefFuncInvocation(Symbol *s, struct ElementArray *ea)
{
	Symbol *param = NULL;
	Symbol * type;
	int i = 0;
	int nArgs = 0;

	nArgs = ea->nElements;

	// check argument count
	if (nArgs != 1) {
		errMsg = customErrorString("Function %s expected "
		    "1 argument but %d given.", s->name, nArgs);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}
	
	param = ((struct treeNode *)getElementAt(ea, i))->symbol;
	type = getTypeSym(param);
	
	if (isArgTypeValidInPreDefFunc(s, param)) {
		return getPreDefFuncReturnType(s, type);
			
	} else {
		errMsg = customErrorString("Function %s cannot be "
		    "called with argument of type %s.", s->name,
		    typeToString(getType(type)));
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}
}


Symbol *getPreDefFuncReturnType(Symbol *s, Symbol *argTypeSym) {
	char *name = NULL;
	
	if (!s) return NULL;

	name = s->name;

	if (
	    (strcmp(name, ABS) == 0) ||
	    (strcmp(name, SQR) == 0) ||
	    (strcmp(name, SUCC) == 0) ||
	    (strcmp(name, PRED) == 0)
	) {
		return argTypeSym;
	} else if (
	    (strcmp(name, SIN) == 0) ||
	    (strcmp(name, EXP) == 0) ||
	    (strcmp(name, LN) == 0) ||
	    (strcmp(name, SQRT) == 0)
	) {
		return getPreDefReal(preDefTypeSymbols);
	} else if (
	    (strcmp(name, TRUNC) == 0) ||
	    (strcmp(name, ROUND) == 0) ||
	    (strcmp(name, ORD) == 0)
	){
		return getPreDefInt(preDefTypeSymbols);
	} else if (
	    (strcmp(name, CHR) == 0)
	){
		return getPreDefChar(preDefTypeSymbols);
	} else if (
	    (strcmp(name, ODD) == 0)
	){
		return getPreDefBool(preDefTypeSymbols);
	}
	return NULL;
}


Symbol *
paramToVar(Symbol *param)
{
	Symbol *s = NULL;
	if (!param) return NULL;
	Symbol *typeSym = getTypeSym(param);
	s = newVariableSym(param->name, typeSym);
	if (!s) return NULL;
	if (isByReference(param)) s->kindPtr.VarKind->byRef = 1;
	return s;
}


/* Checks each memeber of the passed ElementArray to see if each
 * memeber is of simple type.
 *
 * Parameters:
 *              elementArray: elementArray passed
 *
 * Return: Boolean: 1 if elemetn array is simple
 *		    0 if not
 */
int isElementArraySimple(struct ElementArray *elementArray) {
	struct Symbol *symbol;
	type_t symbolsType;

	for (int i = 0; i < elementArray->nElements; ++i) {
		symbol = (struct Symbol *) getElementAt(elementArray, i);

		if ( symbol->kind != TYPE_KIND ) {
			return 0;
		}

		symbolsType = getType(symbol);

		if ( symbolsType != BOOLEAN_T
			&& symbolsType != CHAR_T
			&& symbolsType != INTEGER_T
			&& symbolsType != REAL_T
			&& symbolsType != STRING_T ) {
			return 0;
		}
	}

	return 1;
}
int isArgTypeValidInIOFunc(Symbol *s, Symbol *arg) {
	char *name = NULL;
	type_t type;
	type_t arrayBaseType;
	kind_t kind;
	if(!s || !arg) return 0;
	
	name = s->name;
	type = getType(arg);
	kind = arg->kind;
	
	if (type == ARRAY_T) {
			arrayBaseType = getType(getArrayBaseSym(arg));
			if (arrayBaseType == CHAR_T) {
				type = arrayBaseType;
			}
	}
		
	if ((strcmp(name, "read") == 0) ||
		(strcmp(name, "readln") == 0)
	) {
		if (kind == TYPE_KIND) { 
			if (!(arg->isAddress)) {
				return 0;
			}
		} else if (kind == CONST_KIND) {
				return 0;
		} else if ((type != CHAR_T) && (type != INTEGER_T) &&
					(type != REAL_T) && (type != STRING_T) )
		     {
			return 0;
		}
			
	} else if ((strcmp(name, "writeln") == 0) ||
	           (strcmp(name, "write") == 0 )
	) {
		if( (type != CHAR_T) && (type != INTEGER_T) &&
		    (type != REAL_T) && (type != STRING_T) ) {
			return 0;
		}
	}
	
	return 1;
	
}

int isArgTypeValidInPreDefFunc(Symbol *s, Symbol *arg) {
	char *name = NULL;
	type_t type;
	if (!s || !arg) return 0;
	name = s->name;
	type = getType(arg);

	if (
	    (strcmp(name, ABS) == 0) ||
	    (strcmp(name, SQR) == 0) ||
	    (strcmp(name, SIN) == 0) ||
	    (strcmp(name, EXP) == 0) ||
	    (strcmp(name, LN) == 0) ||
	    (strcmp(name, SQRT) == 0)
	) {
		if ((type == INTEGER_T) || (type == REAL_T)) {
			return 1;
		}
	} else if (
	    (strcmp(name, TRUNC) == 0) ||
	    (strcmp(name, ROUND) == 0)
	){
		if (type == REAL_T || type == INTEGER_T) return 1;
	} else if (
	    (strcmp(name, CHR) == 0) ||
	    (strcmp(name, ODD) == 0)
	){
		if (type == INTEGER_T) return 1;
	} else if (
	    (strcmp(name, ORD) == 0) ||
	    (strcmp(name, SUCC) == 0) ||
	    (strcmp(name, PRED) == 0)
	){
		
		if (isScalarMember(arg)) return 1;
		if (isScalarVar(arg)) return 1;
		if (isOrdinal(type)) return 1;
	}
	return 0;
}
