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





/*
 * Given a linked list of ProxySymbols, returns the type which results
 * from using the linked list of ProxySymbols to access the array given
 * by var.
 *
 * Parameters:
 * 	var: symbol for array variable to be indexed into
 * 	indices: linked-list of array indices to use to index into var
 * 
 * Return:
 * 	A Symbol of kind TYPE_KIND that is the expected resultant type of the
 * 		array indexing.
 * 	NULL on error
 *
 * TODO: if index is const not part of scalar, see if its value falls in the
 * allowable range.
 *
 */
Symbol *isValidArrayAccess(ProxySymbol *var, ProxySymbol *indices) {
	Symbol *arrayTypeSym = NULL;
	Symbol *indexTypeSym = NULL;
	Symbol *arg = indices;
	int typeErr = 0;

	if ((var == NULL)||(indices == NULL)) {
		err(EXIT_FAILURE, "Tried to do array access with NULL args.");
	}

	arrayTypeSym = getTypeSym(var);

	if (getType(arrayTypeSym) != ARRAY_T) {
		errMsg = customErrorString("Tried to index into %s, which is "
		    "of type %s, and not an array type.",
		    arg->name,
		    typeToString(getType(arrayTypeSym)));
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}

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
			    "subscript.  Expected type %s "
			    "but got %s",
		    	    typeToString(getType(indexTypeSym)),
		    	    typeToString(getType(arg)));
			recordError(errMsg, yylineno, colno, SEMANTIC);
			return NULL;
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
		return NULL;
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

