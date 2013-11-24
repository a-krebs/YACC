#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ElementArray.h"
#include "Error.h"
#include "ErrorLL.h"
#include "Type.h"
#include "Hash.h"
#include "PreDef.h"
#include "SymbolAll.h"


/*For error reporting*/
extern int yylineno;
extern int colno;
static char *errMsg;
struct Error *e;


/*
 * Return 1 if valid invocation, 0 otherwise.
 */
int isValidProcInvocation(Symbol *s, struct ElementArray *ea)
{
	struct ElementArray *params = NULL;
	Symbol *passedParam, *expectedParam = NULL;
	int i;

	// make sure we're given a proc and not a func
	if (s->kind != PROC_KIND) {
		errMsg = customErrorString("Identifier %s cannot be called "
		    "as a procedure.", s->name);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}

	params = s->kindPtr.ProcKind->params;
	if (!params) {
		// special built-in proc that takes unlimited args
		// TODO for now just assuming all arguments are valid
		return 1;
	} else if (params->nElements != ea->nElements) {
		errMsg = customErrorString("Procedure %s expects %d "
		    "parameters, got %d", s->name, params->nElements,
		    ea->nElements);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;	
	}


	for (i = 0; (i < params->nElements) && (i < ea->nElements); i++) {
		passedParam = (Symbol *) getElementAt(ea, i);
		expectedParam = (Symbol *) getElementAt(params, i);
		if (!areSameType(passedParam, getTypeSym(expectedParam))) {
			errMsg = customErrorString("Procedure %s expects "
			    "argument of type %s at index %d, but got "
			    "argument of type %s", s->name, i,
			    typeToString(getType(expectedParam)),
			    typeToString(getType(passedParam)));
			e = recordError(errMsg, yylineno, colno,
			     SEMANTIC);
			printError(e);
			return 0;
		}
	}
	return 1;
}


Symbol *
isValidFuncInvocation(Symbol *s, struct ElementArray *ea)
{
	struct ElementArray *params = NULL;
	Symbol *passedParam, *expectedParam = NULL;
	int i;

	// make sure we're given a func and not a proc
	if (s->kind != FUNC_KIND) {
		errMsg = customErrorString("Identifier %s cannot be " 			"called as a function.", s->name);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}

	params = s->kindPtr.FuncKind->params;
	if (!params) {
		// special case of predefined-function
		// TODO check what types are acceptable,
		// for now assuming all types
		return getTypeSym(s);
	} else if (params->nElements != ea->nElements) {
		errMsg = customErrorString("Procedure %s expects %d "
		    "parameters, got %d", s->name, params->nElements,
		    ea->nElements);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		printError(e);	
		return NULL;	
	}


	for (i = 0; i < params->nElements; i++) {
		passedParam = (Symbol *) getElementAt(ea, i);
		expectedParam = (Symbol *) getElementAt(params, i);
		if (!areSameType(passedParam, getTypeSym(expectedParam))) {
			errMsg = customErrorString("Procedure %s expects "
			    "argument of type %s at index %d, but got "
			    "argument of type %s", s->name, i,
			    typeToString(getType(expectedParam)),
			    typeToString(getType(passedParam)));
			e = recordError(errMsg, yylineno, colno, SEMANTIC);
			printError(e);
			return NULL;
		}
	}
	return getTypeSym(s);
}


int
isIOProc(Symbol *s) {
	if (!s) return 0;
	if (s->kind != PROC_KIND) return 0;

	if (  (	(strcmp(s->name, "read") == 0)	 	||
	    	(strcmp(s->name, "readln") == 0) 	||
	    	(strcmp(s->name, "write") == 0) 	||
	    	(strcmp(s->name, "writeln") == 0) )	&&
		(s->lvl == 0) ) {
		return 1;
	}
	return 0;

}


