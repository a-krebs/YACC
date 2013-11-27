/*
 * Module -- implements asc code generation facilities.
 */
#ifndef EMIT_H
#define EMIT_H

#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Error.h"
#include "Definitions.h"
#include "Kind.h"
#include "StmtLL.h"
#include "SymbolAPI.h"
#include "Type.h"

#define STMT_LEN 128	/* default size of an asc statement, the only exception
			 * to this size would be for labels which may have the
			 * the same name as proc/funcs, in which case we would
			 * not use this default size */

#define CHECK_CAN_EMIT(s)\
do {\
	if(!(s) || (doNotEmit)) {\
		doNotEmit = 1;\
		return;\
	}\
} while (0)
   

extern StmtLL *stmts;

/*
 * From the given pal filename, this function strips the .pal extension and
 * appends the .asc extension.
 * Parameters
 * 		filename: the name of the file to be renamed
 */
char *getAscFileName(char *);


void allocStmt(char **, size_t);
void emitComment(char *);

/* Constant declarations emission functions */
void emitConstDecl(Symbol *);
void emitIntConstDecl(Symbol *, int);
void emitRealConstDecl(Symbol *, float);

/* Variable declaration emission function */
void emitVarDecl(Symbol *);

/* Value pushing emission functions */
void emitPushVarValue(Symbol *);

#endif
