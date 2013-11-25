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

/*
 * Sets the size (i.e., the number of ASC memory units occupied by) the given
 * symbol.  In appropriate cases, it calculates the size of the given symbol
 * and then correctly sets the value.
 * Parameters:
 *		s: the symbol whose size is to be set
 */
void setSymbolSize(Symbol *);

/*
 * Sets the given Symbol's offset appropriate and increments the offset
 * value in the symbol table for the current lexical level.
 * Parameter:
 * 		s: the symbol whose offset value is to be set
 */
void setSymbolOffset(Symbol *);

#endif
