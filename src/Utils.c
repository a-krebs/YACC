/*
 * Utility functions that require input from various sources and do not
 * necessarily belong to any one module.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"
#ifndef TESTBUILD
#include "parser.tab.h"
#endif
#ifdef TESTBUILD
#include "tokens.h"
#endif
int
isLogicalOperator(int op)
{
	switch (op) {
	case NOT:
	case AND:
	case OR:
		return 1;
	default:
		return 0;
	}
}


/*
 * Returns true if the given token is a relation operator token.
 */
int
isRelationalOperator(int op)
{
	switch (op) {
	case EQUAL:
	case NOT_EQUAL:
	case LESS:
	case LESS_OR_EQUAL:
	case GREATER:
	case GREATER_OR_EQUAL:
		return 1;
	default:
		return 0;
	}	
}

/*
 * Returns true if the given token is a unary operator.
 */
int
isUnaryOperator(int op)
{
	if ((op == PLUS) || (op == MINUS)) return 1;
	return 0;

}
