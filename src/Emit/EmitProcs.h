/*
 * Module implementing functions generating asc code for 
 * procedures and functions.
 */
#ifndef EMITPROCS_H
#define EMITPROCS_H

#include <err.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../Error.h"
#include "../Definitions.h"
#include "../Kind.h"
#include "../StmtLL.h"
#include "../SymbolAPI.h"
 #include "../SymbolAll.h"
#include "../Type.h"
#include "../ElementArray.h"
#include "../Hash.h"

#include "EmitUtils.h"
#include "EmitExprs.h"

extern int doNotEmit;


void emitPushParamValue(Symbol *, int);
/*
 * Emit code to push local procedure/function parameters onto the
 * the stack.
 *
 * Parameters: 	param: parameter symbol
 *				paramNum: the parameter's position number in the 
 *					parameter list.
 * 	
 * Returns: void
 */
void emitProcOrFuncDecl(Symbol *symbol, struct ElementArray *ea);


/*
 * Emit code to end a procedure.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitEndProc(Symbol *symbol);


/*
 * Emit code to end a functions. 
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitEndFunc(Symbol *symbol) ;


/*
 * Emit code to end a procedure/function. Adjusts for any local variables
 * and returns.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitProcOrFuncEndCommon(Symbol *symbol, char *msg);


/*
 * Creates a label for procedure/function. Label would have form
 * symbolName_currentStackNumber.
 *
 * I fully realize this function was coded as stupid...
 *
 * Parameters: symbol: procedure/function symbol to create label for.
 * 	
 * Returns: generated label
 */
char *createProcOrFunctionLabel(Symbol *symbol);


/*
 * Emit code to invoce procedure
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitProcInvok(Symbol *symbol, struct ElementArray *params);


/*
 * Emit code to invoce function
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitFuncInvok(Symbol *symbol, struct ElementArray *params);


/*
 * Common code to emit functions and procedures invocation
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitProcOrFuncInvokCommon(Symbol *symbol, 
	struct ElementArray *params, char *label);


/*
 * Determines the size of a parameter list
 *
 * Parameters: 	symbol: pointer to function or procedure symbol
 * 	
 * Returns: size of list
 */
int getSizeOfParams(Symbol *procOrFuncSymbol);


/*
 * Emit code to emit array symbol
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitStructuredType(Symbol *arg, Symbol *param);


/*
 * Gets the ElementArray for the paramters for a fucntion or
 * procedure symbol
 *
 * Parameters: procOrFuncSymbol: symbol to func/proc
 * 	
 * Returns: ElementArray of paramters
 */
struct ElementArray *getProcOrFuncParams(Symbol *procOrFuncSymbol);



#endif
