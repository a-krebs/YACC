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
 * Perform assignment of x to y.
 */
void assignOp(ProxySymbol *x, ProxySymbol *y) {
	if (!(x) || !(y)) return;

	if ( x->kind == CONST_KIND ) {
		errMsg = customErrorString("The identifier %s is a constant and cannot be re-assigned a "
			"value.", x->name);
		recordError(errMsg, yylineno, colno, SEMANTIC);
	} 

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
	Symbol *tmp;
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
	tmp = list1;
	while (tmp->next != NULL) tmp = tmp->next;
	tmp->next = list2;

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

#if DEBUG
	printf("\n%s %s %s\n", typeToString(getType(type1)), 
	opToString(opToken), typeToString(getType(type2)));
#endif
	/* if type1 pointer is null but the operator is PLUS or MINUS (i.e.,
	 * it is a unary operator) then we assume the best */ 
	if ((!type1) && (isUnaryOperator(opToken))) {
		if ((s2_t == REAL_T) 
			|| (s2_t == INTEGER_T)
			|| (s2_t == BOOLEAN_T)) {
			return type2;
		}	
		else {
			opError(typeToString(s2_t), opToken, 
			    typeToString(s2_t));
			return NULL;
		}
	} else if (!type1) {
		opError(typeToString(s2_t), opToken, typeToString(s2_t));
		return NULL; /* else it was an error */
	}

	/* If the operator is relational, we just need op compatible types */
	if ( isRelationalOperator(opToken) && areOpCompatible(type1, type2) ) {
		return getPreDefBool(preDefTypeSymbols);
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
	// if (!type1->name) return 0;

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