/*
 * Cmput 415 - Team YACC
 * Unit tests for the Error module.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "testError.h"


char *
test_createErrorString()
{
	char errorMsg[] = "This is only a test.";
	int ERR_STRSIZE = strlen(errorMsg);
	int lineno = 1029, colno = 999;
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
	mu_assert("createErrorString() should write to buf the expected return",
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
	ret = recordError(errorMsg, lineno, colno, GENERIC);

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
test_customErrorString()
{
	char bigStr[CUSTOM_ERRMSG_SZ + 10];
	int a1 = 10, a2 = 123, a3 = 321;
	char varName[] = "customVan";
	char formatStr[] = "a1 = %d, a2 = %d, a3 = %d, varName = %s";
	char expectedRet[] = "a1 = 10, a2 = 123, a3 = 321, varName = customVan";
	char *ret = customErrorString(formatStr, a1, a2, a3, varName);
	int i;

	mu_assert("customErrorString() should return a string of the expected\
		  format", strcmp(ret, expectedRet) == 0);
	for(i = 0; i < CUSTOM_ERRMSG_SZ + 10; i++) {
		bigStr[i] = 'a';
	}

	ret = customErrorString(bigStr);
	mu_assert("call to customErrorString() should not cause segfault  \
		  when passed string larger than buf size and the returned\
		  string should be null terminated",
		  ret[CUSTOM_ERRMSG_SZ-1] == '\0');

	ret = customErrorString(formatStr, a1, a2, a3, varName);
	mu_assert("customErrorString() should return string of the expected\
		  format even newest string is smaller than previous string\
		  (e.g., fact that buffer was filled on last call should   \
		  not affect null termination of next string created)",
		  strcmp(ret, expectedRet) == 0);
	return NULL;
}

char *
test_freeError()
{	

	char errorMsg[] = "This is only a test.";

	int lineno = 1029, colno = 9899;

	errors = NULL;
	struct Error *ret = NULL;

	ret = recordError(errorMsg, lineno, colno, GENERIC);
	freeError(ret);
	mu_assert("Call to freeError does not cause segfault",
		  1);

	return NULL;
}

char *test_getErrorTypeString()
{
	char *syntax = "Syntax";
	char *semantic = "Semantic";
	mu_assert("getErrorTypeString returned wrong string.",
	    strcmp(getErrorTypeString(SYNTAX), syntax) == 0);
	mu_assert("getErrorTypeString returned wrong string.",
	    strcmp(getErrorTypeString(SEMANTIC), semantic) == 0);
	mu_assert("getErrorTypeString returned wrong string.",
	    getErrorTypeString(GENERIC) == NULL);
	return NULL;
}

char *
test_all_Error() 
{
	mu_run_test(test_createErrorString);
	mu_run_test(test_recordError);
	mu_run_test(test_customErrorString);
	mu_run_test(test_freeError);
	mu_run_test(test_getErrorTypeString);
	return NULL;
}
