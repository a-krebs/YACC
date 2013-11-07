#ifndef PREDEF_H
#define PREDEF_H


#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Globals.h"
#include "Definitions.h"


/* Macros and const string variable declarations. */
struct preDefTypeSymbols {
	Symbol *boolean;
	Symbol *chars;
	Symbol *integer;
	Symbol *real;	
};


/* Global variables. */


/* Non-C99 compliant function prototypes. */


/* Function declarations. */
Symbol *getPreDefBool(struct preDefTypeSymbols*);
Symbol *getPreDefChar(struct preDefTypeSymbols*);
Symbol *getPreDefInt(struct preDefTypeSymbols*);
Symbol *getPreDefReal(struct preDefTypeSymbols*);

#endif
