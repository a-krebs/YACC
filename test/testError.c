/*
 * Cmput 415 - Team YACC
 * Unit tests for the Error module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testError.h"

char *
test_recordError() 
{
	char errorMsg[ERR_STRSIZE] = "This is only a test.";
	int lineno = 1029;
	struct Error *ret = NULL;

	errors = NULL;
	ret = recordError(errorMsg, lineno);

	mu_assert("recordError doest not return  NULL pointer.", (!ret));
	mu_assert("lineno correctly set in returned Error.",
		  ret->lineno != lineno);
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
	mu_run_test(test_recordError);
	return NULL;
}
