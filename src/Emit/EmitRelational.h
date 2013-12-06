/*
 * Module implementing functionality with regard to asc code generation for
 * performing relational operations.
 */
#ifndef EMITRELATIONAL_H
#define EMITRELATIONAL_H

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

//#include "parser.tab.h"
#include "EmitExprs.h"
#include "EmitUtils.h"
#include "../Symbol.h"
#include "../Type.h"

#define INTEGER_OPERATION 0
#define REAL_OPERATION 1
#define STRUCTURED_OPERATION 2
#define SCALAR_OPERATION 3


void emitEqualsOp(Symbol *, Symbol *);
void emitInequalityOp(Symbol *, Symbol *);
void emitLTEOp(Symbol *, Symbol *);
void emitLTOp(Symbol *, Symbol *);
void emitGTEOp(Symbol *, Symbol *);
void emitGTOp(Symbol *, Symbol *);

#endif
