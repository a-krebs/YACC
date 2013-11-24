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


void
setSymbolName(Symbol *s, char *id)
{
	size_t len;
	if (id == NULL) {
		s->name = NULL;
		return;
	}
	
	len = strlen(id) + 1;
	s->name = calloc(1, sizeof(char)*len);
	if (!s->name) {
		err(1, "Failed to allocate memory for symbol name!");
		exit(EXIT_FAILURE);
	}
	strcpy(s->name, id);
}


/* Creates a new symbol. Auto-determines all substructures
 * based on the parameter kind.
 *
 * Does not insert into the symbol table, use createAndInsertSymbol for that.
 *
 * Parameters:
 * 		table: the symbol table from which to get lexical level
 *              id: name of symbol
 *		kind: kind of symbol. Comes from kind_t enum
 *		typeOriginator: flag for if type originator 
 *
 * Return: Newly created symbol.
 */
Symbol *createSymbol(
    struct hash *table, char *id, kind_t kind, int typeOriginator)
{
	Symbol *symbol = allocateSymbol();

	if (symbol == NULL) {
		err(1, "Could not create new symbol.");
		exit(EXIT_FAILURE);			
	}

	// set symbol independent values
	setSymbolName(symbol, id);

	symbol->kind = kind;
	allocateKindPtr(symbol);
	
	symbol->lvl = getCurrentLexLevel(table);
	symbol->typeOriginator = typeOriginator;
	symbol->next = NULL;

	return symbol;
}


/* Allocates memeory for a struct symbol and only a struct symbol.
 *
 * Parameters:
 *
 * Return: Pointer to newly allocated memory chunk
 */
Symbol *allocateSymbol() {
	Symbol *symbol = NULL;

	symbol = calloc(1, sizeof(Symbol));
	if ( symbol == NULL ) {
		err(1, "Could not alloc memory for symbol.");
		exit(EXIT_FAILURE);		
	}

	return symbol;
}

