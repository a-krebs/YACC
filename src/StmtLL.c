/*
 * Implements functionality with regard to the linked list of ASC statements
 * generated during program compilation.
 */

#include <err.h>
#include <stdlib.h>
#include <stdio.h>

#include "StmtLL.h"


StmtLL *stmts = NULL;

void
appendStmt(StmtLL **ll, char *s)
{
	StmtLL *t1, *t2;

	t1 = *ll;
	if (!*ll) {
		/* List is empty, allocate memory and add first element */
		t1 = calloc(1, sizeof(StmtLL));
		if (!t1) err(1, "Failed to allocate memory for StmtLL node");
		t1->stmt = s;
		t1->next = NULL;
		*ll = t1;
	} else {
		while (t1->next != NULL) t1 = t1->next;
		t2 = calloc(1, sizeof(StmtLL));
		if (!t2) err(1, "Failed to allocate memory for StmtLL node");

		t2->stmt = s;
		t2->next = NULL;
		t1->next = t2;
	}
}

/*
 * Debug function -- prints all statements in the stmtLL to stderr.
 * Parameters:
 *		ll : the StmtLL to be dumped
 */
void
dumpStmtLL(StmtLL *ll)
{
	if (!ll) return;
	writeStmtLL(stderr, ll);
}


/*
 * Print all statments in the stmtLL to the given file stream.
 * Parameters:
 * 	outStream: the file stream to which to write
 * 	ll: the StmtLL to be printed
 */
void writeStmtLL(FILE *outStream, StmtLL *ll) {
	if ((!ll)||(!outStream)) return;
	while (ll) {
		fprintf(outStream, "%s", ll->stmt);
		ll = ll->next;
	}
}

char *
getNextStmt(StmtLL **ll)
{
	if (!(*ll)) return NULL;
	if (!((*ll)->stmt)) return NULL;
	if (!(*ll = (*ll)->next)) return NULL;
	return (*ll)->stmt;
}

void
freeStmtList(StmtLL *ll)
{
	StmtLL *copy;
	while (ll) {
		copy = ll;
		ll = ll->next;
		free(copy->stmt);
		free(copy);
	}
}
