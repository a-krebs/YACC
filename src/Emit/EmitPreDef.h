/*
 * Module implements functions which generate asc code to call pre-defined
 * asc functions.
 */

#ifndef EMITPREDEF_H
#include <stdio.h>

#include "../Tree.h"
#include "EmitProcs.h"
#include "EmitExprs.h"
#include "EmitUtils.h"
#include "../ElementArray.h"

#define REAL_IO_OP 0
#define INT_IO_OP 1
#define STR_IO_OP 2

void emitPreDefIO(Symbol *, struct ElementArray *);
void emitPreDefFunc(Symbol *, struct ElementArray *);
#endif 

