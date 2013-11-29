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
	emitStmt(
	    STMT_LEN, "IFZ %s%d", 
	    LABEL_PREFIX, peekLabelStackTop(labelStack));
}
