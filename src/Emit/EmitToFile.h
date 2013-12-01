/*
 * Module implementing asc code generation functions needed by the other
 * code generation modules.
 */
#ifndef EMIT_TO_FILE_H
#define EMIT_TO_FILE_H
#include <err.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "StmtLL.h"
#include "EmitUtils.h"
#include "PreDefAsc.h"

#define USER_PROG_START_LABEL "MAIN"

extern StmtLL *stmts;


/*
 * Write generated code to file.
 *
 * Parameters:
 * 	fileName: name of the .asc file to which to write.
 * Return:
 * 	0 on success,
 * 	non-zero otherwise
 */
int emitToFile(char *fileName);


/*
 * Emit the pre-defined ASC functions.
 */
void emitPreDefCode();


/*
 * Emit anything that must be emitted before the code generated from the
 * input PAL. This includes predefined funcs and procs, constants, etc.
 */
void emitInit();


#endif
