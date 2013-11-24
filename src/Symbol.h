#ifndef SYMBOL_H
#define SYMBOL_H

#include "Definitions.h"
#include "Kind.h"
/* Symbol creation function */
Symbol *newTypeSymFromSym(char *, Symbol *);
Symbol *newAnonArraySym(Symbol *, Symbol *);
Symbol *newConstSym(int, char *, Symbol *);
Symbol *newConstSymFromType(int, Type, type_t);
Symbol *newSubrangeSym(Symbol *, Symbol *);
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

/* */
Symbol * paramToVar(int, Symbol *);
/* Utility functions */
Symbol *getTypeSym(Symbol *);
Symbol *getArrayIndexSym(Symbol *);
Symbol *getArrayBaseSym(Symbol *);
Symbol *getSubrangeBaseTypeSym(Symbol *);
int getArrayDim(Symbol *s);
int getSymbolListLength(Symbol *s);
void setSymbolName(Symbol *, char *);
Symbol * getArrayTerminalTypeSym(Symbol *);

/* Semantic validation functions */
int isConstInScalar(Symbol *, Symbol *);
int isValidProcInvocation(Symbol *, struct ElementArray *);
int isElementArraySimple(struct ElementArray *elementArray);
int isValidIOProcInvocation(Symbol *, struct ElementArray *);
int isIOProc(Symbol *);

int typeIsInValidArgs(Symbol *, type_t);
Symbol *getPreDefFuncReturnType(Symbol*, type_t);
ProxySymbol *isValidPreDefFuncInvocation(Symbol *, struct ElementArray*);
int isPreDefFunc(Symbol*);

Symbol * isValidFuncInvocation(Symbol *, struct ElementArray *);
Symbol * isValidArrayAccess(Symbol *, ProxySymbol *);

struct Param *newParameter(char *, Symbol *);

/* functios for working with records */
Symbol *newRecordTypeSym(int, char*);
int addFieldToRecord(Symbol*, ProxySymbol*);
void freeProxySymbol(ProxySymbol*);

/*api functions*/
Symbol *createSymbol(struct hash*, char *id, kind_t kind, int typeOriginator);
Symbol *allocateSymbol();
Symbol *createAndInsertSymbol(
    struct hash*, char *key, kind_t kind, int typeOriginator);
Symbol *createConstSymbol(char *id);
Symbol *createFuncSymbol(char *id);
Symbol *createParamSymbol(char *id);
Symbol *createProcSymbol(char *id);
Symbol *createVarSymbol(char *id);
Symbol *createTypeSymbol(char *id, int typeOriginator);

/* symbol creation for type-specific stuff */
Symbol *createArrayTypeSymbol(
    char *id, int typeOriginator, Symbol *base, Symbol*index);


/*no idea...*/
Symbol *
newStringTypeSym(int lexLevel, int strlen);
#endif
