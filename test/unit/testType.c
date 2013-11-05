/*
 * Cmput 415 - Team YACC
 * Unit tests for the Type module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testType.h"

char *
test_areSameType()
{
	Symbol *s1 = setUpTypeSymbol();
	Symbol *s2 = setUpTypeSymbol();

	mu_assert("s1 and s2 are NOT the exact same type",
	    !areSameType(s1, s2));

	s1->kindPtr.TypeKind = s2->kindPtr.TypeKind;
	mu_assert("s1 and s2 are of the exact same type",
	    areSameType(s1, s2));
	return NULL;

}

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
test_setTypePtr()
{
	Type new, old;
	type_t type;
	void * addr = (void *) 0x3924ff30;

	old.Array = addr;
	type = ARRAY_T;
	setTypePtr(&new, old, type);
	mu_assert("new.Array should point to test addr",
		  new.Array == addr);
	return NULL;
}

char *
test_all_Type()
{
	mu_run_test(test_areSameType);
	mu_run_test(test_setTypePtr);
	mu_run_test(test_isOrdinal);
	return NULL;
}
