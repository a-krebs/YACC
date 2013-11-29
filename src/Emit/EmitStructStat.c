/*
 * Module implementing functions generating asc code for structured
 * statements like if-then, if-then-else, while, continue, end
 */

#include "EmitStructStat.h"

/*
 * Emit ASC code to start an if statement.
 * Assumes the correspoding expression has already been emitted
 */
void emitIfStat(Symbol *s) {
	CHECK_CAN_EMIT(s);
	/* reserve labels for THEN and ELSE */
	reserveLabels(labelStack, 2);

	emitComment("IF expr THEN");
	emitStmt(STMT_LEN, "IFZ %s%d", 
	    LABEL_PREFIX, peekLabelStackTop(labelStack));
}


/*
 * Emit ASC code for a then statment.
 * Assumes the corresposding statement or matched_stat code has already
 * been emitted.
 */
void emitThenMatchedStat() {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(1);

	emitComment("THEN stat");
	emitStmt(STMT_LEN, "GOTO %s%d",
	    LABEL_PREFIX, peekLabelStackTop(labelStack) + 1);
	emitStmt(STMT_LEN, "%s%d:",
	    LABEL_PREFIX, peekLabelStackTop(labelStack));
}

/*
 * Emit ASC code for an else statement
 * Assumes the corresponding statement code is already generated.
 */
void emitElseStat() {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(1);

	emitComment("ELSE stat");
	emitStmt(STMT_LEN, "%s%d",
	    LABEL_PREFIX, peekLabelStackTop(labelStack) + 1);
	popLabels(labelStack);
}
