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
struct Symbol {
	char *name;	/* the name associated with the entry */
	kind_t kind;	/* the kind associated with this entry */
	type_t type;	/* the type associated with the kind of this entry */
	Type typePtr;	/* pointer to the type associated with kind of entry */	
	int lvl;	/* the lexical level at which the entry is defined */	
};

struct Symbol *newArraySym(int, char *, struct Symbol *, struct Symbol *);
struct Symbol *newConstSym(int, char *, struct Symbol *);
struct Symbol *newConstSymFromType(int, Type, type_t);
struct Symbol *newSubrangeSym(int, struct Symbol *, struct Symbol *);
struct Symbol *newVariableSym(int, char *, struct Symbol *);
struct Symbol *newProcedureSym(int, char *, struct ParamArray *);
struct Param *newParameter(char *, struct Symbol *);
#endif
