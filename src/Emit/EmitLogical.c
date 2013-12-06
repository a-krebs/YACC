/*
 * Module implementing functions which generate asc code necessary to
 * perform logical operations.
 */

/*
 * TODO: NO_OP cases are resultant from a previous and now incorrect design
 * for this module.  These cases are no longer reached and should be removed.
 */

#include "EmitLogical.h"

static void emitLogicalPrep(Symbol *, Symbol *, int *);


/*
 * Given two symbols to be used in a relational operation, emitLogicalPrep()
 * generates the ASC code to insure that two required values are on the 
 * top of the stack before the relational operator is applied.
 */
static void emitLogicalPrep(Symbol *x, Symbol *y, int *opType)
{
	if ( ( x->kind == CONST_KIND && isConstResultSym(x) )
		&&  ( y->kind == CONST_KIND && isConstResultSym(y) ) ) {
		/* Nothing to do */
		*opType = NO_OP;
		return;
	}  

	if ( (x->kind == CONST_KIND) && isConstResultSym(x) ) {
	}
	else if (x->kind == TYPE_KIND && x->isAddress) {
		emitPushAddressValue(x);
	} else if (x->kind != TYPE_KIND) {
		emitPushSymbolValue(x);
	}

	if ( (y->kind == CONST_KIND) && isConstResultSym(y) ) {
	}
	else if (y->kind == TYPE_KIND && y->isAddress) {
		emitPushAddressValue(y);
	} else if (y->kind != TYPE_KIND) {
		emitPushSymbolValue(y);
	}

	*opType = BOOLEAN_OPERATION;	
}

void emitAnd(Symbol *x, Symbol *y)
{
	int opType;
	
	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	emitLogicalPrep(x, y, &opType);
	
	switch (opType) {
	case BOOLEAN_OPERATION:
		emitStmt(STMT_LEN, "AND");
		break;
	case NO_OP:
		break;
	default:
		/* Not reached */
		break;
	}
}

void emitOr(Symbol *x, Symbol *y)
{
	int opType;

	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	emitLogicalPrep(x, y, &opType);

	switch (opType) {
	case BOOLEAN_OPERATION:
		emitStmt(STMT_LEN, "OR");
		break;
	case NO_OP:
		/* Nothing to do */
		break;
	default:
		/* Not reached */
		break;
	}
}
