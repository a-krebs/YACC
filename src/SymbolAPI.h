#ifndef SYMBOL_API_H
#define SYMBOL_API_H


/* Creates const kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createConstSymbol(char *id);


/* Creates func kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createFuncSymbol(char *id);


/* Creates Param kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createParamSymbol(char *id);


/* Creates proc kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createProcSymbol(char *id);


/* Creates var kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createVarSymbol(char *id);


/* Creates type kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *		typeOriginator: flag for if type originator 
 *
 * Return: Newly created symbol
 */
Symbol *createTypeSymbol(char *id, int typeOriginator);


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
    struct hash *table, char *key, kind_t kind, int typeOriginator);


/*
 * Returns a pointer to the Symbol of TYPE_KIND defining the type for the
 * given CONST_KIND, FUNC_KIND, PROC_KIND, or VAR_KIND symbol.  Returns
 * NULL for Symbols of TYPE_KIND.
 */
Symbol *
getTypeSym(Symbol *s);


/*
 * Returns a pointer to the type symbol defining the base type for the given
 * subrange symbol.
 */
Symbol *
getSubrangeBaseTypeSym(Symbol *sr);

/*
 * Returns 1 if the symbol (which is kind PARAM_KIND or VAR_KIND) has been
 * passed by reference (e.g., the byRef flag in its kindPtr is set)
 * Parameters
 *		s: the symbol for which we would are inquiring if it has been
 *		    passed by reference
 * Return: 1 if the conditions above are met, 0 if not	
 */
int isByReference(Symbol *);

/*
 * Checks whehter the given CONST_KIND symbol is a result of 
 * constant calculation or not.
 *
 * Parameters:
 *		ProxySymbol *s: MUST BE a CONST_KIND symbol !!!
 *	
 * Returns:  1: It is a result of const calculation.
 *			0: It is not.
 */
int isConstResultSym(ProxySymbol *);

/* 
 * set the constResult flag to 1 
 * 
 * Parameters:
 *		ProxySymbol *s: MUST BE a CONST_KIND symbol !!!
 */
void setConstResultFlag(ProxySymbol *);

void freeProxySymbol(ProxySymbol *p);

/*
 * Adds the given symbol to the symbol table supplied.
 *
 * This is a wrapper around createHashElement that also sets the
 * symbols size, since when we add to the hash table we know all the elements
 * needed to set the size.
 *      
 * Parameters: 
 *              table: hash table for element to be created in
 *              symbol: pointer to symbol to add to hash table.
 *
 * Returns: 0 on success 
 *         1 current lex level and symbol's lex level differ
 *         2 element on hash table has symbol set to NULL
 *         3 element's symbol list head lex level same as symbol's
 *         4 symbol's lex level lower than element's symbol list head    
 *         5 could not create a name for null key
*/
int addToSymbolTable(struct hash *table, Symbol *symbol);


#endif
