/*b
 * Module implementing functionality with regard to asc code generation for
 * performing re
lational operations.
 */

#include "EmitRelational.h"


static void emitRelationalOperandValue(Symbol *);
static void emitRelationalPrep(Symbol *, Symbol *, int *);
static void emitRelationalSimpleTypeConversion(Symbol *, Symbol *, int *);	

/*
 * Performs conversion of the given simple types as necessary in order to
 * make the relational operation function as expected.
 * Parameters
 *		x : the LHS operand
 * 		y : the RHS operand
 */
static void emitRelationalSimpleTypeConversion(Symbol *x, Symbol *y, 
    int *opType)
{
	if ( (getType(x) == INTEGER_T) && (getType(y) == INTEGER_T) ) {

		/* No conversion to make */
		*opType = INTEGER_OPERATION;	

	} else if ((getType(x) == SCALARINT_T) && (getType(y) == SCALARINT_T)) {

		/* No conversion to make */
		*opType = INTEGER_OPERATION;

	} else if ( (getType(x) == REAL_T) && (getType(y) == REAL_T) ) {

		/* No conversion to make */
		*opType = REAL_OPERATION; 

	} else if ( (getType(x) == INTEGER_T) && (getType(y) == REAL_T) ) {
	
		/* Convert x to a a real value */
		emitComment("Converting %s to a real value.", x->name);
		emitStmt(STMT_LEN, "ADJUST -1");
		emitStmt(STMT_LEN, "ITOR");
		emitStmt(STMT_LEN, "ADJUST 1");
		*opType = REAL_OPERATION;

	} else if ( (getType(x) == REAL_T) && (getType(y) == INTEGER_T) ) {

		/* Convert y to a real value */
		emitComment("Converting %s to a real value.", y->name);
		emitStmt(STMT_LEN, "ITOR");
		*opType = REAL_OPERATION;
	}
}


/*
 * Determines if the value related to the given symbol is already on the stack.
 * If it is not, it generates the code necessary to place it there.
 * Parameter
 *		x : the symbol which relates the value for which we would like
 *		    to determine if its value is on the stack. 
 */
static void emitRelationalOperandValue(Symbol *x)
{
	if ( (x->isAddress) && (isSimpleType(getType(x))) ) {

		/* The value on top of the stack is an address and x is a
		 * simple type, therefore we need resolve the address into
		 * a value */
		emitPushAddressValue(x);

	} else if (x->kind == CONST_KIND) {

		emitPushSymbolValue(x);
	
	} else if (x->kind != TYPE_KIND) {
		/* If we are being passed a type kind, then x is the type symbol
		 * resultant from an operation that already occurred, so its
		 * value is already on the stack.  Else, we push its value */
		emitPushSymbolValue(x);
	}

}
/*
 * Given two symbols to be used in a relational operation, emitRelationalPrep()
 * generates the asc code to insure that the two required values are on the
 * top of the stack before the relational operator is applied.  Type conversion
 * is also performed as necessary.
 * Parameters
 *		x : the LHS operand
 *		y : the RHS operand
 */
static void emitRelationalPrep(Symbol *x, Symbol *y, int *opType)
{
	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	emitRelationalOperandValue(x);
	emitRelationalOperandValue(y);

	if ( (x->kind == CONST_KIND) && (y->kind == CONST_KIND) ) {
		/* Both LHS and RHS operand consts => we have evaluated the
		 * expr at the semantic level */
		*opType = NO_OP;
		return;
	}

	if (isSimpleType(getType(x))) 
	    emitRelationalSimpleTypeConversion(x, y, opType);
	else *opType = STRUCTURED_OPERATION;
}

void emitEqualsOp(Symbol *x, Symbol *y)
{
	int opType;
	emitRelationalPrep(x, y, &opType);
	switch (opType) {
	case INTEGER_OPERATION:
		emitStmt(STMT_LEN, "EQI");
		break;
	case REAL_OPERATION:
		emitStmt(STMT_LEN, "EQR");
		break;
	case STRUCTURED_OPERATION:
		emitComment("We are performing 'eq' op on two structured " 
		    "types");
		emitComment("We call a pre-defined function to do the"
		    "operation ");
		emitStmt(STMT_LEN, "PUSH %d", getStrSymLen(x));
		emitStmt(STMT_LEN, "CALL 0, __do_str_eq_op");
		emitComment("__do_str_eq_op overwrote our first param, so we");
		emitComment("only adjust -2");
		emitStmt(STMT_LEN, "ADJUST -2");	
		break;
	case NO_OP:
		/* Nothing to do */
		break;
	}
}

void emitInequalityOp(Symbol *x, Symbol *y)
{
	int opType;
	emitRelationalPrep(x, y, &opType);
	
	switch (opType) {
	case INTEGER_OPERATION:
		emitStmt(STMT_LEN, "EQI");
		emitStmt(STMT_LEN, "NOT");
		break;
	case REAL_OPERATION:
		emitStmt(STMT_LEN, "EQR");
		emitStmt(STMT_LEN, "NOT");
		break;
	case STRUCTURED_OPERATION:
	
		emitComment("We are performing 'eq' op on two structured " 
		    "types");
		emitComment("We call a pre-defined function to do the "
		    "operation");
		
		emitStmt(STMT_LEN, "PUSH %d", getStrSymLen(x));
		emitStmt(STMT_LEN, "CALL 0, __do_str_eq_op");

		emitComment("__do_str_lt_op overwrote our first param, so we");
		emitComment("only adjust -2");

		emitStmt(STMT_LEN, "ADJUST -2");	

		break;
	case NO_OP:
		/* Nothing to do */
		break;
	}
}

