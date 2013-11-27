/*
 * Module implementing functions generating asc code for performing 
 * arithmetic operations.
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

#include "EmitUtils.h"

#define ARITHMETIC_RESULT_INTEGER 0
#define ARITHMETIC_RESULT_REAL 1

extern int doNotEmit;

void emitArithmeticPrep(Symbol *, Symbol *, int *);
void emitAddition(Symbol *, Symbol *);


#endif
