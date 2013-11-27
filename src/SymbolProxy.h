#ifndef SYMBOL_PROXY_H
#define SYMBOL_PROXY_H

ProxySymbol *
newProxySymFromSym(Symbol *s);


/*
 * Creates a new CONST_KIND ProxySymbol.
 *
 * Parameters:
 * 	id: the 
 * 	result: a pointer to the value for the new constant
 * 		this will be case to the appropriate C type depending on typeSym
 * 	tpyeSym: a symbol with kind TYPE_KIND for the new symbol
 *
 * Return:
 * 	A pointer to the new ProxySymbol
 */
ProxySymbol *newConstProxySym(char *id, void * result, Symbol *typeSym);


/*
 * TODO: proxy symbol will have kindPtr to pre-defined kind?
 */
// TODO this looks like a dup of newConstProxySym?
Symbol * newConstSymFromProxy(int lvl, char * id, ProxySymbol * proxySym);


ProxySymbol * newStringProxySym(char *str, int strlen, Symbol *type);

#endif
