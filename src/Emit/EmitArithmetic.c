/*
 * Module implementing functions generating asc code for performing 
 * arithmetic operations.
 */

#include "EmitArithmetic.h"

static void emitArithmeticPrep(Symbol *, Symbol *, int *);

/*============================================================================
					API Functions
=============================================================================*/

/*
 * Emits the acs nessary to perform an division opertation with the
 * give two symbols. Result is left of top of stack.
 *
 * Parameters: 
 * 		x : the LHS operand
 * 		y : the RHS operand
 *
 * Returns: void
 */
void emitAddition(Symbol *x, Symbol *y) {
	genericArithConstruct(x, y, "addition", "ADDI", "ADDR");
}


/*
 * Emits the acs nessary to perform an subtraction opertation with the
 * give two symbols. Result is left of top of stack.
 *
 * Parameters: 
 * 		x : the LHS operand
 * 		y : the RHS operand
 *
 * Returns: void
 */
void emitSubtraction(Symbol *x, Symbol *y) {
	genericArithConstruct(x, y, "subtraction", "SUBI", "SUBR");
}


/*
 * Emits the acs nessary to perform an multiplication opertation with the
 * give two symbols. Result is left of top of stack.
 *
 * Parameters: 
 * 		x : the LHS operand
 * 		y : the RHS operand
 *
 * Returns: void
 */
void emitMultiplication(Symbol *x, Symbol *y) {
	genericArithConstruct(x, y, "mulitplication", "MULI", "MULR");
}


/*
 * Emits the acs nessary to perform an division opertation with the
 * give two symbols. Result is left of top of stack.
 *
 * Parameters: 
 * 		x : the LHS operand
 * 		y : the RHS operand
 *
 * Returns: void
 */
void emitDivision(Symbol *x, Symbol *y) {
	genericArithConstruct(x, y, "division", "DIVI", "DIVR");
}


/*
 * Emits the acs nessary to perform an mod opertation with the
 * give two symbols. Result is left of top of stack.
 *
 * Parameters: 
 * 		x : the LHS operand
 * 		y : the RHS operand
 *
 * Returns: void
 */
void emitMod(Symbol *x, Symbol *y) {
	int result;
	emitArithmCheckAndComment(x, y, "mod");

	emitArithmeticPrep(x, y, &result);
	emitStmt(STMT_LEN, "MOD");	
}


/*
 * Emits the acs nessary to perform an integer to real conversion.
 * Result is left of top of stack.
 *
 * Parameters: 
 * 		x : operand to convert
 *
 * Returns: void
 */
void emitITOR(Symbol *x) {
	CHECK_CAN_EMIT(x);

	emitComment("Perform ITRO of %s %s and %s %s",
	    	typeToString(getType(x)), x->name);	

	if ( getType(x) == INTEGER_T) {
		emitPushVarValue(x);
		emitStmt(STMT_LEN, "ITOR");
	}
}


/*
 * Emits the acs nessary to perform an real to integer conversion.
 * Result is left of top of stack.
 *
 * Parameters: 
 * 		x : operand to convert
 *
 * Returns: void
 */
void emitRTOI(Symbol *x) {
	CHECK_CAN_EMIT(x);

	emitComment("Perform RTOI of %s %s and %s %s",
	    	typeToString(getType(x)), x->name);	

	if ( getType(x) == REAL_T) {
		emitPushVarValue(x);
		emitStmt(STMT_LEN, "RTOI");
	}
}


/*=============================================================================
					Internals
=============================================================================*/


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
static void emitArithmeticPrep(Symbol *x, Symbol *y, int *result)
{
	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	printf("GOT %s, %s\n", x->name, y->name);

	if (x->wasArray) {
		/* the value for x on top of the stack is an address, we need
		 * to replace it with the value of x */
		emitPushArrayLocationValue(x);
	} else {

		emitPushSymbolValue(x);
	}
	if (y->wasArray) {
		/* the value for x on top of the stack is an address, we need
		 * to replace it with the value of x */
		emitStmt(STMT_LEN, "ADJUST -1");
		emitPushArrayLocationValue(y);
		emitStmt(STMT_LEN, "ADJUST +1");
	} else {

		emitPushSymbolValue(x);

	}

	if ((getType(x) == INTEGER_T) && (getType(y) == INTEGER_T)) {
	
		/* Emit code to perform arithmetic operation on two integers */
		*result = ARITHMETIC_RESULT_INTEGER;

	} else if ((getType(x) == REAL_T) && (getType(y) == REAL_T)) {

		/* Emit code to arithmetic operaton on two reals */
		*result = ARITHMETIC_RESULT_INTEGER;

	} else if ((getType(x) == INTEGER_T) && (getType(y) == REAL_T)) {
		/* 
		 * Emit code to change x to a real, then emit code to perform
		 * arithmetic operation on two reals.
		 */
		emitStmt(STMT_LEN, "ITOR");
		*result = ARITHMETIC_RESULT_REAL;
	
	} else if ((getType(x) == REAL_T) && (getType(y) == INTEGER_T)) {
		/* 
		 * Emit code to change x to a real, then emit code to perform
		 * arithmetic operation on two reals.
		 */
		emitStmt(STMT_LEN, "ITOR");
		*result = ARITHMETIC_RESULT_REAL;
	}
}


/*
 * Emits the acs nessary to perform generic arithmetic opertations with the
 * give two symbols. Result is left of top of stack.
 *
 * Parameters: 
 * 		x : the LHS operand
 * 		y : the RHS operand
 *
 * Returns: void
 */
void genericArithConstruct(Symbol *x, Symbol *y, char *opName, 
	char *ascIntName, char *ascRealName) 
{
	int result;

	emitArithmCheckAndComment(x, y, opName);
	emitArithmeticPrep(x, y, &result);

	if ( result == ARITHMETIC_RESULT_INTEGER) {
		emitStmt(STMT_LEN, ascIntName);
	}
	else {
		emitStmt(STMT_LEN, ascRealName);
	}
}	

/*
 * Generic check for two arithmetic operands for if we can emit.
 * Also, emits commit code.
 *
 * Parameters: 
 * 		x : the LHS operand
 * 		y : the RHS operand
 *		opName: name of operation
 *
 * Returns: void
 */
void emitArithmCheckAndComment(Symbol *x, Symbol *y, char *opName) {
	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	emitComment("Perform %s of %s %s and %s %s",
		opName,
	    	typeToString(getType(x)), x->name, 
	    	typeToString(getType(y)), y->name);
}

/*
 * Emits asc code to perform an addition operation with the two given
 * symbols and leaves the result on top of the stack.
 */
