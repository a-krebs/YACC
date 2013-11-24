#ifndef SYMBOL_INVOC_H
#define SYMBOL_INVOC_H


/*
 * Return 1 if valid invocation, 0 otherwise.
 */
int isValidProcInvocation(Symbol *s, struct ElementArray *ea);

Symbol *
isValidFuncInvocation(Symbol *s, struct ElementArray *ea);

int isIOProc(Symbol *s);

int isPreDefFunc(Symbol *s);


int isValidIOProcInvocation(Symbol *s, struct ElementArray *ea);


ProxySymbol *isValidPreDefFuncInvocation(Symbol *s, struct ElementArray *ea);


Symbol *getPreDefFuncReturnType(Symbol *s, type_t argType);


Symbol *paramToVar(Symbol * param);


#endif