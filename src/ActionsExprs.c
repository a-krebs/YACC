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
	return exprsOp(x, EQUAL ,y);

	/* Else, we have two CONST_KIND symbols.  We must evaluate */

	return NULL;
}


ProxySymbol *notEqOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, NOT_EQUAL ,y);
}


ProxySymbol *lessOrEqOp(ProxySymbol *x, ProxySymbol *y) {    
	return exprsOp(x, LESS_OR_EQUAL ,y);
}


ProxySymbol *lessOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, LESS ,y);
}


ProxySymbol *gtOrEqOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, GREATER_OR_EQUAL ,y);
}


ProxySymbol *gtOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, GREATER ,y);
}


ProxySymbol *unaryPlusOp(ProxySymbol *y) {
	return exprsOp(NULL, PLUS, y);
}


ProxySymbol *unaryMinusOp(ProxySymbol *y) {
	return exprsOp(NULL, MINUS ,y);
}


ProxySymbol *plusOp(ProxySymbol *x, ProxySymbol *y) {

	ProxySymbol *ps = exprsOp(x, PLUS ,y);
			  
	if (ps) {
		emitAddition( (Symbol *) x, (Symbol *) y);
		return ps;
	} else {
		return NULL;
	}
}


ProxySymbol *minusOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, MINUS ,y);
}


ProxySymbol *orOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, OR ,y);
}


ProxySymbol *multOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, MULTIPLY ,y);
}


ProxySymbol *divideOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, DIVIDE ,y);
}


ProxySymbol *divOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, DIV ,y);
}


ProxySymbol *modOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, MOD ,y);
}


ProxySymbol *andOp(ProxySymbol *x, ProxySymbol *y) {
	return exprsOp(x, AND ,y);
}


ProxySymbol *unaryNotOp(ProxySymbol *y) {
	return exprsOp(NULL, NOT ,y);
}


ProxySymbol *exprsOp(ProxySymbol *x, int opToken, ProxySymbol *y){

	ProxySymbol *ps = NULL;
 	
	Symbol *sym_t = assertOpCompat(getTypeSym(
	    (Symbol *) x), opToken, getTypeSym((Symbol *)y));
	    
	if (sym_t == NULL) {
		return NULL;
	}
	
	if ((x == NULL) || (y == NULL)){
		/*
		 * Add unary operation later
		 */
		return y;
	
	} else if ((x->kind == CONST_KIND) && (y->kind == CONST_KIND)) {
		ps = (ProxySymbol *)createConstSymbol(NULL);
		ps->kindPtr.ConstKind->typeSym = sym_t;
		
	} else {
		ps = (ProxySymbol *)createVarSymbol(NULL);
		ps->kindPtr.ConstKind->typeSym = sym_t;
	} 

	return ps;
}

