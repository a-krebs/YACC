#ifndef ACTION_CONSTS_H
#define ACTION_CONSTS_H


/*
 * Make a new ProxySymbol with type integer and given value.
 * Return pointer to the proxy
 */
ProxySymbol *proxyIntLiteral(int value);


/*
 * Make a new anonymous symbol with type real and given value.
 * Return a pointer to the hash symbol.
 */
ProxySymbol *proxyRealLiteral(double value);


ProxySymbol *proxyCharLiteral(struct String s);


/*
 * Make a new anonymous symbol with the given string.
 * Return a pointer to the hash symbol.
 */
Symbol *proxyStringLiteral(struct String s);

#endif