int isPreDefFunc(Symbol *s) {
	char *name = NULL;

	if (!s) return 0;
	if (s->kind != FUNC_KIND) return 0;

	name = s->name;

	if ( (	(strcmp(name, "abs") == 0) ||
		(strcmp(name, "sqr") == 0) ||
		(strcmp(name, "sin") == 0) ||
		(strcmp(name, "cos") == 0) ||
		(strcmp(name, "exp") == 0) ||
		(strcmp(name, "ln") == 0) ||
		(strcmp(name, "sqrt") == 0) ||
		(strcmp(name, "arctan") == 0) ||
		(strcmp(name, "trunc") == 0) ||
		(strcmp(name, "round") == 0) ||
		(strcmp(name, "chr") == 0) ||
		(strcmp(name, "odd") == 0) ||
		(strcmp(name, "ord") == 0) ||
		(strcmp(name, "succ") == 0) ||
		(strcmp(name, "pred") == 0) ) &&
			s->lvl == 0) {
	   	return 1;
	}
	return 0;
}


int
isValidIOProcInvocation(Symbol *s, struct ElementArray *ea)
{
	Symbol *param = NULL;
	type_t type;
	int i, nArgs, valid = 1;

	nArgs = ea->nElements;

	if (!nArgs) {
		errMsg = customErrorString("Procedure %s cannot be "
		    "called without any arguments.", s->name);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}

	for (i = 0; i < nArgs; i++) {
		param = getElementAt(ea, i);
		type = getType(param);
		if ( (type != CHAR_T) && (type != INTEGER_T) &&
		    (type != REAL_T) && (type != STRING_T) ) {
			errMsg = customErrorString("Invalid argument "
			    "of type %s passed to procedure %s.",
			    typeToString(type), s->name);
			recordError(errMsg, yylineno, colno, SEMANTIC);
			valid = 0;
		}
	}
	if (!valid) return 0;
	return 1;
}


ProxySymbol *isValidPreDefFuncInvocation(Symbol *s, struct ElementArray *ea)
{
	Symbol *param = NULL;
	type_t type;
	int i = 0;
	int nArgs = 0;

	nArgs = ea->nElements;

	// check argument count
	if (nArgs != 1) {
		errMsg = customErrorString("Function %s expected "
		    "1 argument but %d given.", s->name, nArgs);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}
	
	param = getElementAt(ea, i);
	type = getType(param);
	
	if (typeIsInValidArgs(s, type)) {
		return getPreDefFuncReturnType(s, type);
			
	} else {
		errMsg = customErrorString("Function %s cannot be "
		    "called with argument of type %s.", s->name,
		    typeToString(type));
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}
}


Symbol *getPreDefFuncReturnType(Symbol *s, type_t argType) {
	char *name = NULL;
	
	if (!s) return NULL;

	name = s->name;

	if (
	    (strcmp(name, "abs") == 0) ||
	    (strcmp(name, "sqr") == 0) ||
	    (strcmp(name, "succ") == 0) ||
	    (strcmp(name, "pred") == 0)
	) {
		return getTypeSym(s);
	} else if (
	    (strcmp(name, "sin") == 0) ||
	    (strcmp(name, "cos") == 0) ||
	    (strcmp(name, "exp") == 0) ||
	    (strcmp(name, "ln") == 0) ||
	    (strcmp(name, "sqrt") == 0) ||
	    (strcmp(name, "arctan") == 0)
	) {
		return getPreDefReal(preDefTypeSymbols);
	} else if (
	    (strcmp(name, "trunc") == 0) ||
	    (strcmp(name, "round") == 0) ||
	    (strcmp(name, "ord") == 0)
	){
		return getPreDefInt(preDefTypeSymbols);
	} else if (
	    (strcmp(name, "chr") == 0)
	){
		return getPreDefChar(preDefTypeSymbols);
	} else if (
	    (strcmp(name, "odd") == 0)
	){
		return getPreDefBool(preDefTypeSymbols);
	}
	return NULL;
}


Symbol *
paramToVar(Symbol * param)
{
	if (!param) return NULL;
	if (param->kind != PARAM_KIND) return NULL;
	Symbol *typeSym = getTypeSym(param);
	return newVariableSym(param->name, typeSym);
}
