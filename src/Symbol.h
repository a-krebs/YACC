#ifndef SYMBOL_H
#define SYMBOL_H

#include "Definitions.h"
#include "Kind.h"
/* Symbol creation function */
Symbol *newTypeSymFromSym(int, char *, Symbol *);
Symbol *newAnonArraySym(int, Symbol *, Symbol *);
Symbol *newConstSym(int, char *, Symbol *);
Symbol *newConstSymFromType(int, Type, type_t);
Symbol *newSubrangeSym(int, Symbol *, Symbol *);
Symbol *newVariableSym(int, char *, Symbol *);
Symbol *newProcedureSym(int, char *, struct ParamArray *);

/* Symbol creation from ProxySymbol functions */
Symbol *newConstSymFromProxy(int, char *, ProxySymbol *);


/* Utility functions */
Symbol *getTypeSym(Symbol *);
void setSymbolName(Symbol *, char *);

struct Param *newParameter(char *, Symbol *);
#endif
