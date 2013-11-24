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


/* Creates and inserts a symbol into the symbol table
 *
 * Parameters:
 * 		table: the symbol table into which to insert
 *              id: name of symbol
 *		kind: kind of symbol. Comes from kind_t enum
 *		typeOriginator: flag for if type originator 
 *
 * Return: a pointer to the created symbol
 */
Symbol *createAndInsertSymbol(
    struct hash *table, char *key, kind_t kind, int typeOriginator)
{
	Symbol *symbol = createSymbol(table, key, kind, typeOriginator);

	if (symbol == NULL) {
		err(1, "Could not create symbol.");
		exit(EXIT_FAILURE);
	}

	if (createHashElement(table, key, symbol) != 0) {
		err(1, "Could not insert into symbol table.");
		exit(EXIT_FAILURE);
	}

	return symbol;
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


/*
 * Returns a pointer to the type symbol defining the base type for the given
 * subrange symbol.
 */
Symbol *
getSubrangeBaseTypeSym(Symbol *sr) {
	if (!sr) return NULL;
	if (getType(sr) != SUBRANGE_T) return NULL;
	return getTypePtr(sr)->Subrange->baseTypeSym;

}


void freeProxySymbol(ProxySymbol *p) {
	free(p);
}
