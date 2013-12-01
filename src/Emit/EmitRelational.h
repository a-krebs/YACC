/*
 * Module implementing functionality with regard to asc code generation for
 * performing relational operations.
 */
#ifndef EMITRELATIONAL_H
#define EMITRELATIONAL_H

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "EmitExprs.h"
#include "EmitUtils.h"
#include "../Type.h"


void emitRelationalPrep(Symbol *, Symbol *);

#endif
