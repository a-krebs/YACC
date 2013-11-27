/*
 * Module implementing functions generating asc code for performing 
 * arithmetic operations.
 */

#include "EmitArithmetic.h"

/*
 * Emits asc code to perform an addition operation with the two given symbols
 * and leaves the result on top of the stack
 * Parameters:
 * 		x : the LHS operand
 * 		y : the RHS operand
 */
void emitAddition(Symbol *x, Symbol *y)
{
	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	emitComment("Perform addition of %s %s and %s %s",
	    typeToString(getType(x)), x->name, 
	    typeToString(getType(y)), y->name);

	if ((getType(x) == INTEGER_T) && (getType(y) == INTEGER_T)) {
	
		/* Emit code to add two integers */
		emitPushVarValue(x);
		emitPushVarValue(y);
		emitStmt(STMT_LEN, "ADDI");

	} else if ((getType(x) == REAL_T) && (getType(y) == REAL_T)) {

		/* Emit code to add two REALS */
		emitPushVarValue(x);
		emitPushVarValue(y);
		emitStmt(STMT_LEN, "ADDR");

	} else if ((getType(x) == INTEGER_T) && (getType(y) == REAL_T)) {
		/* 
		 * Emit code to change x to a real, then emit code to add
		 * two reals 
		 */
		emitPushVarValue(x);
		emitStmt(STMT_LEN, "ITOR");
		emitPushVarValue(y);
		emitStmt(STMT_LEN, "ADDR");
			
	} else if ((getType(x) == REAL_T) && (getType(y) == INTEGER_T)) {
		/* 
		 * Emit code to change y to a real, then emit code to add
		 * two reals 
		 */
		emitPushVarValue(y);
		emitStmt(STMT_LEN, "ITOR");
		emitPushVarValue(x);
		emitStmt(STMT_LEN, "ADDR");
			
	}
}
