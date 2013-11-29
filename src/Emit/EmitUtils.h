/*
 * Module implementing asc code generation functions needed by the other
 * code generation modules.
 */
#ifndef EMITUTILS_H
#define EMITUTILS_H
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
#include "../SymbolArray.h"
#include "../Type.h"

extern int doNotEmit;

#define STMT_LEN 128	/* default size of an asc statement, the only exception
			 * to this size would be for labels which may have the
			 * the same name as proc/funcs, in which case we would
			 * not use this default size */

#define MAX_COMMENT_LEN 1024

#define CHECK_CAN_EMIT(s)\
do {\
	if(!(s) || (doNotEmit)) {\
		doNotEmit = 1;\
		return;\
	}\
} while (0)
   

extern StmtLL *stmts;

char *getAscFileName(char *);

void allocStmt(char **, size_t);
void emitComment(char *, ...);
void emitStmt(int len, char *, ...);

#endif
