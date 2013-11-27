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
 * Each string constant gets a new type symbol that carries the string length
 * around.
 *
 * Parameters:
 * 	s: a String struct with the string length and a char* to the string
 *
 * Return:
 * 	a pointer to the hash symbol with kind CONST_KIND
 */
Symbol *proxyStringLiteral(struct String s) {
	Symbol *typeSym = NULL;
	ProxySymbol *proxy = NULL;

	/* make a new type */
	typeSym = newStringTypeSym(s.strlen);

	/* make the constant proxy symbol */
	proxy = newStringProxySym(s.str, s.strlen, typeSym);

	/* add the type to the symbol table */
	createHashElement(symbolTable, NULL, typeSym);

	return proxy;
}
