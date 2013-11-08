#ifndef INIT_H
#define INIT_H

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Error.h"
#include "Globals.h"
#include "Hash.h"
#include "PreDef.h"


/* Macros and const string variable declarations. */

/* Global variables. */
extern struct preDefTypeSymbols *preDefTypeSymbols;
extern struct hash *symbolTable;


/* Non-C99 compliant function prototypes. */


/* Function declarations. */
int initialize();


#endif