ProxySymbol *calculate
	(ProxySymbol *ps, ProxySymbol *x, int opToken, ProxySymbol *y) {
	

	if ((getType(x) == INTEGER_T) && (getType(y) == INTEGER_T)) {
			
		if (opToken == EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value ==
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == NOT_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value !=
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == LESS_OR_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value <=
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == LESS) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value <
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == GREATER_OR_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value >=
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == GREATER) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value >
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == PLUS) { 
			ps->kindPtr.ConstKind->value.Integer.value =
			x->kindPtr.ConstKind->value.Integer.value + 
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == MINUS) {
			ps->kindPtr.ConstKind->value.Integer.value =
			x->kindPtr.ConstKind->value.Integer.value - 
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == OR) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value || 
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == MULTIPLY) {
			ps->kindPtr.ConstKind->value.Integer.value =
			x->kindPtr.ConstKind->value.Integer.value * 
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == DIVIDE) {
			ps->kindPtr.ConstKind->value.Real.value =
			(double)x->kindPtr.ConstKind->value.Integer.value / 
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == DIV) {
			ps->kindPtr.ConstKind->value.Integer.value =
			x->kindPtr.ConstKind->value.Integer.value / 
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == MOD) {
			ps->kindPtr.ConstKind->value.Integer.value =
			x->kindPtr.ConstKind->value.Integer.value % 
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == AND) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value && 
			y->kindPtr.ConstKind->value.Integer.value; }
	
	} else if ((getType(x) == REAL_T) && (getType(y) == INTEGER_T)) {
	
		if (opToken == EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value ==
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == NOT_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value !=
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == LESS_OR_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value <=
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == LESS) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value <
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == GREATER_OR_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value >=
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == GREATER) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value >
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == PLUS) { 
			ps->kindPtr.ConstKind->value.Real.value =
			x->kindPtr.ConstKind->value.Real.value + 
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == MINUS) {
			ps->kindPtr.ConstKind->value.Real.value =
			x->kindPtr.ConstKind->value.Real.value - 
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == OR) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value || 
			y->kindPtr.ConstKind->value.Integer.value; }
			
		if (opToken == MULTIPLY) {
			ps->kindPtr.ConstKind->value.Real.value =
			x->kindPtr.ConstKind->value.Real.value * 
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == DIVIDE) {
			ps->kindPtr.ConstKind->value.Real.value =
			(double)x->kindPtr.ConstKind->value.Real.value / 
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == DIV) {
			ps->kindPtr.ConstKind->value.Integer.value =
			x->kindPtr.ConstKind->value.Real.value / 
			y->kindPtr.ConstKind->value.Integer.value; }
		
		if (opToken == MOD) {
			/*TODO
			Error Report
			*/ }
		
		if (opToken == AND) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value && 
			y->kindPtr.ConstKind->value.Integer.value; }
	
	} else if ((getType(x) == INTEGER_T) && (getType(y) == REAL_T)) {
	
		if (opToken == EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value ==
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == NOT_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value !=
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == LESS_OR_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value <=
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == LESS) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value <
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == GREATER_OR_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value >=
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == GREATER) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value >
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == PLUS) { 
			ps->kindPtr.ConstKind->value.Real.value =
			x->kindPtr.ConstKind->value.Integer.value + 
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == MINUS) {
			ps->kindPtr.ConstKind->value.Real.value =
			x->kindPtr.ConstKind->value.Integer.value - 
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == OR) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value || 
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == MULTIPLY) {
			ps->kindPtr.ConstKind->value.Real.value =
			x->kindPtr.ConstKind->value.Integer.value * 
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == DIVIDE) {
			ps->kindPtr.ConstKind->value.Real.value =
			(double)x->kindPtr.ConstKind->value.Integer.value / 
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == DIV) {
			ps->kindPtr.ConstKind->value.Integer.value =
			x->kindPtr.ConstKind->value.Integer.value / 
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == MOD) {
			/*TODO
			Error Report
			*/ }
		
		if (opToken == AND) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Integer.value && 
			y->kindPtr.ConstKind->value.Real.value; }
			
	} else if ((getType(x) == REAL_T) && (getType(y) == REAL_T)) {
	
		if (opToken == EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value ==
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == NOT_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value !=
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == LESS_OR_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value <=
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == LESS) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value <
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == GREATER_OR_EQUAL) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value >=
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == GREATER) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value >
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == PLUS) { 
			ps->kindPtr.ConstKind->value.Real.value =
			x->kindPtr.ConstKind->value.Real.value + 
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == MINUS) {
			ps->kindPtr.ConstKind->value.Real.value =
			x->kindPtr.ConstKind->value.Real.value - 
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == OR) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value || 
			y->kindPtr.ConstKind->value.Real.value; }
			
		if (opToken == MULTIPLY) {
			ps->kindPtr.ConstKind->value.Real.value =
			x->kindPtr.ConstKind->value.Real.value * 
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == DIVIDE) {
			ps->kindPtr.ConstKind->value.Real.value =
			x->kindPtr.ConstKind->value.Real.value / 
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == DIV) {
			ps->kindPtr.ConstKind->value.Integer.value = 
			x->kindPtr.ConstKind->value.Real.value / 
			y->kindPtr.ConstKind->value.Real.value; }
		
		if (opToken == MOD) {
			/*TODO
			Error Report
			*/ }
		
		if (opToken == AND) {
			ps->kindPtr.ConstKind->value.Boolean.value =
			x->kindPtr.ConstKind->value.Real.value && 
			y->kindPtr.ConstKind->value.Real.value; }
	
	}
	
	return ps;
	
}


