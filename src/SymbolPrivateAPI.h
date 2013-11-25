#ifndef SYMBOL_PRIVATE_H
#define SYMBOL_PRIVATE_h


/* Set the name of the passed symbol
 *
 * Parameters:
 * 		s: symbol to be named
 *		id: name of symbole
 *
 * Return: void
 */
void setSymbolName(Symbol *s, char *id);


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
    struct hash *table, char *id, kind_t kind, int typeOriginator);


/* Allocates memeory for a struct symbol and only a struct symbol.
 *
 * Parameters:
 *
 * Return: Pointer to newly allocated memory chunk
 */
Symbol *allocateSymbol();    


#endif
