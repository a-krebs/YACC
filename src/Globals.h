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
struct labelStack *labelStack;

/* label stuff for procedure/function statement code emmission */
struct labelStack *procOrFuncStack;

#endif
