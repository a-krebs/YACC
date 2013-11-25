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


/* Checks each memeber of the passed ElementArray to see if each
 * memeber is of simple type.
 *
 * Parameters:
 *              elementArray: elementArray passed
 *
 * Return: Boolean: 1 if elemetn array is simple
 *		    0 if not
 */
int isElementArraySimple(struct ElementArray *elementArray);


int typeIsInValidArgs(Symbol *s, type_t type);


#endif
