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
Symbol *newFuncSym(int, char *, Symbol *, struct ElementArray *);
Symbol *newProcSym(int, char *, struct ElementArray *);
Symbol *newAnonScalarSym(int, struct ElementArray *);


/* Symbol creation from ProxySymbol functions */
Symbol *newConstSymFromProxy(int, char *, ProxySymbol *);

/* ProxySymbol creations functions */
ProxySymbol *newConstProxySym(void *, Symbol *); 
ProxySymbol *newStringProxySym(int, char *, int);
ProxySymbol *newProxySymFromSym(Symbol *);

/* Utility functions */
Symbol *getTypeSym(Symbol *);
Symbol *getArrayIndexSym(Symbol *);
Symbol *getArrayBaseSym(Symbol *);
Symbol *getSubrangeBaseTypeSym(Symbol *);
int getArrayDim(Symbol *s);
int getSymbolListLength(Symbol *s);
void setSymbolName(Symbol *, char *);


/* Semantic validation functions */
int isConstInScalar(Symbol *, Symbol *);
int isValidProcInvocation(Symbol *, struct ElementArray *);

Symbol * isValidFuncInvocation(Symbol *, struct ElementArray *);
Symbol * isValidArrayAccess(Symbol *, ProxySymbol *);


struct Param *newParameter(char *, Symbol *);
#endif
