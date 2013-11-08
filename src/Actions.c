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

	if ( (!type1) && (!type2)) return NULL;

	printf("\n%s %s %s\n", typeToString(getType(type1)), 
	opToString(opToken), typeToString(getType(type2)));
	/* if type1 pointer is null but the operator is PLUS or MINUS (i.e.,
	 * it is a unary operator) then we assume the best */ 
	if ((!type1) && (isUnaryOperator(opToken))) {
		if ((s2_t == REAL_T) || (s2_t == INTEGER_T)) return type2;
		else {
			opError(typeToString(s2_t), opToken, 
			    typeToString(s2_t));
			return NULL;
		}
	} else if (!type1) {
		opError(typeToString(s2_t), opToken, typeToString(s2_t));
		return NULL; /* else it was an error */
	}

	if ( (isRelationalOperator(opToken) && areSameType(type1, type2) ) &&
	    	getType(type1) == SCALAR_T ) {
		return getPreDefBool(preDefTypeSymbols); 
	}


	/* Only simple and string types are compatible with operators */
	if (!(isSimpleType(s1_t) && isSimpleType(s2_t)) &&
	    (s1_t != STRING_T)) {
		opError(typeToString(s1_t), opToken, typeToString(s2_t));
		return NULL;
	}

	/* If operator is a logical operator, we only accept boolean types */
	if (isLogicalOperator(opToken)) {
		if ((s1_t != BOOLEAN_T) || (s2_t != BOOLEAN_T)) {
			opError(typeToString(s1_t), opToken,
			    typeToString(s2_t));
			return NULL;
		}
		/* Else return pointer to pre-defined boolean type */
		return getPreDefBool(preDefTypeSymbols); 
	}

	/* If the operator is relational, we just need op compatible types */
	if ( isRelationalOperator(opToken) && areOpCompatible(type1, type2) ) {
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
					return getPreDefInt(
					    preDefTypeSymbols);
				}
				break;
			default:
				/* NOT REACHED */
				break;	
		}
	}
	
	opError(typeToString(s1_t), opToken, typeToString(s2_t));
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

	errMsg = customErrorString("The type %s cannot be assigned a value"
	    " of type %s", typeToString(getType(type1)), 
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
	incrementLexLevel(symbolTable);
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
		alreadyDefinedError(id);
		return;
	}

	/* Else we can try to make new const  and add it to symbol table
*/	
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
struct ElementArray *appendToScalarListType(struct ElementArray *ea,
    char *id) {
	Symbol *s = NULL;
	if (!ea) return NULL;
	
	s = getLocalSymbol(symbolTable, id);
	if (s) {
		alreadyDefinedError(id);
		return NULL;
	}
	s = (Symbol *) newConstProxySym(&ea->nElements, 
	    getPreDefInt(preDefTypeSymbols));
	s->lvl = getCurrentLexLevel(symbolTable);
	setSymbolName(s, id);
	createHashElement(symbolTable, s->name, s);
	appendElement(ea, s);
	return ea;
}

struct ElementArray * createScalarList(char *id) {
	Symbol *s = NULL;	
	struct ElementArray *ea = NULL;
	int value = 0;

	s = getLocalSymbol(symbolTable, id);
	if (s) {
		alreadyDefinedError(id);
		return NULL;
	}
	s = (Symbol *) newConstProxySym(&value, 
	    getPreDefInt(preDefTypeSymbols));
	setSymbolName(s, id);
	s->lvl = getCurrentLexLevel(symbolTable);
	createHashElement(symbolTable, s->name, s);
	ea = newElementArray();
	appendElement(ea, s);
	return ea;
}


/*
 * Create a new scalar list type with id as the only member.
 *
 * Return a pointer to the new scalar list
 */
Symbol *createScalarListType(struct ElementArray *ea) {
	Symbol *s = NULL;
	int lvl = getCurrentLexLevel(symbolTable);
	if (!ea) return NULL;
	s = newAnonScalarSym(lvl, ea);
	createHashElement(symbolTable, NULL, s);
	return s;
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

	if (!index_type) return NULL;
	if (index_type->kind != TYPE_KIND) return NULL;

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
	if (!(lower) || !(upper)) return NULL;
	s = newSubrangeSym(lvl, (Symbol *) lower, (Symbol *) upper);
	return s;
}

/*
 * Create a new record type from the array of fields.
 *
 * Return a pointer to the new record type symbol.
 */
