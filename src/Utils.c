/*
 * Utility functions that require input from various sources and do not
 * necessarily belong to any one module.
 */

#include "Utils.h"
#include "parser.tab.h"
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
