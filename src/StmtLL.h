/*
 * Implements functionality with regard to the linked list of ASC statements
 * generating during program compliation.
 */

struct stmtll {
	char *stmt;
	struct stmtll *next;
};

typedef struct stmtll StmtLL;

extern struct StmtLL *stmts;

void appendStmt(StmtLL **, char *);
char *getNextStmt(StmtLL **);
void freeStmtLL(StmtLL *);