/*
 * Check that the given types are compatible when using the given
 * operator.
 *
 * Parameters:  typeSymbol1: a symobol of type TYPE
 *		opToken: operation to check against	
 *		typeSymbol1: a symobol of type TYPE
 *
 * Returns: Return a pointer to a Symbol struct that is populated 
 * 		with the resulting type when performing the operation. 
 *		Otherwise, returns and if possible, sets an opError message.
 */
Symbol *assertOpCompat(
    Symbol *typeSymbol1, int opToken, Symbol *typeSymbol2) {
	
	type_t type1 = getType(typeSymbol1);
	type_t type2 = getType(typeSymbol2);

	if ( (!typeSymbol1) && (!typeSymbol2)) return NULL;

#if DEBUG
	printf("\n%s %s %s\n", typeToString(getType(typeSymbol1)), 
	opToString(opToken), typeToString(getType(typeSymbol2)));
#endif

	/* if typeSymbol1 pointer is null but the operator is PLUS or MINUS (i.e.,
	 * it is a unary operator) then we assume the best */ 
	if ( typeSymbol1 == NULL
		&& isUnaryOperator(opToken)
		&& isRealIntBool(type2)
	) {
		return typeSymbol2;
	}

	/* At this point, we do not accept nulls */
	if ( typeSymbol1 == NULL || typeSymbol2 == NULL ) {
		opError(typeToString(type2), opToken, typeToString(type2));
		return NULL; /* else it was an error */		
	}

	/* If the operator is relational, we just need op compatible types */
	if ( isRelationalOperator(opToken) 
		&& areOpCompatible(typeSymbol1, typeSymbol2) ) {
		return getPreDefBool(preDefTypeSymbols);
	}	

	/* If the operator is relational and both types are scalar */
	if ( isRelationalOperator(opToken) 
		&& areSameType(typeSymbol1, typeSymbol2) 
		&& type1 == SCALAR_T 
	) 
	{
		return getPreDefBool(preDefTypeSymbols); 
	}

	/* If operator is a logical operator, we only accept boolean types */
	if (isLogicalOperator(opToken)) {
		/*check to see if both types are boolean*/
		if ((type1 != BOOLEAN_T) || (type2 != BOOLEAN_T)) {
			opError(typeToString(type1), opToken,
			    typeToString(type2));
			return NULL;
		}

		/* Else return pointer to pre-defined boolean type */
		return getPreDefBool(preDefTypeSymbols); 
	}


	if (areArithmeticCompatible(typeSymbol1, typeSymbol2)) {
		switch (opToken) {
			case PLUS: //drop through
			case MINUS: //drop through
			case MULTIPLY:
				if (areBothInts(typeSymbol1, typeSymbol2)) {
					return getPreDefInt(preDefTypeSymbols);
				}
				else {
				       return getPreDefReal(preDefTypeSymbols);
				} 
				break;
			case DIVIDE:
				return getPreDefReal(preDefTypeSymbols);
			case DIV: //drop throught
			case MOD:
				if (areBothInts(typeSymbol1, typeSymbol2)) {
					return getPreDefInt(preDefTypeSymbols);
				}
				break;
			default:
				/* NOT REACHED */
				break;	
		}
	}
	
	opError(typeToString(type1), opToken, typeToString(type2));
	return NULL;
}


/*
 * Boolean function to determine if two symbols are assignment
 * compatible
 *
 * Parameters:  type1: type symbole to compare
 *		type2: type symbole to compare
 *
 * Returns: 1 if both symbols are compatible. 0 otherwise
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
