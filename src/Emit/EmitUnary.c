/*
 * Module implementing functions which generate asc code to perform unary
 * operations.
 */

#include "EmitUnary.h"

static void emitUnaryPrep(Symbol *, int *);

static void emitUnaryPrep(Symbol *x, int *opType)
{
	/* If x is a const, then its value has been calculated and propogated
 	 * in the semantic analysis portion of the compiler */
	if (x->kind == CONST_KIND) {
		emitPushSymbolValue(x);
		return;
	}

	/* If x is a type, then its value has been pushed onto the stack
	 * during the parsing of the expression which defines its value.
	 * Else, we push its value. */
	if (x->kind != TYPE_KIND) {
		emitPushSymbolValue(x);
	}

	switch (getType(x)) {
	case BOOLEAN_T:
		*opType = BOOLEAN_UNARY_OPERATION;
	
	case INTEGER_T:
		*opType = INTEGER_UNARY_OPERATION;
		return;
	case REAL_T:
		*opType = REAL_UNARY_OPERATION;
		return;
	default:
		/* Not reached */
		return;

	}
}

void emitUnaryPlus(Symbol *x)
{
	int opType;
	emitUnaryPrep(x, &opType);
	/* Do nothing */
}

void emitUnaryMinus(Symbol *x)
{
	int opType;
	emitUnaryPrep(x, &opType);

	switch (opType) {
	case INTEGER_UNARY_OPERATION:
		emitStmt(STMT_LEN, "CONSTI -1");
		emitStmt(STMT_LEN, "MULI");
		break;

	case REAL_UNARY_OPERATION:
		emitStmt(STMT_LEN, "CONSTR -1.0");
		emitStmt(STMT_LEN, "MULR");
		break;

	case NO_OP:
		/* Do nothing */
		break;
	default:
		/* Not reached. */
		break;
	}
}

void emitNot(Symbol *x)
{
	int opType;
	emitUnaryPrep(x, &opType);

	switch (opType) {
	case BOOLEAN_UNARY_OPERATION:
		emitStmt(STMT_LEN, "NOT");
		break;
	case NO_OP:
		/* Do nothing */
		break;
	default:
		/* Not reached */
		break;
	}
}
