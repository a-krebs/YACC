/*
 * Cmput 415 - Team YACC
 * Unit tests for the ErrorLL module.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testErrorLL.h"

char *
test_appendError()
{
	struct ErrorLL *ell = NULL;
	struct Error *e = NULL;
	char  errMsg[ERR_STRSIZE] = "This is only a test";
	int lineno = 1000;

	e = calloc(1, sizeof(struct Error));
	if (!e) {
		err(1, "Failed to allocate memory for test_appendError.");
		return NULL;
	}
	strncpy(e->msg, errMsg, ERR_STRSIZE);
	e->lineno = lineno;

	appendError(&ell, e);

	mu_assert("appendError should not leave ErrorLL NULL",
		  ell != NULL);
	mu_assert("appended Error is identical to one passed to appendError",
		  (ell->error->lineno == lineno) &&
		  (strncmp(ell->error->msg, errMsg, ERR_STRSIZE) == 0));	
}

char *
test_all_ErrorLL()
{
	mu_run_test(test_appendError);
	return NULL;
}
