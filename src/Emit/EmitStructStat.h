/*
 * Module implementing functions generating asc code for performing 
 * const, variable, procedure and function declarations.
 */
#ifndef EMIT_STRUCT_STAT_H
#define EMIT_STRUCT_STAT_H

#include <err.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Error.h"
#include "Globals.h"
#include "Definitions.h"
#include "Kind.h"
#include "StmtLL.h"

#include "EmitUtils.h"

#define LABEL_PREFIX "L"

extern int doNotEmit;


/*
 * Emit ASC code to start an if statement.
 * Assumes the correspoding expression has already been emitted
 */
void emitIfStat(Symbol *s);


/*
 * Emit ASC code for a then statment.
 * Assumes the corresposding statement or matched_stat code has already
 * been emitted.
 */
void emitThenMatchedStat();


/*
 * Emit ASC code for an else statement
 * Assumes the corresponding statement code is already generated.
 */
void emitElseStat();


#endif
