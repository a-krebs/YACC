/*
 * Module implementing functionality with regard to asc code generation for
 * performing relational operations.
 */

#include "EmitRelational.h"


/*
 * Given two symbols to be used in a relational operation, emitRelationalPrep()
 * generates the asc code to insure that the two required values are on the
 * top of the stack before the relational operator is applied.
 */
void emitRelationalPrep(Symbol *x, Symbol *y)
{
	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	if ( (x->isAddress) && (isSimpleType(x)) ) {
		/* The value on top of the stack is an address and x is a
		 * simple type, therefore we need resolve the address into
		 * a value */
		emitPushArrayLocationValue(x);
	}

}
