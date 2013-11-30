/*
 * Module implementing functions generating asc code for 
 * procedures and functions.
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

extern int doNotEmit;


void emitProcDecl(Symbol *symbol, struct ElementArray *ea);
void emitProcParam(Symbol *param, int paramNum);


#endif
