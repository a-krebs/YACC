/*
 * Cmput 415 - Team YACC
 * Unit tests for the Actions module
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>

#include "testActions.h"
#include "Actions.h"

char *test_assertOpCompat() {
	// TODO
	return NULL;
}

char *test_assignmentCompatEh() {
	// TODO
	return NULL;
}

char *test_enterConstDeclPart() {
	// function does nothing, so nothing to test
	return NULL;
}

char *test_doConstDecl(){
	// TODO
	return NULL;
}

char *test_enterTypeDecltPart() {
	// function does nothing, so nothing to test
	return NULL;
}

char *test_doTypeDecl() {
	// TODO
	return NULL;
}

char *test_all_Actions() {
	mu_run_test(test_assertOpCompat);
	mu_run_test(test_assignmentCompatEh);
	mu_run_test(test_enterConstDeclPart);
	mu_run_test(test_doConstDecl);
	mu_run_test(test_enterTypeDecltPart);
	mu_run_test(test_doTypeDecl);
	return NULL;
}
