#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "ErrorLL.h"

struct ErrorLL *errors = NULL;


/*
 * Appends the given error pointer e to the linked list of errors
 * eLL.
 */
void
appendError(struct ErrorLL **eLL, struct Error *e)
{
	struct ErrorLL *t1, *t2;
	
	t1 = *eLL;
	if (*eLL == NULL) {
		/* List is empty, add first element */
		t1 = calloc(1, sizeof(struct ErrorLL));
		if (t1 == NULL) {
			/* Out of memory? ... stop compiling? */
			err(1, "Failed to allocate memory for ErrorLL node.");
			return;
		}
		t1->error = e;
		t1->next = NULL;
		*eLL = t1;
	} else {
		/* List is not empty, append to end */
		while (t1->next != NULL) {
			t1 = t1->next;
		}
		t2 = calloc(1, sizeof(struct ErrorLL));
		
		if (t2 == NULL) {
			/* Out of memory? ... stop compiling? */
			err(1, "Failed to allocate memory for ErrorLL node.");
			return;
		}
		
		t2->error = e;
		t2->next = NULL;
		t1->next = t2;
	}
}


/*
 * Returns a pointer to the next Error in the given
 * ErrorLL or NULL if none exists or if passed a NULL
 * pointer.
 */
struct Error *
getNextError(struct ErrorLL ** eLL)
{
	if (!(*eLL)) return NULL;
	if (!((*eLL)->error)) return NULL;
	if (!(*eLL = (*eLL)->next)) return NULL;
	return (*eLL)->error;

}


/*
 * Frees all memory associated with the linked list ErrorLL.
 */
void
freeErrorList(struct ErrorLL *ell)
{
	struct ErrorLL *copy;
	while (ell) {
		copy = ell;
		ell = ell->next;
		freeError(copy->error);
		free(copy);
	}
}
