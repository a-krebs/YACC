#ifndef SYMBOL_H
#define SYMBOL_H

#include "Definitions.h"

/* Symbol creation function */
Symbol *newArraySym(int, char *, Symbol *, Symbol *);
Symbol *newAnonArraySym(int, Symbol *, Symbol *);
Symbol *newConstSym(int, char *, Symbol *);
Symbol *newConstSymFromType(int, Type, type_t);
Symbol *newSubrangeSym(int, Symbol *, Symbol *);
Symbol *newVariableSym(int, char *, Symbol *);
Symbol *newProcedureSym(int, char *, struct ParamArray *);

/* Utility functions */
Symbol *getTypeSym(Symbol *);

struct Param *newParameter(char *, Symbol *);
#endif
