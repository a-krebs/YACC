#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ElementArray.h"
#include "Error.h"
#include "ErrorLL.h"
#include "Type.h"
#include "Hash.h"
#include "PreDef.h"
#include "SymbolAll.h"

/*For error reporting*/
extern int yylineno;
extern int colno;
static char *errMsg;
struct Error *e;


int typeIsInValidArgs(Symbol *s, type_t type) {
	char *name = NULL;
	if (!s) return 0;
	name = s->name;

	if (
	    (strcmp(name, "abs") == 0) ||
	    (strcmp(name, "sqr") == 0) ||
	    (strcmp(name, "sin") == 0) ||
	    (strcmp(name, "cos") == 0) ||
	    (strcmp(name, "exp") == 0) ||
	    (strcmp(name, "ln") == 0) ||
	    (strcmp(name, "sqrt") == 0) ||
	    (strcmp(name, "arctan") == 0)
	) {
		if ((type == INTEGER_T) || (type == REAL_T)) {
			return 1;
		}
	} else if (
	    (strcmp(name, "trunc") == 0) ||
	    (strcmp(name, "round") == 0)
	){
		if (type == REAL_T) return 1;
	} else if (
	    (strcmp(name, "chr") == 0) ||
	    (strcmp(name, "odd") == 0)
	){
		if (type == INTEGER_T) return 1;
	} else if (
	    (strcmp(name, "ord") == 0) ||
	    (strcmp(name, "succ") == 0) ||
	    (strcmp(name, "pred") == 0)
	){
		if (isOrdinal(type)) return 1;
	}
	return 0;
}


/*
 * Given a linked list of ProxySymbols, returns the type which results
 * from using the linked list of ProxySymbols to access the array given
 * by var.
 * TODO: if index is const not part of scalar, see if its value falls in the
 * allowable range.
 *
 */
Symbol *
isValidArrayAccess(ProxySymbol *var, ProxySymbol *indices)
{
	Symbol *arrayTypeSym = NULL;
	Symbol *indexTypeSym = NULL;
	Symbol *arg = indices;
	int typeErr = 0;

	if (!var) {
		return NULL;
	}
	arrayTypeSym = getTypeSym(var);

	if (getType(arrayTypeSym) != ARRAY_T) {
		return arrayTypeSym;
	}
//	arrayDim = getArrayDim(arrayTypeSym);
//	nArgs = getSymbolListLength(indices);

//	if (arrayDim != nArgs) {
//		errMsg = customErrorString("Trying to access array %s of "
//		    "dimension %d with %d index/indices.", var->name,
//		    arrayDim, nArgs);
//		recordError(errMsg, yylineno, colno, SEMANTIC);
//		return NULL;
//	}

	indexTypeSym = getArrayIndexSym(arrayTypeSym);
	while ( (arg) && (getType(arrayTypeSym) == ARRAY_T)) {
		switch (getType(indexTypeSym)) {
		case SCALAR_T:
			if (!isConstInScalar(arg, indexTypeSym))
			    typeErr = 1;
			break;
		case SUBRANGE_T:
			if (!areSameType(
			    getSubrangeBaseTypeSym(indexTypeSym),
			    getTypeSym(arg))) typeErr = 1;
			break;
		default:
			if (!areSameType(indexTypeSym,
			     getTypeSym(arg))) typeErr = 1;
			break;	
		}
		if (typeErr) {
			errMsg = customErrorString("Invalid array "
			    "subscript.  Expected type %d "
			    "%d but got %s",
		    	    typeToString(getType(indexTypeSym)),
		    	    typeToString(getType(arg)));
			recordError(errMsg, yylineno, colno, SEMANTIC);
		}
		typeErr = 0;
		arrayTypeSym = getArrayBaseSym(arrayTypeSym);
		indexTypeSym = getArrayIndexSym(arrayTypeSym);
		arg = arg->next;
	}

	/* Else are ready to return the base type */

	if (arg) {
		/* Didn't exhaust args, but exhausted arrays.
		 * Return arrayTypeSym */
		recordError("Illegal array access -- too many indices.",
		    yylineno, colno, SEMANTIC);
		return arrayTypeSym;
	} 
	return arrayTypeSym;
}


/*
 * Returns the dimension of the given array (assumes that the given
 * Symbol describing the array is the "first dimensional array")
 */
int
getArrayDim(Symbol *s)
{
	Symbol *nextIndexSym = NULL;
	int dim = 0;	
	nextIndexSym = getArrayIndexSym(s);
	while (nextIndexSym != NULL) {
		dim++;
		nextIndexSym = getArrayIndexSym(nextIndexSym);
	}
	return dim;
}


/*
 * Returns the symbol which indexes the array.
 */
Symbol *
getArrayIndexSym(Symbol *s)
{
	if (!s) return NULL;
	if (getType(s) != ARRAY_T) return NULL;
	return getTypePtr(s)->Array->indexTypeSym;
}


Symbol *
getArrayTerminalTypeSym(Symbol *s)
{
	Symbol *baseSym = NULL;
	if (!s) return NULL;
	if (getType(s) != ARRAY_T) return NULL;
	baseSym = getTypePtr(s)->Array->baseTypeSym;
	while (getType(baseSym) == ARRAY_T) {
		baseSym = getTypePtr(baseSym)->Array->baseTypeSym;
	}
	return baseSym;

}


Symbol *
getArrayBaseSym(Symbol *s)
{
	if (!s) return NULL;
	if (getType(s) != ARRAY_T) return NULL;
	return getTypePtr(s)->Array->baseTypeSym;

}

