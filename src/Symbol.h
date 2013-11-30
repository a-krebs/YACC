#ifndef SYMBOL_H
#define SYMBOL_H

#include "Definitions.h"
#include "Kind.h"

/*
 * Create a new type symbol for an array type.
 *
 * Parameters:
 * 	id: the type's name
 * 	typeOriginator: typeOriginator flag
 * 	base: the array base type
 * 	index: the array index type
 *
 * Return:
 * 	Return a pointer to the new symbol.
 */
Symbol *createArrayTypeSymbol(
   char *id, int typeOriginator, Symbol *base, Symbol *index);


/*
 * Create a new type symbol for a scalar list type.
 *
 * Parameters:
 * 	id: the type's name
 * 	typeOriginator: typeOriginator flag
 * 	scalars: the list of constants that are part of this type
 *
 * Return:
 * 	A pointer to the new symbol
 */
Symbol *createScalarListTypeSymbol(
    char *id, int typeOriginator, struct ElementArray *scalars);


/* Creates a varable symbol ands the inner type symbol. 
 *
 * Parameters:
 *              id: name of symbol
 *		typeSym: type symbol to be put in new var symbol
 *
 * Return: Newly created symbol
 */
Symbol *
newVariableSym(char *id, Symbol* typeSym);


/* Creates a parameter symbol and sets the inner type symbol
 *
 * Parameters:
 *              id: name of symbol
 *		typeSym: type symbol to be put in new var symbol
 *
 * Return: Newly created symbol
 */
Symbol *
newParamSym(char *id, Symbol *typeSym);


/* Creates a procedure symbol 
 *
 * Parameters:
 *              id: name of symbol
 *				ea: element of parameters to procdure
 *
 * Return: Newly created symbol
 */
Symbol *
newProcSym(char *id, struct ElementArray *ea);


/* Creates a fucntion symbol and sets the inner type symbol
 *
 * Parameters:
 *              id: name of symbol
 *		typeSym: type symbol to be put in new var symbol
 *
 * Return: Newly created symbol
 */
Symbol *
newFuncSym(int lvl, char *id, Symbol *typeSym, struct ElementArray *ea);


/*
 * Create a new symbol for a record type defintion to be added to the symbol
 * table.
 * 
 * Parameters:
 *              id: name of symbol
 *
 * Return a pointer to the new type symbol.
 */
Symbol *newRecordTypeSym(char *id);


 /*
 * Constructs an anonymous subrange symbol.
 * 
 * Parameters:
 *              constSymLow: pointer to symbol holding lower bound info
 *              constSymHigh: pointer to symbol holding uppper bound info
 *
 * Return a pointer to the new subrange symbol.
 */
Symbol *
newSubrangeSym(ProxySymbol *constSymLow, ProxySymbol *constSymHigh);


/*
 * Constructs a	named type symbol given a ptr to another type symbol.
 * (so the new symbol will either be constructed from an anonymous type symbol
 * or be a copy of another named symbol)
 *
 * Lexical level is NOT set, and symbol is NOT inserted into symbol table.
 *
 * Parameters:
 * 	id: name of created symbol
 * 	typeSym: symbol from which type is to be taken. Must be TYPE_KIND
 *
 * Returns: pointer to created symbol, or NULL on error
 *
 */
Symbol *newTypeSymFromSym(char *id, Symbol *typeSym);


/*
 * Creates a new anonymous array type symbol given a pointer to a symbol
 * defining the base type and a pointer to a symbol defining the index type.
 *
 * Parameters:
 * 	baseTypeSym: the symbol for the base type. Should be TYPE_KIND
 * 	indexTypeSym: the symbol for the index type. Should be TYPE_KIND
 *
 * Return:
 * 	pointer to new symbol with kind TYPE_KIND and kindPtr type ARRAY_T
 */
Symbol *newAnonArraySym(Symbol *baseTypeSym, Symbol *indexTypeSym);


/*
 * Create a new symbol for an anonymous scalar list type.
 *
 * Parameters:
 * 	ea: the list of scalars that are part of this list
 *
 * Return:
 * 	a symbol to the new type.
 */
Symbol *newAnonScalarListTypeSym(struct ElementArray *ea);


Symbol *
newStringTypeSym(int strlen);


/*
 * Determines if the given symbol is a const which appears in the given
 * symbol of kind TYPE_KIND and type SCALAR_T
 * Why checking by name and lexical level is enough: each identifier
 * only appears once per scope.  If def hidden later, lvl is enough
 * to tell us that the id no longer refers to a const inside the
 * scalar list.
 */
int
isConstInScalar(Symbol *constSym, Symbol *scalarSym);

/*
 * Sets the given Symbol's offset as appropriate and increments the offset
 * value in the symbol table for the current lexical level.
 * Parameter:
 * 		s: the symbol whose offset value is to be set
 *		table : the symbol table in which the symbol s resides
 */
void setSymbolOffset(Symbol *, struct hash *);

/*
 * Sets the offset of the given Symbol which is of kind VAR_KIND derived from 
 * a Symbol of PARAM_KIND. 
 * Parameters:
 *		s: the symbol whose offset value is to be calculated
 * 		params: the array of parameters for the proc/func to which
 *		    s belongs
 */
void setParamOffset(Symbol *, struct ElementArray *);

#endif
