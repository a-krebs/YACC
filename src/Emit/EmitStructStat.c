/*
 * Module implementing functions generating asc code for structured
 * statements like if-then, if-then-else, while, continue, end
 */

#include "EmitStructStat.h"

/*
 * Emit ASC code to start an if statement.
 * Assumes the correspoding expression has already been emitted
 *
 * Note that both IF-THEN-ELSE and IF-THEN statements
 * reserve two labels, but only one is ever used in IF-THEN statements.
 */
void emitIfStat(Symbol *s) {
	CHECK_CAN_EMIT(s);
	/* reserve labels for THEN and ELSE */
	reserveLabels(labelStack, 2);

	emitComment("IF expr THEN. If 'expr' is false skip to %s%d",
	    LABEL_PREFIX, peekLabelStackTop(labelStack));
	emitStmt(STMT_LEN, "IFZ %s%d", 
	    LABEL_PREFIX, peekLabelStackTop(labelStack));
}


/*
 * Emit ASC code for a then statment as part of IF-THEN-ELSE.
 * Assumes the corresposding statement or matched_stat code has already
 * been emitted.
 */
void emitThenMatchedStat() {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(1);

	emitComment("Bottom of an IF-THEN.");
	emitComment("Either THEN was executed, so GOTO,");
	emitComment("or land at %s%d if 'expr' was false",
	    LABEL_PREFIX, peekLabelStackTop(labelStack));
	
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

	emitComment("Bottom of ELSE stat");
	emitStmt(STMT_LEN, "%s%d:",
	    LABEL_PREFIX, peekLabelStackTop(labelStack) + 1);
	popLabels(labelStack);
}


/*
 * Emit ASC code for a then statment as part of IF-THEN.
 * Assumes the corresposding statement or matched_stat code has already
 * been emitted.
 */
void emitThenStat() {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(1);

	emitComment("Bottom of IF-THEN as part of IF-THEN");
	emitStmt(STMT_LEN, "%s%d:",
	    LABEL_PREFIX, peekLabelStackTop(labelStack));
	popLabels(labelStack);
}


/*
 * Beginning of a while loop
 */
void emitBeginWhile() {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(1);

	/* Reserve loop labels. One for the top, one for the bottom */
	reserveLabels(loopLabelStack, 2);

	emitComment("Top of WHILE loop %s%d",
	    LOOP_PREFIX, peekLabelStackTop(loopLabelStack));
	emitStmt(STMT_LEN, "%s%d:",
	    LOOP_PREFIX, peekLabelStackTop(loopLabelStack));
}

/*
 * Check that expr is true to do loop, otherwise skip loop
 */
void emitWhileLoopCondCheck(Symbol *s) {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(s);

	emitComment("If expr is false, skip loop body");
	emitStmt(STMT_LEN, "IFZ %s%d",
	    LOOP_PREFIX, peekLabelStackTop(loopLabelStack) + 1);
}


/*
 * Emit code to return to the top of the current loop.
 */
void emitGotoLoopTop() {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(1);

	emitComment("Bottom of loop body for %s%d",
	    LOOP_PREFIX, peekLabelStackTop(loopLabelStack));
	emitStmt(STMT_LEN, "GOTO %s%d",
	    LOOP_PREFIX, peekLabelStackTop(loopLabelStack));
}


/*
 * Emit code for the end of a while loop.
 */
void emitEndWhile() {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(1);

	emitComment("End of WHILE loop %s%d",
	    LOOP_PREFIX, peekLabelStackTop(loopLabelStack));
	emitStmt(STMT_LEN, "%s%d:",
	    LOOP_PREFIX, peekLabelStackTop(loopLabelStack) + 1);

	popLabels(loopLabelStack);
}
