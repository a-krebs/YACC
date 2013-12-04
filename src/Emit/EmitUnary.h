/*
 * Module implementing functionality with regard to asc code generation for
 * performing relational operations.
 */
#ifndef EMITUNARY_H
#define EMITUNARY_H

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "EmitExprs.h"
#include "EmitUtils.h"

#define INTEGER_UNARY_OPERATION 1
#define REAL_UNARY_OPERATION 2
#define BOOLEAN_UNARY_OPERATION 3

void emitUnaryPlus(Symbol *);
void emitUnaryMinus(Symbol*);
void emitNot(Symbol *);

#endif
