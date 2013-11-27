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


/* Creates const kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createConstSymbol(char *id) {
	return createSymbol(symbolTable, id, CONST_KIND, TYPEORIGINATOR_NO);
}


/* Creates func kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createFuncSymbol(char *id) {
	return createSymbol(symbolTable, id, FUNC_KIND, TYPEORIGINATOR_NO);
}


/* Creates Param kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createParamSymbol(char *id) {
	return createSymbol(symbolTable, id, PARAM_KIND, TYPEORIGINATOR_NO);
}


/* Creates proc kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createProcSymbol(char *id) {
	return createSymbol(symbolTable, id, PROC_KIND, TYPEORIGINATOR_NO);
}


/* Creates var kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createVarSymbol(char *id) {
	return createSymbol(symbolTable, id, VAR_KIND, TYPEORIGINATOR_NO);
}


/* Creates type kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *		typeOriginator: flag for if type originator 
 *
 * Return: Newly created symbol
 */
Symbol *createTypeSymbol(char *id, int typeOriginator) {
	return createSymbol(symbolTable, id, TYPE_KIND, typeOriginator);
}

/* Returns pointer to base type symbol of the subrange symbol
 *
 * Parameters:
 * 		s: subrange symbol
 *
 * Return: a pointer to the type symbol
 */
Symbol * getSubrangeBaseTypeSym(Symbol *sr) {
	if (!sr) return NULL;
	if (getType(sr) != SUBRANGE_T) return NULL;
	return getTypePtr(sr)->Subrange->baseTypeSym;
}


/* Frees passed proxy symbol
 *
 * Parameters:
 * 		p: proxy symbol
 *
 * Return: void
 */
void freeProxySymbol(ProxySymbol *p) {
	free(p);
}


/*
 * Returns a pointer to the Symbol of TYPE_KIND defining the type for the
 * given CONST_KIND, FUNC_KIND, PROC_KIND, or VAR_KIND symbol.  Returns
 * NULL for Symbols of TYPE_KIND.
 */
Symbol *
getTypeSym(Symbol *s) 
{
	if (!s) return NULL; 
	switch (s->kind) {
	case CONST_KIND:
		return s->kindPtr.ConstKind->typeSym;
	case PARAM_KIND:
		return s->kindPtr.ParamKind->typeSym;
	case PROC_KIND: 
		/* Procedures do not have associated type symbols */
		return NULL;
	case FUNC_KIND:
		return s->kindPtr.FuncKind->typeSym;
	case TYPE_KIND:
		return s;
	case VAR_KIND:
		return s->kindPtr.VarKind->typeSym;
	default:
		/* NOT REACHED */
		return NULL;
	}
}