Symbol *createRecordType(struct ElementArray *fields) {
	Symbol *recType = NULL;
	Symbol *newField = NULL;
	int lexLvl = -1;
	int recordLexLvl = -1;
	ProxySymbol *f = NULL;
	struct hash *recHash = NULL;
	char *fieldId;

	lexLvl = getCurrentLexLevel(symbolTable);

	recType = newRecordTypeSym(lexLvl, NULL);
	recHash = recType->kindPtr.TypeKind->typePtr.Record->hash;

	recordLexLvl = getCurrentLexLevel(recHash);

	for (int i = 0; i < fields->nElements; i++) {
		f = getElementAt(fields, i);
		if (!f) continue;
		fieldId = f->name;

		if (!fieldId) {
			freeProxySymbol(f);
			continue;
		}

		newField = newVariableSym(recordLexLvl, fieldId, getTypeSym(f));

		if (getLocalSymbol(recHash, fieldId) != NULL) {
			errMsg = customErrorString(
			    "Record field with name %s already defined.",
			    fieldId); 
			recordError(errMsg, yylineno, colno, SEMANTIC);
			freeProxySymbol(f);
			continue;
		}
		
		if (createHashElement(recHash, fieldId, newField) != 0) {
			freeProxySymbol(f);
			continue;
		}
	}

	return recType;
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

	newField = newVariableSym(0, id, type);
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
	int lvl = getCurrentLexLevel(symbolTable);
	s = getLocalSymbol(symbolTable, id);
	if (s) {
		alreadyDefinedError(id);
		return NULL;
	}

	if ((!id) || !(type)) return NULL;

	s = newVariableSym(lvl, id, type);
	if (s) {
		createHashElement(symbolTable, id, s);
	}
	return type;
}

/*
 * Exit a procedure or function definition.
 *
 * This is a good time to pop lexical level.
 */
void exitProcOrFuncDecl(void) {
	popLexLevel(symbolTable);
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
	Symbol *s = NULL;

	if (!id) {
		return NULL;
	}

	int lvl = getCurrentLexLevel(symbolTable);
	incrementLexLevel(symbolTable);
	s = getLocalSymbol(symbolTable, id);
	if (s) {
		errMsg = customErrorString("Procedure with name %s "
		    "is already defined.",id);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}

	if (!ea) {
		ea = newElementArray();
	}
	s = newProcSym(lvl, id, ea);
	if (createHashElement(symbolTable, id, s) != 0) {
		// TODO error
	}
	incrementLexLevel(symbolTable);
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
	Symbol *s = NULL;
	int lvl = getCurrentLexLevel(symbolTable);

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

	s = newFuncSym(lvl, id, typeSym, ea);
	if (createHashElement(symbolTable, id, s) != 0) {
		// TODO error
	}
	incrementLexLevel(symbolTable);
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
	
	int lvl = getCurrentLexLevel(symbolTable);
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
	if (!(x) || !(y)) return;
	isAssignmentCompat(getTypeSym(x), getTypeSym(y));
}

ProxySymbol *hashLookupToProxy(char *id) {
	Symbol *s = NULL;
	s = getGlobalSymbol(symbolTable, id);
	if (!s) {
		notDefinedError(id);
		return NULL;
	}
	return newProxySymFromSym(s);	
}


/*
 * id1 == name of record, id3 == name of field we are trying to access
 */
ProxySymbol *recordAccessToProxy(ProxySymbol *p, char *id) {
	Symbol *s = NULL;
	struct Record *r = NULL;

	if ((!p) || (!id)) return NULL;

	s = getTypeSym(p);
	if (getType(s) != RECORD_T) {
		errMsg = customErrorString("Cannot get field %s from %s. "
		    "Identifier %s is not a record.", id, p->name, p->name);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}
	
	r = s->kindPtr.TypeKind->typePtr.Record;

	s = getGlobalSymbol(r->hash, id);
	if (!s) {
		errMsg = customErrorString("Field %s does not exist in %s.",
		    id, p->name);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}
	return newProxySymFromSym(s);
}

/*
 * Access an array given the list of indexes.
 *
 * Return a ProxySymbol of the expected type.
 */
ProxySymbol *arrayIndexAccess(ProxySymbol *var, ProxySymbol * indices) {
	/* Record specific errors in isValidArrayAccess */
	if ((!indices) || (!var)) return NULL;	
	return isValidArrayAccess((Symbol *) var, indices);

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

	list2->next = list1;
	return list1;
}

