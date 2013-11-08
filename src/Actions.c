#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Definitions.h"

#include "ElementArray.h"
#include "Error.h"
#include "Globals.h"
#include "Hash.h"
#include "PreDef.h"
#include "Type.h"
#include "Symbol.h"
#include "Utils.h"
#ifndef TESTBUILD
#include "parser.tab.h"	/* token definitions used in operator compat checks */
#endif
#ifdef TESTBUILD
#include "tokens.h"
#endif
extern int yylineno;
extern int colno;

static char *errMsg;

/*
 * Utility functions. Can maybe be refactored into own module.
 */

/*
 * Check that the given types are compatible when using the given
 * operator.
 *
 * Return a pointer to a Symbol struct 
 * that is populated with the resulting type when performing the operation, and
 * the value of the expression if it can be evaluated (like when dealing with
 * constants).
 *
 * If the types are not combatible for this operator, set error and return NULL.
 * TODO: right now success returns non-NULL for the benefit of unit tests.
 */
Symbol *assertOpCompat(
    Symbol *type1, int opToken, Symbol *type2) {
	
	type_t s1_t, s2_t;
	s1_t = getType(type1);
	s2_t = getType(type2);

	/* if type1 pointer is null but the operator is PLUS or MINUS (i.e.,
	 * it is a unary operator) then we assume the best */ 
	if ((!type1) && (isUnaryOperator(opToken))) {
		if ((s2_t == REAL_T) || (s2_t == INTEGER_T)) return type2;
		return NULL; /* else error */
	} else if (!type1) return NULL; /* else it was an error */


	/* Only simple and string types are compatible with operators */
	if (!(isSimpleType(s1_t) && isSimpleType(s2_t)) &&
	    (s1_t != STRING_T)) {
		/* TODO: record error */
		return NULL;
	}

	/* If operator is a logical operator, we only accept boolean types */
	if (isLogicalOperator(opToken)) {
		if ((s1_t != BOOLEAN_T) || (s2_t != BOOLEAN_T)) return NULL;
		/* Else return pointer to pre-defined boolean type */
		return type1; 
	}

	/* If the operator is relational, we just need op compatible types */
	if ((isRelationalOperator(opToken)) && areOpCompatible(type1, type2)) {
		return getPreDefBool(preDefTypeSymbols);
	}

	if (areArithmeticCompatible(type1, type2)) {
		switch (opToken) {
			case PLUS:
			case MINUS:
			case MULTIPLY:
				if (areBothInts(type1, type2)) {
					return type1;
				}
				else return getPreDefReal(
				    preDefTypeSymbols);
				break;
			case DIVIDE:
				return getPreDefReal(preDefTypeSymbols);
			case DIV:
			case MOD:
				if (areBothInts(type1, type2)) {
					/* return ptr to int type */
					return type1;
				}
				break;
			default:
				/* NOT REACHED */
				break;	
		}
	}

	/* Fell through to here, must have been an error */
	
	return NULL;
}

/*
 * Return 0 if the given types are assignment compatible, otherwise return
 * non-zero
 */
int isAssignmentCompat(Symbol * type1, Symbol * type2) {
	
	if (areSameType(type1, type2)) {
		return 1;
	} else if (areCompatibleStrings(type1, type2)) {
		return 1;
	} else if ((getType(type1) == REAL_T) && 
	    (getType(type2) == INTEGER_T)) {
		return 1;
	}

	errMsg = customErrorString("The type %s cannot be assigned a value "
	    "of type %s", typeToString(getType(type1)), 
	    typeToString(getType(type2)));
	recordError(errMsg, yylineno, colno, SEMANTIC);
	return 0;
}

/*
 * Parser action functions, in the order they appear in parser.y
 */

/*
 * Capture program header definitions of input and output arguments.
 *
 * Arguments may be null if program contains errors.
 */
