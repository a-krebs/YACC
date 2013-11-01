/*
 * Cmput 415 - Team YACC
 * Unit tests for the Type module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testType.h"

char *
test_isOrdinal()
{
	mu_assert("isOrdinal() should return false for REAL_T",
		  isOrdinal(REAL_T) == 0);
	mu_assert("isOrdinal() should return true for CHAR_T",
		  isOrdinal(CHAR_T));
	mu_assert("isOrdinal() should return true for BOOLEAN_T",
		  isOrdinal(BOOLEAN_T));
	mu_assert("isOrdinal() should return true for INTEGER_T",
		  isOrdinal(INTEGER_T));
	mu_assert("isOrdinal() should return 0 for ARRAY_T",
		  !isOrdinal(ARRAY_T));
	return NULL;
}

char *
test_all_Type()
{
	mu_run_test(test_isOrdinal);
	return NULL;
}
