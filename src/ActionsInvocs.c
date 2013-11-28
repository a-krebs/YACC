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
extern int yylineno;
extern int colno;
static char *errMsg;


/*
 * Invoke procedure with given name.
 *
 * The argument ea contains a list of arguments.
 */
void procInvok(char *id, struct ElementArray *ea) {
	Symbol *s = NULL;
	s = getGlobalSymbol(symbolTable, id);
	if (!s) {
		notDefinedError(id);
		return;
	}
	if (!ea) {
		ea = newElementArray();
	}

	if (isIOProc(s)) {
		isValidIOProcInvocation(s, ea);
	} else {
		// this prints errors, so call it but ignore return value
		isValidProcInvocation(s, ea);
	}
}


/*
 * Invoke function with the given name.
 *
 * The argument argv contains a list of arguments.
 *
 * Return a ProxySymbol containing the type returned.
 */
ProxySymbol *funcInvok(char *id, struct ElementArray *argv) {
	Symbol *s = NULL;
	s = getGlobalSymbol(symbolTable, id);
	if (!s) {
		notDefinedError(id);
		return NULL;
	}

	if (!argv) {
		argv = newElementArray();
	}

	if (isPreDefFunc(s)) {
		return isValidPreDefFuncInvocation(s, argv);
	}

	if (isValidFuncInvocation(s, argv)) {
		return getTypeSym(s);
	}

	return NULL;
}


/*
 * Create an argument list for function and procedure invocation.
 *
 * Return a pointer to a ProxySymbol containing the list.
 */
struct ElementArray *createArgList(Symbol *arg) {
	struct ElementArray * ea = NULL;

	if (!arg) {
		/* ERROR */
		return NULL;
	}

	// check that arg is not a procedure or function
	if (	(arg->kind == PROC_KIND) || 
		(arg->kind == FUNC_KIND) ||
		(arg->kind == PARAM_KIND)
	){
		errMsg = customErrorString("Invaid argument type.");
		recordError(errMsg, yylineno, colno, SEMANTIC);
	}
	ea = newElementArray();
	growElementArray(ea);
	appendElement(ea, getTypeSym(arg));	
	return ea;
}


/*
 * Concatenate two lists of arguments, maintaining order.
 *
 * Return a pointer to a list containing both sets of arguments.
 * Whether to add the arguments to one of the lists or two make a third
 * list and add all arguments is up to implementation.
 */
struct ElementArray *concatArgLists(
    struct ElementArray *arr1, struct ElementArray *arr2) {
	
	struct ElementArray *ea;
	if ((!arr1) && (!arr2)) return NULL;
	if (!arr1) return arr2;
	if (!arr2) return arr1;

	ea = appendElementArray(arr1, arr2);
	return ea;
}
