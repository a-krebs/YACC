#ifndef GLOBALS_H
#define GLOBALS_H

#include "PreDef.h"


/* Global symbol table */
struct hash *symbolTable;

/* global pre-defined types */
struct preDefTypeSymbols *preDefTypeSymbols;

/* how many nested while loops? */
unsigned long long whileLoopDepth;

/* label stuff for control statement code emmission */
struct labelStack *labelStack;		/* for if statements */
struct labelStack *loopLabelStack;	/* for while loops */

/* label stuff for procedure/function statement code emmission */
struct labelStack *procOrFuncStack;
struct labelStack *mainLabelStack;

/* 
 * flag to say we're in the main program decls section. Used to
 * CALL main program body rather than GOTOing, so that display registers
 * are set properly
 */
int inMainDecls;
#endif
