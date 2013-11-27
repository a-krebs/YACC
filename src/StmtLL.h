/*
 * Implements functionality with regard to the linked list of ASC statements
 * generating during program compliation.
 */
#ifndef STMTLL_H
#define STMTLL_H

struct stmtll {
	char *stmt;
	struct stmtll *next;
};

typedef struct stmtll StmtLL;

void appendStmt(StmtLL **, char *);
void dumpStmtLL(StmtLL *);
char *getNextStmt(StmtLL **);
void freeStmtLL(StmtLL *);

#endif