void doProgramDecl(char *prog_name, char *in_name, char *out_name) {

	// TODO: same a proc decl probably
	// TODO push lexical level, figure this out
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
		/* throw symbol already declated at local lvl error */
	}

	/* Else we can try to make new const  and add it to symbol table */	
	s = newConstSymFromProxy(lvl, id, proxy);		
	if (s) {
		createHashElement(symbolTable, id, s);
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
 */
void doTypeDecl(char *id, Symbol *type) {
	Symbol * s = NULL;
	int lvl = getCurrentLexLevel(symbolTable);

	s = getLocalSymbol(symbolTable, id);
	if (s) {
		/* throw already defined error */
	}
	
	s = newTypeSymFromSym(lvl, id, type);
	if (s) {
		createHashElement(symbolTable, id, s);	
	}
	/* Else, error.  newTypeSymFromSym performs error checking */
}

/*
 * Do a lookup in the symbol table for the type with the given id.
 *
 * Raise an error if the type is not available.
 *
 * Return a pointer to the type.
 */
Symbol *simpleTypeLookup(char *id) {
	
	Symbol *s = getGlobalSymbol(symbolTable, id);
	if (!s) {
		errMsg = customErrorString("The identifier %s has not been "
		  "defined.", id);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}

	if (s->kind != TYPE_KIND) {
		errMsg = customErrorString("The identifier %s is not a type. ",
		    s->name);
		recordError(errMsg, yylineno, colno, SEMANTIC);
	}
	/* Else, we return the given type */
	return s;
}

/*
 * Add new_id as a mamber to scalar_list.
 *
 * Return scalar_list
 */
Symbol *appendToScalarListType(Symbol *scalar_list, char *new_id) {
	return scalar_list;
}

/*
 * Create a new scalar list type with id as the only member.
 *
 * Return a pointer to the new scalar list
 */
Symbol *createScalarListType(char *id) {
	return NULL;
}

/*
 * Create a new array type given the index type and base type.
 */
Symbol *createArrayType(Symbol *index, Symbol *base) {
	Symbol * newArraySym = NULL;
	int lvl = getCurrentLexLevel(symbolTable);
	
	newArraySym = newAnonArraySym(lvl, base, index);
	if (newArraySym) {
		createHashElement(symbolTable, NULL, newArraySym);
		return newArraySym;
	}

	/* Else, error.  Error reporting done in newAnonArraySym() */	
	return NULL;
}

/*
 * Check that the given type is a valid array index type.
 *
 * Raise an error if the type is not valid as an index type.
 *
 * Return the given type.
 */
Symbol *assertArrIndexType(Symbol *index_type) {
	type_t sym_t;

	sym_t = getType(index_type);

	if ( (sym_t != SUBRANGE_T) && (sym_t != SCALAR_T) ) {
		errMsg = customErrorString("Invalid array index type %s. "
		    " Must be of type SUBRANGE or of type SCALAR", 
		    typeToString(sym_t));
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}
	return index_type;
}

/*
 * Create a new subrange type. The arguments are proxy symbols that should
 * constain constant values for the range bounds.
 *
 * Return a pointer to the new subrange type.
 */
Symbol *createRangeType(ProxySymbol *lower, ProxySymbol *upper) {
	Symbol *s = NULL;
	int lvl = getCurrentLexLevel(symbolTable);
	s = newSubrangeSym(lvl, (Symbol *) lower, (Symbol *) upper);
	return s;
}

/*
 * Create a new record type from the array of fields.
 *
 * Return a pointer to the new record type symbol.
 */
Symbol *createRecordType(struct ElementArray *fields) {
	return NULL;
}

/*
 * Create a new element array from the given proxy symbol.
 *
 * Return a pointer to the new array.
 */
struct ElementArray *createRecordMemberList(ProxySymbol *field) {
	struct ElementArray *ea = NULL;

	ea = newElementArray();
	growElementArray(ea);
	if (field) {
		appendElement(ea, field);
	}
	return ea;	
}

/*
 * Append the given proxySymbol to the array of fields.
 *
 * Return a pointer to the array.
 */
struct ElementArray *appendToRecordMemberList(
    struct ElementArray *array, ProxySymbol *field) {
	if (!array) return NULL;
	if (field)  {
		appendElement(array, field);
	}
	return array;
}

/*
 * Create a new ProxySymbol with the given id and type.
 *
 * Return a pointer to the new proxy.
 */
ProxySymbol *newRecordFieldProxy(char *id, Symbol *type) {
	ProxySymbol *newField = NULL;

	if (!id) return NULL;
	if (!type) return NULL;

	newField = newProxySymFromSym(type);
	setSymbolName(newField, id);
	return newField;
}

/*
 * Perform actions necessary when exiting variable dec section.
 */
void exitVarDeclPart(void) {
	// nothing to do here
}

/*
 * Declare a new variable with the given type.
 *
 * Return a pointer to type.
 */
Symbol *doVarDecl(char *id, Symbol *type) {
	Symbol *s = NULL;
	int lvl = 0;
	/* TODO: do local look up for symbol */

	if ((!id) || !(type)) return NULL;

	s = newVariableSym(lvl, id, type);

	if (s) {
		/* TODO: add s to the symbol table */
	}

	return type;
}

/*
 * Exit a procedure or function definition.
 *
 * This is a good time to pop lexical level.
 */
void exitProcOrFuncDecl(void) {
	// TODO
}

/*
 * Declare a new procedure with given arguments and perform anything
 * necessary when entering the procedure body definition (like increasing
 * the lexical level).
 *
 * Both arguments can be NULL if the definition contains errors.
 *
 * Return a pointer to the procedure.
 */
Symbol *enterProcDecl(char *id, struct ElementArray *ea) {

	Symbol *procSym = NULL;
	int lvl = 0;
	/* TODO: local lookup of id in symbol table */
	
	/* if the above lookup returned nothing... */

	procSym = newProcSym(lvl, id, ea);
	return procSym;
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
	Symbol *funcSym = NULL;
	int lvl = 0;

	/* TODO: local lookup of id in symbol table */

	funcSym = newFuncSym(lvl, id, typeSym, ea);
	return funcSym;
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
	
	/* TODO: NO LOOKUP IN SYMBOL TABLE NECESSARY */

	int lvl = 0;

	if ((!id) || (!type)) return NULL;
	return newParamSym(lvl, id, type);
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

/*
 * Perform assignment of x to y.
 */
void assignOp(ProxySymbol *x, ProxySymbol *y) {
}

ProxySymbol *hashLookupToProxy(char *id) {
	Symbol *s = NULL;
	//s = getGlobalSymbol(hash, id);
	if (!s) /* global lookup failed error (make function) */ return NULL;
	return newProxySymFromSym(s);	
}


/*
 * id1 == name of record, id3 == name of field we are trying to access
 */
ProxySymbol *recordAccessToProxy(char *id1, char *id3) {
	return NULL;
}

/*
 * Access an array given the list of indexes.
 *
 * Return a ProxySymbol of the expected type.
 */
ProxySymbol *arrayIndexAccess(ProxySymbol *var, ProxySymbol * indices) {
	/* Record specific errors in isValidArrayAccess */
	if (isValidArrayAccess((Symbol *) var, indices)) {
		return newProxySymFromSym(getTypeSym((Symbol *) var));
	}
	return NULL;
}
/*
 * TODO: cannot use element array to construct list of proxy syms
 * as we are never explicitly constructing a list, just creating a bunch
 * of expressions which have to be proxy symbols.  How to do this this then?
 * Da Hack: link proxy symbols resulting from expressions through the
 * symbol's *next ptr!  
 */
/*
 * Concatenate two arrays of array indexes, maintaining order.
 *
 * Return a pointer to a concatenated list.
 */
ProxySymbol *concatArrayIndexList(ProxySymbol *list1, ProxySymbol *list2) {
	/*
	 * b/c we are parsing right to left, make list2 the head of the
	 * linked list of proxy symbols
 	 * TODO: confirm this with Aaron
	 */
	if ((!list1) && (!list2)) {
		return NULL;
	}
	if (!list1) {
		return list2;
	}
	if (!list2) {
		return list1;
	}

	list1->next = list2;
	return list2;
}

/*
 * Create a new array index list as a ProxySymbol.
 *
 * Return a pointer to the new list.
 */
ProxySymbol *createArrayIndexList(ProxySymbol *exp) {
	if (!exp) {
		return NULL;
	}
	exp->next = NULL;
	return exp;
}

ProxySymbol *eqOp(ProxySymbol *x, ProxySymbol *y) {

	if ((!x) || (!y)) return NULL;
	
	/* 
	 * If x or y is not a constant, we have no responsibility
	 * with regard to insuring the propogation of a compile time
	 * known funciton.
	 */
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), EQUAL, getTypeSym((Symbol *)y)));

	/* Else, we have two CONST_KIND symbols.  We must evaluate */

	return NULL;
}

