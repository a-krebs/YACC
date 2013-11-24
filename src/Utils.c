/*
 * Utility functions that require input from various sources and do not
 * necessarily belong to any one module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "Error.h"
#include "Utils.h"
#ifndef TESTBUILD
#include "parser.tab.h"
#endif
#ifdef TESTBUILD
#include "tokens.h"
#endif

extern int yylineno;

static char *errMsg;

#define OPSTR_LEN 64

void
opError(char *xType, int op, char *yType)
{
	errMsg = customErrorString("Invalid expression. Types %s and %s"   
	    " not compatible with operator %s", xType, yType,
	    opToString(op));
	recordError(errMsg, yylineno, colno, SEMANTIC);
}

char *
opToString(int op)
{	
	static char opStr[OPSTR_LEN];
	memset(opStr, '\0', OPSTR_LEN);
	switch (op) {
		case NOT:
			strcpy(opStr, "NOT");
			break;
		case MULTIPLY:
			strcpy(opStr, "MULTIPLY");
			break;
		case DIVIDE:
			strcpy(opStr, "DIVIDE");
			break;
		case DIV:
			strcpy(opStr, "DIV");
			break;
		case MOD:
			strcpy(opStr, "MOD");
			break;
		case AND:
			strcpy(opStr, "AND");
			break;
		case PLUS:
			strcpy(opStr, "PLUS");
			break;
		case MINUS:
			strcpy(opStr, "MINUS");
			break;
		case OR:
			strcpy(opStr, "OR");
			break;
		case EQUAL:
			strcpy(opStr, "EQUAL");
			break;
		case NOT_EQUAL:
			strcpy(opStr, "NOT_EQUAL");
			break;
		case LESS:
			strcpy(opStr, "LESS");
			break;
		case LESS_OR_EQUAL:
			strcpy(opStr, "LESS_OR_EQUAL");
			break;
		case GREATER:
			strcpy(opStr, "GREATER");
			break;
		case GREATER_OR_EQUAL :
			strcpy(opStr, "GREATER_OR_EQUAL ");
			break;
		default:
			break;
	}
	return opStr;
}

void
alreadyDefinedError(char *id) {
	errMsg = customErrorString("The identifer %s is already defined at "
	   "the current scope.", id);
	recordError(errMsg, yylineno, colno, SEMANTIC);
}

void
notDefinedError(char *id) {

	errMsg = customErrorString("The identifier %s is undefined.", id);
	recordError(errMsg, yylineno, colno, SEMANTIC);
}

void symbolTableInsertFailure() {
	err(EXIT_FAILURE, "Failed to insert into symbol table.");
}

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
	if ( (op == PLUS) || 
		(op == MINUS) ||
		   (op == NOT) ) {
		return 1;
	}

	return 0;

}




int getStrlen(struct String s)
{
	return s.strlen;
}
