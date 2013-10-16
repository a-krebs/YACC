/*
 * Cmput 415 - Team YACC
 * Unit tests for the Error module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testError.h"


char *
test_createErrorString()
{
	char errorMsg[] = "This is only a test.";
	int ERR_STRSIZE = strlen(errorMsg);
	int lineno = 1029, colno = 999,bufSize = 512;
	char *buf;
	char expectedRet[] = "Error: This is only a test. (line 1029, col 999)";
	
	struct Error *e = malloc(sizeof(struct Error));
	if (!e) {
		err(1, "Failed to allocate memory for createErrorString()");
		return NULL;
	}
	e->msg = calloc(1, sizeof(char)*ERR_STRSIZE);
	if (!e->msg) {
		err(1, "Failed to allocate memory for error message");
		return NULL;
	}
	strncpy(e->msg, errorMsg, ERR_STRSIZE);
	e->lineno = lineno;
	e->colno = colno;

	createErrorString(&buf, e);
	mu_assert("createErrorString() should write to buf the expected return.",
		  strncmp(expectedRet, buf, strlen(expectedRet)) == 0);
	return NULL;

	
	

}

char *
test_recordError() 
{
	char errorMsg[] = "This is only a test.";
	int ERR_STRSIZE = strlen(errorMsg);

	int lineno = 1029, colno = 9899;
	struct Error *ret = NULL;

	errors = NULL;
	ret = recordError(errorMsg, lineno, colno);

	mu_assert("recordError doest not return  NULL pointer.", (ret));
	mu_assert("lineno correctly set in returned Error.",
		  ret->lineno == lineno);
	mu_assert("colno correctly set in returned Error.",
		  ret->colno == colno);
	mu_assert("Error message correct set in returned Error.",
		  strncmp(ret->msg, errorMsg, ERR_STRSIZE) == 0);
	mu_assert("Error correctly appended as first element of ErrorLL.",
		  (strncmp(errors->error->msg, ret->msg, ERR_STRSIZE) == 0) &&
		  (errors->error->lineno == ret->lineno) &&
		  (errors->error->colno == ret->colno));
	return NULL;
}

char *
test_all_Error() 
{
	mu_run_test(test_createErrorString);
	mu_run_test(test_recordError);
	return NULL;
}
