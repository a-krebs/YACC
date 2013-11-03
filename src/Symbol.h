#ifndef SYMBOL_H
#define SYMBOL_H

#include "Type.h"
#include "Kind.h"
struct Symbol *newArraySymFromSym(int, char *, struct Symbol *);
struct Symbol *newAnonArraySym(int, struct Symbol *, struct Symbol *);
struct Symbol *newConstSym(int, char *, struct Symbol *);
struct Symbol *newConstSymFromType(int, Type, type_t);
struct Symbol *newSubrangeSym(int, struct Symbol *, struct Symbol *);
struct Symbol *newVariableSym(int, char *, struct Symbol *);
struct Symbol *newProcedureSym(int, char *, struct ParamArray *);
struct Param *newParameter(char *, struct Symbol *);
#endif
