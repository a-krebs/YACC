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
#include "Emit.h"

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
 * Encountered 'continue' statement. Verify we're in a while loop and then
 * continue to next iteration.
 */
void continueLoop(void) {
	if (whileLoopDepth <= 0) {
		errMsg = customErrorString("A continue statement is only "
		    "allowed inside a while loop.");
		recordError(errMsg, yylineno, colno, SEMANTIC);
	}
}

/*
 * Encountered 'exit' statement. Verify we're in a while loop and then
 * exit innermost loop.
 */
void exitLoop(void) {
	if (whileLoopDepth <= 0) {
		errMsg = customErrorString("An exit statement is only "
		    "allowed inside a while loop.");
		recordError(errMsg, yylineno, colno, SEMANTIC);
	}
}

/*
 * End of while loop.
 */
void endWhileLoop(void) {
	whileLoopDepth--;
}

/*
 * Confirm that exp is of boolean type.
 */
void ifPart(ProxySymbol *expr) {
	/* make sure we have boolean expression */
	if ((expr == NULL) || (getType(getInnerTypeSymbol(expr)) != BOOLEAN_T)) {
		errMsg = customErrorString("If statement must be given ",
		    "boolean type expression.");
		recordError(errMsg, yylineno, colno, SEMANTIC);
	}

	/* expression code already emitted */
	emitIfStat(expr);
}
