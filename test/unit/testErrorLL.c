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
test_getNextError()
{
	struct ErrorLL *ell = NULL;
	struct Error *e1 = NULL, *e2 = NULL, *ret = NULL;
	char errMsg1[ERR_STRSIZE] = "This is only a test";
	char errMsg2[ERR_STRSIZE] = "This is also only a test";
	int lineno = 1000;


	mu_assert("Calling getNextError() with NULL ptr should return NULL",
		  getNextError(&ell) == NULL);


	/* create first test Error */
	e1 = calloc(1, sizeof(struct Error));
	if (!e1) {
		err(1, "Failed to allocate memory for test_appendError.");
		return NULL;
	}
	strncpy(e1->msg, errMsg1, ERR_STRSIZE);
	e1->lineno = lineno;

	/* create second test Error */
	e2 = calloc(1, sizeof(struct Error));
	if (!e2) {
		err(1, "Failed to allocate memory for test_appendError.");
		return NULL;
	}
	strncpy(e2->msg, errMsg2, ERR_STRSIZE);
	e2->lineno = lineno + 1;

	appendError(&ell, e1);
	appendError(&ell, e1);
	appendError(&ell, e2);


	ret = getNextError(&ell);
	mu_assert("First call to getNextError() should not return NULL",
		  ret != NULL);

	mu_assert("First call to getNextError() should return test error 1",
		  (ret->lineno == e1->lineno) &&
		  (strncmp(ret->msg, e1->msg, ERR_STRSIZE) == 0));

	ret = getNextError(&ell);
	mu_assert("Second call to getNextError() should not return NULL",
		  ret != NULL);

	mu_assert("Second call to getNextError() should return test error 2",
		  (ret->lineno == e2->lineno) &&
		  (strncmp(ret->msg, e2->msg, ERR_STRSIZE) == 0));

	ret = getNextError(&ell);
	mu_assert("Third call to getNextError() should return NULL",
		  ret == NULL);

	ret = getNextError(&ell);
	mu_assert("Fourth call to getNextError() should return NULL",
		  ret == NULL);

}


char *
test_all_ErrorLL()
{
	mu_run_test(test_appendError);
	mu_run_test(test_getNextError);
	return NULL;
}
