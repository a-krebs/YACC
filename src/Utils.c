/*
 * Utility functions that require input from various sources and do not
 * necessarily belong to any one module.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"
#include "parser.tab.h"

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
		return 1;
	case NOT_EQUAL:
		return 1;
	case LESS:
		return 1;
	case LESS_OR_EQUAL:
		return 1;
	case GREATER:
		return 1;
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
