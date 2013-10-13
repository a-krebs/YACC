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
	char errorMsg[ERR_STRSIZE] = "This is only a test.";
	int lineno = 1029, bufSize = 512;
	char buf[bufSize];
	char expectedRet[] = "Error: This is only a test. (line 1029)";
	
	buf[bufSize-1] = 'a';

	struct Error *e = malloc(sizeof(struct Error));
	if (!e) {
		err(1, "Failed to allocate memory for createErrorString()");
		return NULL;
	}
	strncpy(e->msg, errorMsg, ERR_STRSIZE);
	e->lineno = lineno;

	createErrorString(buf, bufSize, NULL);
	mu_assert("Call to createErrorString() with NULL e should leave buf unmodified",
		  buf[bufSize-1] == 'a');

	createErrorString(buf, bufSize, e);
	mu_assert("createErrorString() should write to buf the expected return.",
		  strncmp(expectedRet, buf, strlen(expectedRet)) == 0);
	return NULL;

	
	

}

char *
test_recordError() 
{
	char errorMsg[ERR_STRSIZE] = "This is only a test.";
	int lineno = 1029;
	struct Error *ret = NULL;

	errors = NULL;
	ret = recordError(errorMsg, lineno);

	mu_assert("recordError doest not return  NULL pointer.", (ret));
	mu_assert("lineno correctly set in returned Error.",
		  ret->lineno == lineno);
	mu_assert("Error message correct set in returned Error.",
		  strncmp(ret->msg, errorMsg, ERR_STRSIZE) == 0);
	mu_assert("Error correctly appended as first element of ErrorLL.",
		  (strncmp(errors->error->msg, ret->msg, ERR_STRSIZE) == 0) &&
		  (errors->error->lineno == ret->lineno));
	return NULL;
}

char *
test_all_Error() 
{
	mu_run_test(test_createErrorString);
	mu_run_test(test_recordError);
	return NULL;
}