ProxySymbol *notEqOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), NOT_EQUAL, getTypeSym((Symbol *)y)));
}

ProxySymbol *lessOrEqOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), NOT_EQUAL, getTypeSym((Symbol *)y)));
}

ProxySymbol *lessOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *gtOrEqOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *gtOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *unaryPlusOp(ProxySymbol *y) {
	return NULL;
}

ProxySymbol *unaryMinusOp(ProxySymbol *y) {
	return NULL;
}

ProxySymbol *plusOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *minusOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *orOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *multOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *divideOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *divOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *modOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *andOp(ProxySymbol *x, ProxySymbol *y) {
	return NULL;
}

ProxySymbol *unaryNotOp(ProxySymbol *x) {
	return NULL;
}

/*
 * Make a new ProxySymbol with type integer and given value.
 * Return pointer to the proxy
 */
ProxySymbol *proxyIntLiteral(int value) {
	Symbol *integerType = NULL;
	return newConstProxySym(&value, integerType); 
}
	
/*
 * Make a new anonymous symbol with type real and given value.
 * Return a pointer to the hash symbol.
 */
ProxySymbol *proxyRealLiteral(double value) {
	Symbol *realType = NULL;
	return newConstProxySym(&value, realType);
}

/*
 * Make a new anonymous symbol with the given string.
 * Return a pointer to the hash symbol.
 */
