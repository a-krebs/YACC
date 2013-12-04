/*
 * Module implementing functions generating asc code for performing 
 * const, variable, procedure and function declarations.
 */
#ifndef EMITDECLS_H
#define EMITDECLS_H

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

#include "EmitExprs.h"
#include "EmitUtils.h"

extern int doNotEmit;

/* Constant declarations emission functions */
void emitConstDecl(Symbol *);
void emitIntConstDecl(Symbol *, int);
void emitRealConstDecl(Symbol *, float);
void emitStringConstDecl(Symbol *);

/* Variable declaration emission function */
void emitVarDecl(Symbol *);
#endif
