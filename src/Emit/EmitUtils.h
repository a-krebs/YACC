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

#include "Error.h"
#include "Definitions.h"
#include "Kind.h"
#include "StmtLL.h"
#include "SymbolAPI.h"
#include "SymbolArray.h"
#include "Type.h"

extern int doNotEmit;

#define STMT_LEN 128	/* default size of an asc statement, the only exception
			 * to this size would be for labels which may have the
			 * the same name as proc/funcs, in which case we would
			 * not use this default size */

#define MAX_COMMENT_LEN 1024
#define DEFAULT_LABEL_STACK_SIZE 128

#define CHECK_CAN_EMIT(s)\
do {\
	if(!(s) || (doNotEmit)) {\
		doNotEmit = 1;\
		return;\
	}\
} while (0)


extern StmtLL *stmts;

/* label stack for control statement code emission */
struct labelStack {
	int label;
	int *stack;
	int stackSize;
	int ltop;
};

char *getAscFileName(char *);

void allocStmt(char **, size_t);
void emitComment(char *, ...);
void emitStmt(int len, char *, ...);
void emitLabel(int len, char*, ...);

void emitArrayElementLocation(Symbol *, Symbol *);
void emitPushVarValue(Symbol *);
void emitPushConstValue(Symbol *);
void emitPushSymbolValue(Symbol *);


/*
 * Reserve n labels.
 *
 * Parameters:
 * 	stack: the stack on which to reserve labels
 * 	n: number of labels to reserve
 */
void reserveLabels(struct labelStack *stack, int n);

	
/*
 * Pop labels off the label stack.
 *
 * Parameters:
 * 	stack: the stack from which to pop labels.
 */
void popLabels(struct labelStack *stack);


/*
 * Check the value at the top of the stack without changing it.
 * Errors and exits if the stack does not have labels reserved
 *
 * Parameters:
 * 	stack: the stack at which to look
 *
 * Return:
 * 	the label at the top of the stack
 */
int peekLabelStackTop(struct labelStack *stack);

	
/*
 * Create a new struct labelStack from which labels can be reserved 
 *
 * Return:
 * 	A pointer to the new labelStack struct.
 */
struct labelStack *newLabelStack();


/*
 * Grow a label stack by DEFAULT_LABEL_STACK_SIZE.
 *
 * Parameters:
 * 	stack: the label stack to grow
 */
void growLabelStack(struct labelStack *stack);


/*
 * Destroy a label stack and set the pointer to NULL.
 *
 * Parameters:
 * 	stack: a double pointer to the label stack to destory
 */
void destroyLabelStack(struct labelStack **stack);


#endif