/*
 * Emits asc code to perform x < y operation.
 */
void emitLTOp(Symbol *x, Symbol *y) {
	int opType;
	emitRelationalPrep(x, y, &opType);

	switch (opType) {
	case INTEGER_OPERATION:
		emitStmt(STMT_LEN, "LTI");
		break;
	case REAL_OPERATION:
		emitStmt(STMT_LEN, "LTR");
		break;
	case STRUCTURED_OPERATION:
	
		emitComment("We are performing 'eq' op on two structured " 
		    "types");
		emitComment("We call a pre-defined function to do the"
		    "operation ");
		
		emitStmt(STMT_LEN, "PUSH %d", getStrSymLen(x));
		emitStmt(STMT_LEN, "CALL 0, __do_str_lt_op");

		emitComment("__do_str_lt_op overwrote our first param, so we");
		emitComment("only adjust -2");

		emitStmt(STMT_LEN, "ADJUST -2");	

		break;
	case NO_OP:
		/* Nothing to do */
		break;
	}
}

/*
 * Emit asc code to perform x <= y operation.
 */
void emitLTEOp(Symbol *x, Symbol *y)
{
	int opType;
	emitRelationalPrep(x, y, &opType);

	switch(opType) {
	/* x <= y <=> NOT(x > y) */
	case INTEGER_OPERATION:
		emitStmt(STMT_LEN, "GTI");
		emitStmt(STMT_LEN, "NOT");
		break;
	case REAL_OPERATION:
		emitStmt(STMT_LEN, "GTR");
		emitStmt(STMT_LEN, "NOT");
		break;
	case STRUCTURED_OPERATION:
		
		emitComment("We are performing 'LTE' op on two structured " 
		    "types");
		emitComment("We call a pre-defined function to do the"
		    "operation");
		emitComment("We perform x > y operation, then negate the "
		    "result");
		
		emitStmt(STMT_LEN, "PUSH %d", getStrSymLen(x));
		emitStmt(STMT_LEN, "CALL 0, __do_str_gt_op");

		emitComment("__do_str_gt_op overwrote our first param, so we");
		emitComment("only adjust -2");

		emitStmt(STMT_LEN, "ADJUST -2");
		emitStmt(STMT_LEN, "NOT");	

		break;
	case NO_OP:
		/* Nothing to do */
		break;
	}
}

/*
 * Emits asc code to perform x > y operation.
 */
void emitGTOp(Symbol *x, Symbol *y) {
	int opType;
	emitRelationalPrep(x, y, &opType);

	switch (opType) {
	case INTEGER_OPERATION:
		emitStmt(STMT_LEN, "GTI");
		break;
	case REAL_OPERATION:
		emitStmt(STMT_LEN, "GTR");
		break;
	case STRUCTURED_OPERATION:
		
		emitComment("We are performing 'gt' op on two structured " 
		    "types");
		emitComment("We call a pre-defined function to do the"
		    "operation");
		
		emitStmt(STMT_LEN, "PUSH %d", getStrSymLen(x));
		emitStmt(STMT_LEN, "CALL 0, __do_str_gt_op");

		emitComment("__do_str_gt_op overwrote our first param, so we");
		emitComment("only adjust -2");

		emitStmt(STMT_LEN, "ADJUST -2");
break;
	case NO_OP:
		/* Nothing to do */
		break;
	}
}


/*
 * Emits asc code to perform x >= y operation.
 */
void emitGTEOp(Symbol *x, Symbol *y)
{
	int opType;
	emitRelationalPrep(x, y, &opType);

	switch(opType) {
	/* x >= y <=> NOT(x < y) */
	case INTEGER_OPERATION:
		emitStmt(STMT_LEN, "LTI");
		emitStmt(STMT_LEN, "NOT");
		break;
	case REAL_OPERATION:
		emitStmt(STMT_LEN, "LTR");
		emitStmt(STMT_LEN, "NOT");
		break;
	case STRUCTURED_OPERATION:
		
		emitComment("We are performing 'gte' op on two structured " 
		    "types");
		emitComment("We call a pre-defined function to do the"
		    "operation");
		emitComment("We perform x < y operation, then negate the "
		    "result");
		
		emitStmt(STMT_LEN, "PUSH %d", getStrSymLen(x));
		emitStmt(STMT_LEN, "CALL 0, __do_str_lt_op");

		emitComment("__do_str_lt_op overwrote our first param, so we");
		emitComment("only adjust -2");

		emitStmt(STMT_LEN, "ADJUST -2");
		emitStmt(STMT_LEN, "NOT");	
		break;
	case NO_OP:
		/* Nothing to do */
		break;
	}
}

