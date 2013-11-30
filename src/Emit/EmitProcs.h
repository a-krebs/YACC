/*
 * Module implementing functions generating asc code for 
 * procedures and functions.
 */
#ifndef EMITARITHMETIC_H
#define EMITARITHMETIC_H

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
#include "../Type.h"
#include "../ElementArray.h"
#include "../Hash.h"
#include "EmitUtils.h"

extern int doNotEmit;


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
void emitProcDecl(Symbol *symbol, struct ElementArray *ea);


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
void emitProcParam(Symbol *param, int paramNum);


/*
 * Emit code to end a procedure. Adjusts for any local variables
 * and returns.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitEndProc();


#endif