/*
 * Create a new array index list as a ProxySymbol.
 *
 * Return a pointer to the new list.
 */
ProxySymbol *createArrayIndexList(ProxySymbol *exp) {
	if (!exp) return NULL;
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
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), LESS, getTypeSym((Symbol *)y)));
}

ProxySymbol *gtOrEqOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), GREATER_OR_EQUAL, getTypeSym((Symbol *)y)));
}

ProxySymbol *gtOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), GREATER, getTypeSym((Symbol *)y)));
}

ProxySymbol *unaryPlusOp(ProxySymbol *y) {
	ProxySymbol *ps = newProxySymFromSym(assertOpCompat(
	    NULL, PLUS, getTypeSym((Symbol *)y)));
	return ps;
}

ProxySymbol *unaryMinusOp(ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(
	   NULL, MINUS, getTypeSym((Symbol *)y)));
}

ProxySymbol *plusOp(ProxySymbol *x, ProxySymbol *y) {
	ProxySymbol *ps = newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), PLUS, getTypeSym((Symbol *)y)));

	return ps;
}

ProxySymbol *minusOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), MINUS, getTypeSym((Symbol *)y)));
}

ProxySymbol *orOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), OR, getTypeSym((Symbol *)y)));
}

ProxySymbol *multOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), MULTIPLY, getTypeSym((Symbol *)y)));
}

ProxySymbol *divideOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), DIVIDE, getTypeSym((Symbol *)y)));
}

ProxySymbol *divOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), DIV, getTypeSym((Symbol *)y)));
}

ProxySymbol *modOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), MOD, getTypeSym((Symbol *)y)));
}

ProxySymbol *andOp(ProxySymbol *x, ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(getTypeSym(
	    (Symbol *) x), AND, getTypeSym((Symbol *)y)));
}

ProxySymbol *unaryNotOp(ProxySymbol *y) {
	return newProxySymFromSym(assertOpCompat(
	    NULL, NOT, getTypeSym((Symbol *)y)));
}

/*
 * Make a new ProxySymbol with type integer and given value.
 * Return pointer to the proxy
 */
ProxySymbol *proxyIntLiteral(int value) {
	Symbol *integerType = getPreDefInt(preDefTypeSymbols); 
	return newConstProxySym(&value, integerType); 
}
	
/*
 * Make a new anonymous symbol with type real and given value.
 * Return a pointer to the hash symbol.
 */
ProxySymbol *proxyRealLiteral(double value) {
	Symbol *realType = getPreDefReal(preDefTypeSymbols);
	return newConstProxySym(&value, realType);
}

ProxySymbol *proxyCharLiteral(struct String s) {
	Symbol *charType = getPreDefChar(preDefTypeSymbols);
	return newConstProxySym((s.str+1), charType);
}

/*
 * Make a new anonymous symbol with the given string.
 * Return a pointer to the hash symbol.
 */
ProxySymbol *proxyStringLiteral(struct String s) {
	int lvl = getCurrentLexLevel(symbolTable);
	return newStringProxySym(lvl, (s.str+1), s.strlen);
}

/*
 * Invoke procedure with given name.
 *
 * The argument argv contains a list of arguments.
 */
void procInvok(char *id, struct ElementArray *ea) {
	Symbol *s = NULL;
	s = getGlobalSymbol(symbolTable, id);
	if (!s) {
		notDefinedError(id);
		return;
	}
	if (!ea) {
		ea = newElementArray();
	}
	// this prints errors, so call it but ignore return value
	isValidProcInvocation(s, ea);
}

/*
 * Invoke function with the given name.
 *
 * The argument argv contains a list of arguments.
 *
 * Return a ProxySymbol containing the type returned.
 */
ProxySymbol *funcInvok(char *id, struct ElementArray *argv) {
	Symbol *s = NULL;
	s = getGlobalSymbol(symbolTable, id);
	if (!s) {
		notDefinedError(id);
		return NULL;
	}
	if (!argv) {
		argv = newElementArray();
	}

	if (isValidFuncInvocation(s, argv)) {
		return getTypeSym(s);
	}

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
	
	struct ElementArray *ea;
	if ((!arr1) && (!arr2)) return NULL;
	if (!arr1) return arr2;
	if (!arr2) return arr1;

	ea = appendElementArray(arr1, arr2);
	return ea;
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

int getStrlen(struct String s)
{
	return s.strlen;
}