ProxySymbol *proxyStringLiteral(char *value) {
	// TODO: we require the length of the string in order
	// to avoid the cases where the string literal may have null
	// bytes.
	int lvl = 0, strlen = 0;
	return newStringProxySym(lvl, value, strlen);
}

/*
 * Invoke procedure with given name.
 *
 * The argument argv contains a list of arguments.
 */
void procInvok(char *id, struct ElementArray *ea) {

	/* TODO: global lookup for id */
	/* if lookup successful, make sure it is a process */
	/* if lookup successful, call isValidProcInvoke(symbol, ea) */
}

/*
 * Invoke function with the given name.
 *
 * The argument argv contains a list of arguments.
 *
 * Return a ProxySymbol containing the type returned.
 */
ProxySymbol *funcInvok(char *id, struct ElementArray *argv) {

	return NULL;
}

/*
 * Create an argument list for function and procedure invocation.
 *
 * Return a pointer to a ProxySymbol containing the list.
 */
struct ElementArray *createArgList(Symbol *arg) {
	struct ElementArray * ea = NULL;

	if (!arg) {
		/* ERROR */
		return NULL;
	}
	ea = newElementArray();
	growElementArray(ea);
	appendElement(ea, getTypeSym(arg));	
	return ea;
}

/*
 * Concatenate two lists of arguments, maintaining order.
 *
 * Return a pointer to a list containing both sets of arguments.
 * Whether to add the arguments to one of the lists or two make a third
 * list and add all arguments is up to implementation.
 */
struct ElementArray *concatArgLists(
    struct ElementArray *arr1, struct ElementArray *arr2) {
	
	if ((!arr1) && (!arr2)) return NULL;
	if (!arr1) return arr2;
	if (!arr2) return arr1;

	// TODO concatenate the lists

	return NULL;
}

/*
 * Encountered 'continue' statement. Verify we're in a while loop and then
 * continue to next iteration.
 */
void continueLoop(void) {
	// TODO
}

/*
 * Encountered 'exit' statement. Verify we're in a while loop and then
 * exit innermost loop.
 */
void exitLoop(void) {
	// TODO
}

/*
 * End of while loop.
 */
void endWhileLoop(void) {
	// TODO
}
