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
// extern int yylineno;
// extern int colno;
// static char *errMsg;
// struct Error *e;


ProxySymbol *
newProxySymFromSym(Symbol *s)
{
	ProxySymbol *ps = NULL;
	if (!s) return NULL;

	ps = calloc(1, sizeof(ProxySymbol));
	if (s->name) {
		setSymbolName((Symbol *)ps, s->name);
	}

	ps->kind = s->kind;
	ps->kindPtr = s->kindPtr;
	ps->typeOriginator = 0;
	ps->lvl = s->lvl;
	ps->offset = s->offset;
	ps->size = s->size;
	if (s->wasArray) {
		ps->wasArray = 1;
		s->wasArray = 0;
	}
	return ps;
}


/*
 * Creates a new CONST_KIND ProxySymbol.
 *
 * Parameters:
 * 	id: the 
 * 	result: a pointer to the value for the new constant
 * 		this will be case to the appropriate C type depending on typeSym
 * 	tpyeSym: a symbol with kind TYPE_KIND for the new symbol
 *
 * Return:
 * 	A pointer to the new ProxySymbol
 */
ProxySymbol *newConstProxySym(char *id, void * result, Symbol *typeSym)
{
	Symbol *constSym = NULL;
	double *doubleResult;
	int *intResult;
	char *charResult;
	struct String *stringResult;

	/* id can be NULL, this makes the constant anonymous */
	if ((result == NULL) || (typeSym == NULL)) {
		err(EXIT_FAILURE, "Passed NULL arguments to newConstProxySym");
	}

	constSym = createConstSymbol(id);
	if (!constSym) {
		err(1, "Failed to allocate memory for new constant proxy "
		    "symbol!");
	}
	
	/* set the new symbol's type */
	// TODO, this should point back to a pre-defined type, and we should
	// enforce that the given typeSym is a pre-defined type
	setInnerTypeSymbol(constSym, typeSym);

	/* 
	 * The memory for Boolean.value, Char.value, etc is allocated
	 * when the symbol is created.
	 */
	switch (getType(typeSym)) {
	case BOOLEAN_T:
		intResult = (int *) result;
		getConstVal(constSym)->Boolean.value = *intResult;
		break;
	case CHAR_T:
		charResult = (char *) result;
		getConstVal(constSym)->Char.value = *charResult;
	case INTEGER_T:
		intResult = (int *) result;
		getConstVal(constSym)->Integer.value = *intResult;
		break;
	case REAL_T:
		doubleResult = (double *) result;
		getConstVal(constSym)->Real.value = *doubleResult;
		break;
	case STRING_T:
		stringResult = (struct String *) result;
		setStringStr(
		    &getConstVal(constSym)->String, 
		    stringResult->str,
		    stringResult->strlen);
		break;
	default:
		/* Shouldn't be reached */
		err(EXIT_FAILURE, "Called newConstProxySym with invalid "
		    "typeSym (can't get inner type)");
	}

	return (ProxySymbol *) constSym;
}


/*
 * TODO: proxy symbol will have kindPtr to pre-defined kind?
 */
// TODO this looks like a dup of newConstProxySym?
Symbol *
newConstSymFromProxy(int lvl, char * id, ProxySymbol * proxySym)
{
	Symbol * newConstSym = NULL;

	/* Error checking */
	if (!proxySym) {
		/* Record error */
		return NULL;
	}

	if (proxySym->kind != CONST_KIND) {
		/* Error: trying to declare constant with non-constant kind */
		return NULL;
	}

	newConstSym = calloc(1, sizeof(Symbol));
	if (!newConstSym) {
		err(1, "Failed to allocate memory for new const symbol!");
		exit(1);
	}	

	setSymbolName(newConstSym, id);
	
	newConstSym->kind = CONST_KIND;
	allocateKindPtr(newConstSym);
	setInnerTypeSymbol(newConstSym, getTypeSym(proxySym));
	copyConstVal(&(newConstSym->kindPtr.ConstKind->value), 
	    getConstVal(proxySym), getType(proxySym));
	newConstSym->lvl = lvl;

	return newConstSym;
}
