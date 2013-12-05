#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Definitions.h"
#include "ElementArray.h"
#include "Error.h"
#include "Globals.h"
#include "Hash.h"
#include "Emit.h"
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
 * The argument ea contains a list of arguments (i.e., expression nodes).
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
		/* We can spit out proc invocations as soon as we see them as
		 * they cannot be part of expressions */	
		emitProcInvok(s, ea);
	}

}


/*
 * Invoke function with the given name.
 *
 * The argument argv contains a list of arguments.
 *
 * Return a treeNode struct. 
 */
struct treeNode *funcInvok(char *id, struct ElementArray *argv) {
	struct treeNode *funcNode;
	Symbol *s = NULL, *newNodeSym;
	s = getGlobalSymbol(symbolTable, id);
	
	if (!s) {
		notDefinedError(id);
		return createLeafNode(NULL);
	}

	if (!argv) {
		argv = newElementArray();
	}

	if (isPreDefFunc(s)) {
		/* Needs to be handled separately */
		return createLeafNode(isValidPreDefFuncInvocation(s, argv));
	}

	if (isValidFuncInvocation(s, argv)) {
		newNodeSym = newFuncSym(s->lvl, s->name, getTypeSym(s), argv);
		newNodeSym->kindPtr.FuncKind->label = s->kindPtr.FuncKind->label;
		funcNode = createLeafNode(newNodeSym);
		funcNode->opToken = FUNCTION_INVOCATION;
		return funcNode;	
	}

	return createLeafNode(NULL);
}


/*
 * Create an argument list for function and procedure invocation.
 *
 * Return a pointer to a ProxySymbol containing the list.
 */
struct ElementArray *createArgList(struct treeNode *arg) {
	struct ElementArray * ea = NULL;
	
	if (!arg) {
		/* ERROR */
		return NULL;
	}

	if (!(arg->symbol)) return NULL;

	if (	(arg->symbol->kind == PROC_KIND) || 
		(arg->symbol->kind == FUNC_KIND) ||
		(arg->symbol->kind == PARAM_KIND)
	){
		errMsg = customErrorString("Invaid argument type.");
		recordError(errMsg, yylineno, colno, SEMANTIC);
	}

	ea = newElementArray();
	growElementArray(ea);
	appendElement(ea, arg);	
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
