#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Definitions.h"
#include "ElementArray.h"
#include "Error.h"
#include "Globals.h"
#include "Hash.h"
#include "PreDef.h"
#include "Type.h"
#include "SymbolAll.h"
#include "Utils.h"
#include "ActionsAll.h"

#ifndef TESTBUILD
#include "parser.tab.h"	/* token definitions used in operator compat checks */
#endif
#ifdef TESTBUILD
#include "tokens.h"
#endif

/*For error reporting:*/
// extern int yylineno;
// extern int colno;
// static char *errMsg;


/*
 * Make a new ProxySymbol with type integer and given value.
 * Return pointer to the proxy
 */
ProxySymbol *proxyIntLiteral(int value) {
	Symbol *integerType = getPreDefInt(preDefTypeSymbols);
	/* anonymous, so NULL id */
	return newConstProxySym(NULL, &value, integerType); 
}
	
	
/*
 * Make a new anonymous symbol with type real and given value.
 * Return a pointer to the hash symbol.
 */
ProxySymbol *proxyRealLiteral(double value) {
	Symbol *realType = getPreDefReal(preDefTypeSymbols);
	/* anonymous, so NULL id */
	return newConstProxySym(NULL, &value, realType);
}


ProxySymbol *proxyCharLiteral(struct String s) {
	Symbol *charType = getPreDefChar(preDefTypeSymbols);
	/* anonymous, so NULL id */
	return newConstProxySym(NULL, s.str, charType);
}


/*
 * Make a new anonymous symbol with the given string.
 * Return a pointer to the hash symbol.
 */
Symbol *proxyStringLiteral(struct String s) {
	Symbol *typeSym;
	ProxySymbol *proxy;
	int lvl = getCurrentLexLevel(symbolTable);
	proxy= newStringProxySym(lvl, (s.str+1), s.strlen);
	typeSym = newStringTypeSym(s.strlen);
	createHashElement(symbolTable, NULL, typeSym);
	setInnerTypeSymbol(proxy, typeSym);
	return proxy;
}
