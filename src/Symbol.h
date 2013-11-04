#ifndef SYMBOL_H
#define SYMBOL_H

#include "Type.h"
#include "Kind.h"

Symbol *newArraySym(int, char *, Symbol *, Symbol *);
Symbol *newAnonArraySym(int, Symbol *, Symbol *);
Symbol *newConstSym(int, char *, Symbol *);
Symbol *newConstSymFromType(int, Type, type_t);
Symbol *newSubrangeSym(int, Symbol *, Symbol *);
Symbol *newVariableSym(int, char *, Symbol *);
Symbol *newProcedureSym(int, char *, struct ParamArray *);
struct Param *newParameter(char *, Symbol *);
#endif
