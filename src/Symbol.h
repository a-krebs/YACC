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
Symbol *newProcedureSym(int, char *, struct ElementArray *);
Symbol *newParamSym(int, char *, Symbol *);


/* Symbol creation from ProxySymbol functions */
Symbol *newConstSymFromProxy(int, char *, ProxySymbol *);

/* ProxySymbol creations functions */
/* 
 * No creation functions for Char and String as they cannot be the result
 * of operations
 */
ProxySymbol *newConstProxySym(void *, Symbol *); 
/* Utility functions */
Symbol *getTypeSym(Symbol *);
void setSymbolName(Symbol *, char *);

struct Param *newParameter(char *, Symbol *);
#endif
