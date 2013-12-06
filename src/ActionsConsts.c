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
#include "Emit.h"
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
extern int yylineno;
extern int colno;
static char *errMsg;


/*
 * Make a new ProxySymbol with type integer and given value.
 * Return pointer to the proxy
 */
ProxySymbol *proxyIntLiteral(long int value) {
	Symbol *newConstProxy = NULL;
	int intValue = 0;

	/* check that value is within range before casting it to int */
	if (value > ASC_MAX_INT || value < -ASC_MAX_INT) {
		errMsg = customErrorString("%ld is larger than maxint, "
		    "which is: %d", value, ASC_MAX_INT);
		recordError(errMsg, yylineno, colno, SEMANTIC);
	}

	/* convert to int */
	intValue = value;

	/* Create symbol. Anonymous, so NULL id */
	Symbol *integerType = getPreDefInt(preDefTypeSymbols);
	newConstProxy =  newConstProxySym(NULL, &intValue, integerType);

//	emitPushAnonConstValue(newConstProxy);
	return newConstProxy; 
}
	
	
/*
 * Make a new anonymous symbol with type real and given value.
 * Return a pointer to the hash symbol.
 */
ProxySymbol *proxyRealLiteral(double value) {
	Symbol *realType = getPreDefReal(preDefTypeSymbols);
	Symbol *newConstProxy = NULL;
	/* anonymous, so NULL id */
	newConstProxy =  newConstProxySym(NULL, &value, realType);
//	emitPushAnonConstValue(newConstProxy);
	return newConstProxy;
}


ProxySymbol *proxyCharLiteral(struct String s) {
	Symbol *charType = getPreDefChar(preDefTypeSymbols);
	Symbol *newConstProxy = NULL;

	newConstProxy = newConstProxySym(NULL, s.str, charType);
//	emitPushAnonConstValue(newConstProxy);
	return newConstProxy;
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
	proxy = newConstProxySym(NULL, &s, typeSym);

	/* add the type to the symbol table */
	addToSymbolTable(symbolTable, typeSym);

//	emitPushAnonConstValue(proxy);

	return proxy;
}

