/*
 * Unit tests for the Utils module.
 */

#include <stdio.h>
#include <stdlib.h>

#include "testUtils.h"

char *
test_isLogicalOperator()
{
	mu_assert("AND is a logical operator",
	    isLogicalOperator(AND));
	mu_assert("MULTIPLY is not a logical operator",
	    !isLogicalOperator(MULTIPLY));
	return NULL;
}

char *
test_isRelationalOperator()
{
	mu_assert("GREATER_OR_EQUAL is a relational operator",
	    isRelationalOperator(GREATER_OR_EQUAL));
	mu_assert("EQUAL is a relational operator",
	    isRelationalOperator(EQUAL));
	mu_assert("AND is not a relational operator",
	    !isRelationalOperator(AND));
	return NULL;
}


char *
test_isUnaryOperator()
{
	mu_assert("PLUS is a unary operator", isUnaryOperator(PLUS));
	mu_assert("MINUS is a unary operator", isUnaryOperator(MINUS));
	mu_assert("EQUAL is not a unary operator", !isUnaryOperator(EQUAL));

	return NULL;
}

char *
test_all_Utils()
{
	mu_run_test(test_isUnaryOperator);
	mu_run_test(test_isLogicalOperator);
	mu_run_test(test_isRelationalOperator);
	return NULL;
}


