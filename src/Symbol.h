#ifndef SYMBOL_H
#define SYMBOL_H

#include "Type.h"
#include "Kind.h"

/*
 * The object stored at a hash element in the symbol table.
 * Here we define the name of the entry, what kind it is (e.g., VAR, CONST,
 * PARAM, ... ), and a pointer to the particular type of kind it is. 
 * We also have type and typePtr here as well because EVERY entry will have
 * these fields.
 */
typedef struct symbol_t {
	char *name;	/* the name associated with the entry */
	kind_t kind;	/* the kind associated with this entry */
	type_t type;	/* the type associated with the kind of this entry */
	Type typePtr;	/* pointer to the type associated with kind of entry */	
	struct symbol_t *typeSym;/*the symbol describing the type of the Symbol */
	int lvl;	/* the lexical level at which the entry is defined */	
} Symbol;

/* 
 * Type to hold same information as Symbol, but is
 * never stored in the symbol table.
 */
typedef Symbol ProxySymbol;

Symbol *newArraySym(int, char *, Symbol *, Symbol *);
Symbol *newConstSym(int, char *, Symbol *);
Symbol *newConstSymFromType(int, Type, type_t);
Symbol *newSubrangeSym(int, Symbol *, Symbol *);
Symbol *newVariableSym(int, char *, Symbol *);
Symbol *newProcedureSym(int, char *, struct ParamArray *);
struct Param *newParameter(char *, Symbol *);
#endif
