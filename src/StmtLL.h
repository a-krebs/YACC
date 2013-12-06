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


/*
 * Print all statments in the stmtLL to the given file stream.
 * Parameters:
 * 	outStream: the file stream to which to write
 * 	ll: the StmtLL to be printed
 */
void writeStmtLL(FILE *outStream, StmtLL *ll);

	
char *getNextStmt(StmtLL **);
void freeStmtLL(StmtLL *);

#endif
