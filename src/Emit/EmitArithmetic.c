/*
 * Module implementing functions generating asc code for performing 
 * arithmetic operations.
 */

#include "EmitArithmetic.h"

/*
 * Emits asc code to push necessary values of the correct type in order to
 * perform an arithmetic operation.  Sets the integer pointer result's value
 * to ARITHMETIC_RESULT_INTEGER or ARITHMETIC_RESULT_REAL such that caller
 * knows what type of arithmetic operation to perform (real or integer) and
 * the value on top of th estack.
 * Parameters:
 *		x : the LHS operand
 *		y : the RHS operand
 *		result : a pointer to an integer
 */
void emitArithmeticPrep(Symbol *x, Symbol *y, int *result)
{
	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	if ((getType(x) == INTEGER_T) && (getType(y) == INTEGER_T)) {
	
		/* Emit code to perform arithmetic operation on two integers */
		emitPushVarValue(x);
		emitPushVarValue(y);
		*result = ARITHMETIC_RESULT_INTEGER;

	} else if ((getType(x) == REAL_T) && (getType(y) == REAL_T)) {

		/* Emit code to arithmetic operaton on two reals */
		emitPushVarValue(x);
		emitPushVarValue(y);
		*result = ARITHMETIC_RESULT_INTEGER;

	} else if ((getType(x) == INTEGER_T) && (getType(y) == REAL_T)) {
		/* 
		 * Emit code to change x to a real, then emit code to perform
		 * arithmetic operation on two reals.
		 */
		emitPushVarValue(x);
		emitStmt(STMT_LEN, "ITOR");
		emitPushVarValue(y);
		*result = ARITHMETIC_RESULT_REAL;
	
	} else if ((getType(x) == REAL_T) && (getType(y) == INTEGER_T)) {
		/* 
		 * Emit code to change x to a real, then emit code to perform
		 * arithmetic operation on two reals.
		 */
		emitPushVarValue(y);
		emitStmt(STMT_LEN, "ITOR");
		emitPushVarValue(x);
		*result = ARITHMETIC_RESULT_REAL;
	}

}




/*
 * Emits asc code to perform an addition operation with the two given symbols
 * and leaves the result on top of the stack
 * Parameters:
 * 		x : the LHS operand
 * 		y : the RHS operand
 */
void emitAddition(Symbol *x, Symbol *y)
{
	int result;

	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	emitComment("Perform addition of %s %s and %s %s",
	    typeToString(getType(x)), x->name, 
	    typeToString(getType(y)), y->name);

	emitArithmeticPrep(x, y, &result);
	if (result == ARITHMETIC_RESULT_INTEGER) emitStmt(STMT_LEN, "ADDI");
	else emitStmt(STMT_LEN, "ADDR");

}

/*
 * Emits asc code to perform an addition operation with the two given
 * symbols and leaves the result on top of the stack.
 */
