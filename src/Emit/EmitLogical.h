/*
 * Module implementing functionality with regard to asc code generation for
 * performing logical operations.
 */
#ifndef EMITLOGICAL_H
#define EMITLOGICAL_H

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "EmitExprs.h"
#include "EmitUtils.h"
#include "../Symbol.h"
#include "../Type.h"

#define BOOLEAN_OPERATION 1

void emitAnd(Symbol *, Symbol *);
void emitOr(Symbol *, Symbol *);

#endif
