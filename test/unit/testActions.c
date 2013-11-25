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
#include "testSymbol.h"	/* for setUpTypeSymbol() */
#include "ActionsAll.h"

char *test_assertOpCompat() {
	Symbol *type1 = setUpTypeSymbol();
	Symbol *type2 = setUpTypeSymbol();

	mu_assert("Two integer types compatible with DIV",
	    assertOpCompat(type1, PLUS, type2));	
	mu_assert("Two integer types are compatible with EQUAL",
	    assertOpCompat(type1, EQUAL, type2));

	type1->kindPtr.TypeKind->type = BOOLEAN_T;

	mu_assert("A boolean and an integer are not compatible with LESS",
	    !assertOpCompat(type1, LESS, type2));

	type1->kindPtr.TypeKind->type = ARRAY_T;
	type1->kindPtr.TypeKind->type = ARRAY_T;
	mu_assert("Two arrays types are not compatible with EQUAL",
	   !assertOpCompat(type1, EQUAL, type2));
	
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
