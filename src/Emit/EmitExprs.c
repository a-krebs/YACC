#include "EmitExprs.h"

extern int yylineno;

/*
 * Given a list of indices and a base of array, this function emits the asc code
 * necessary to calculate location of the element indexed by the indices 
 * according to to the formula:
 * for index in indices:
 * 	location += (index_value - index_lower_bound) * base_type
 * Parameters
 *		arrayBase : the initial base of the array which the first index
 *		    is an index for
 *		indices : linked list of symbols of indices we are using to
 * 		    index the array
 */


void emitArrayElementLocation(Symbol* arrayBase, Symbol *indices)
{
	Symbol *arrayType = NULL;
	int onceThrough, lowVal, baseTypeSize;

	arrayType = getTypeSym(arrayBase);

	while (indices) {
		emitComment("Pushing index_val - index_lowerbound_val for");
		emitComment("location calculation.");
		emitPushSymbolValue(indices);
		lowVal = getArrayLowIndexValue(arrayType);
		emitStmt(STMT_LEN, "CONSTI %d", lowVal);
		emitStmt(STMT_LEN, "SUBI");
		
		emitComment("Pushing size of base type.");
		baseTypeSize = getArrayBaseSym(arrayType)->size;
		emitStmt(STMT_LEN, "CONSTI %d", baseTypeSize);
		emitStmt(STMT_LEN, "MULI");

		if (onceThrough) emitStmt(STMT_LEN, "ADDI");
		else onceThrough = 1;

		/* Prepare for next iteration */
		indices = indices->next;
		arrayType = getArrayBaseSym(arrayType);
	}

	/*
	 * If arrayBase is a symbol of kind VAR_KIND (as opposed to a TYPE_KIND)
	 * then we know that the location value we have calculated from the 
	 * indices needs to have the value of (a->offset)[a->lvl] (e.g., the
	 * absolute address referenced by this display offset) added to the
	 * location.  Else, if arrayBase is an array type, then we make a 
	 * call to ADDI as we know in this case we must have previously 
	 * calculated some location value and left it on top of the stack.
	 */
	if (arrayBase->kind == VAR_KIND) {
		emitComment("We now push the base address of the array");
		emitPushVarAddress(arrayBase);
	}
	emitStmt(STMT_LEN, "ADDI");
}

/*
 * Emits the asc code necessary to push the value of the given symbol which is 
 * of kind VAR_KIND to top of the stack.
 * Parameters
 * 		s : the symbol of kind VAR_KIND whose value is to be pushed
 *		     onto the stack
 */
void emitPushSymbolValue(Symbol *s)
{
	CHECK_CAN_EMIT(s);

	switch (s->kind) {
	case CONST_KIND:
		emitPushConstValue(s);
		break;
	case VAR_KIND:
		emitPushVarValue(s);
		break;
	default:
		/* Should not be reached */
		break;
	}

	
}

/*
 * EMits the asc code necessary to push the value of the given symbol of
 * kind CONST_KIND to the top of the stack.  Handles both the case where
 * the symbol is named and the case where the symbol is anonymous.
 * Parameter
 *		s : the symbol of kidn CONST_KIND whose value is to be pushed
 *		    onto the stack.
 *
 */
void emitPushConstValue(Symbol *s)
{
	CHECK_CAN_EMIT(s);

	if (s->name) {
		/* 
		 * The const symbol is named and so its value is saved in the
		 * stack somewhere.
		 */
		emitComment("Pushing value of const %s of type %s onto stack.",
		    s->name, typeToString(getType(s)));
		emitStmt(STMT_LEN, "PUSH %d[%d]", s->offset, s->lvl);
	
	} else {
		/* It is an anonymous const value, so its value is already
		 * on the stack and we do nothing */
		//TODO: the times they are a-changin'
		emitComment("Pushing anonymous constant value of type %s",
		    typeToString(getType(s)));
		emitPushAnonConstValue(s);	
	}

}

void emitPushAnonConstValue(Symbol *s)
{
	CHECK_CAN_EMIT(s);

	switch (getType(s)) {
	case BOOLEAN_T:
		emitStmt(STMT_LEN, "CONSTI %d", 
		    getConstVal(s)->Boolean.value);
		break;
	case CHAR_T:
		emitStmt(STMT_LEN, "CONSTI %d",
		    getConstVal(s)->Char.value);
		break;
	case INTEGER_T:
		emitStmt(STMT_LEN, "CONSTI %d",
		    getConstVal(s)->Integer.value);
		break;
	case REAL_T:
		emitStmt(STMT_LEN, "CONSTI %f",
		    getConstVal(s)->Real.value);
		break;
	case SCALARINT_T:
		emitStmt(STMT_LEN, "CONSTI %d",
		    getConstVal(s)->Integer.value);
		break;
	case STRING_T:
		emitPushStringLiteralValue(s);
		break;
	default:
		break;
	}		
}


/*
 * Constructs the asc statement(s) necessary to push the address of the variable
 * symbol s on top of the stack (in preparation for an assignment operation)
 * Parameters
 *		s : the symbol whose address is to be placed on top of the stack
 */
void emitPushVarAddress(Symbol *s)
{
	CHECK_CAN_EMIT(s);

	switch(getType(s)) {
	case ARRAY_T:
	case BOOLEAN_T:
	case CHAR_T:
	case INTEGER_T:
	case REAL_T:
	case RECORD_T:
	case SCALARINT_T:
	{
		if (!isByReference(s)) {
			/* Not passed by reference, so we push the address
			 * referenced by (offset)[lvl] */
			emitStmt(STMT_LEN, "PUSHA %d[%d]", s->offset,
			    s->lvl);		
		} else {
			/* Else, var was passed by reference so the value
			 * that is stored at (offset)[lvl] is the address
			 * to which we ultimately want to assign a new value */
			emitStmt(STMT_LEN, "PUSH %d[%d]", s->offset, s->lvl);
		}
	break;
	}
	default:
		return;
		break;
	}
	
}

/*  
 * Constructs the asc statement(s) necessary to push the value of the variable 
 * / constant symbol s on the top of the stack and appends it to the list 
 * of asc statements. 
 * Parameters: 
 *		s : the symbol whose value is to be placed on top of the stack
 * 
 */ 
void emitPushVarValue(Symbol *s) 
{ 
 	CHECK_CAN_EMIT(s); 
 	
	switch (getType(s)) {
	case ARRAY_T:
		if (!isByReference(s)) { 
	 		emitStmt(STMT_LEN, "PUSHA %d[%d]", s->offset, s->lvl);	 
	 	} else { 
 			emitStmt(STMT_LEN, "PUSH %d[%d]", s->offset, s->lvl); 
		}
		break;
	case BOOLEAN_T:
	case CHAR_T:
	case INTEGER_T:
	case REAL_T:
	case SCALARINT_T:
	{
		if (!isByReference(s)) { 
 			/*  
 			 * The variable has not been passed by reference, just 
 		 	* push the value stored in the stack 
 		 	*/ 
	 		emitStmt(STMT_LEN, "PUSH %d[%d]", s->offset, s->lvl);	 
	 	} else { 
	 		/*  
 			 * Else the variable has been passed by reference 
 			 * and we have to push the value of the variable 
			 * referenced by the address in the stack 
 			 */
 			emitStmt(STMT_LEN, "PUSH %d[%d]", s->offset, s->lvl); 
 			emitStmt(STMT_LEN, "PUSHI");	 
 	
		}
		break;
	}
	case STRING_T:
		//TODO implement this special case
		break;
	default:
		/* Else function is of type with no value, do nothing */
		return;	
	}
}

/*
 * Given that the address of some value is currently on top of
 * the stack, the function emits the asc code necessary to replace this
 * addres with the actual value of the element.
 */
void emitPushAddressValue(Symbol *s)
{
	CHECK_CAN_EMIT(s);

	switch (getType(s)) {
	case ARRAY_T:
		/* We never push an entire array of values onto the stack */
		break;
	case BOOLEAN_T:
	case CHAR_T:
	case INTEGER_T:
	case SCALARINT_T:
	case REAL_T:
		emitStmt(STMT_LEN, "PUSHI");
		break;
	case SCALAR_T:
		//TODO: test if this case occurs
		break;
	default:
		/* Should not be reached */
		break;
	}
}

/*
 * Generates the asc code necessary to perfrom the assignment of the array
 * y to the array x. (essentially a memory copy)
 * Parameters
 *		x : the array variable whose value is to be assigned, we have
 *		    that the base address of the array is the second value
 *		    on the stack
 *		y : the array variable whose value x will be assigned, we have
 *		    that the base address of the array is the first value
 *		    on the stack
 */
void emitArrayAssignment(Symbol *x, Symbol *y)
{
	if (y->kind == VAR_KIND) {
		/* If y is an array and a var_kind, then the RHS of the 
		 * assignment operation has never undergone indexing and thus
		 * the address of y is not on the stack.  We push its value
		 * now */
		if (!isByReference(y)) { 
	 		emitStmt(STMT_LEN, "PUSHA %d[%d]", y->offset, y->lvl);	 
	 	} else { 
 			emitStmt(STMT_LEN, "PUSH %d[%d]", y->offset, y->lvl); 
		}
	}
	emitComment("Calling pre-defined function __do_array_assignment");
	emitComment("First, we place the array size on the stack.");
	emitStmt(STMT_LEN, "CONSTI %d", getTypeSym(x)->size);
	emitStmt(STMT_LEN, "CALL 0, __do_array_assignment");
	emitComment("Array assignment done; kick local params off the stack");
	emitStmt(STMT_LEN, "ADJUST -3");
}

/*
 * Generates the asc code necessary to perform the assignment of the value y
 * to the variable x.
 * Parameters
 *		x : the variable receiving the value
 *		y : the const or type symbol of the value x will receive
 */
void emitAssignmentOp(Symbol *x, Symbol *y)
{
	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	/* 
	 * When we enter this function, it is the case that the address of
	 * the variable x appears below the value of the symbol y on the stack.
	 */
	if (getType(x) == ARRAY_T || getType(x) == RECORD_T) {
		/* We are doing an array assignment.  Let's let the specialist
		 * handle this one. */
		emitArrayAssignment(x, y);
		return;
	}

	if (y->isAddress) {
		emitComment("Value of y is address, convert to actual value");
		emitPushAddressValue(y);
	}

	// TODO : factor the two conditionals below out into its own function
	if (y->kind == VAR_KIND) {
		emitComment("RHS of assignment operation is a single variable "
		    "value.");
		emitComment("So we push its value now as it was not pushed "
		    "before.");
		emitStmt(STMT_LEN, "PUSH %d[%d]", y->offset, y->lvl);
	}

	if ( (y->kind == CONST_KIND) ) {
		emitComment("RHS of assignment operation is a const, so its "
		    "value was not");
		emitComment("pushed before.  So, we push it now.");
		emitPushSymbolValue(y);	
	}

	emitComment("Assigning a value to %s", x->name);

	switch (getType(x)) {
	case BOOLEAN_T:
	case CHAR_T:
	case INTEGER_T:
		/* No checking to do, simply make the assignment */
		emitStmt(STMT_LEN, "POPI");
		break;
	case REAL_T:
		if (getType(y) == REAL_T) emitStmt(STMT_LEN, "POPI");
		else {
			/* Else y is an integer and we have to convert
 			 * it to a real */
			emitStmt(STMT_LEN, "ITOR");
			emitStmt(STMT_LEN, "POPI");
		}
	default:
		/* No other types can have values */
		break;

	}
}

/*
 * Emits asc code which calculate the address of the given field with respect
 * the given record.
 * Parameters
 *		field : the field whose address we want to calculate
 *		record : symbol of var_kind which has type record_t, field
 *		    is a field value in this record.
 */
void emitPushRecordFieldAddress(Symbol *record, Symbol *field)
{
	CHECK_CAN_EMIT(record);
	CHECK_CAN_EMIT(field);

	emitComment("Calculating offset of record field %s in record %s",
	    field->name, record->name);

	if (record->isRecordHead) {
		/* If the record is the record head, we have to push
		 * the absolute address referenced by its offset/lexical
		 * lvl values */
		emitComment("%s is a record head, so we push its "
		    "address", record->name);
		emitStmt(STMT_LEN, "PUSHA %d[%d]", record->offset,
		    record->lvl);
	}
	emitStmt(STMT_LEN, "CONSTI %d", field->offset);
	emitStmt(STMT_LEN, "ADDI", field->offset);
}


void emitPushStringLiteralValue(Symbol *s)
{
	char *str;
	int i, strlen;

	str = getConstVal(s)->String.str;
	strlen = getConstVal(s)->String.strlen;

	emitComment("Allocating memory for string literal.");
	emitStmt(STMT_LEN, "ALLOC %d", strlen);
	emitComment("We now push the values in the string constant ");
	emitComment("onto the stack.");

	for (i = strlen-1; i >= 0; i--) {
		emitStmt(STMT_LEN, "CONSTI %d", *(str + i)); 
	}

	emitComment("We push the length of the string onto the stack");
	emitStmt(STMT_LEN, "CONSTI %d", strlen);

	emitComment("We call the pre-defined function which will store the ");
	emitComment("appropriate values at the allocated memory location");
	emitStmt(STMT_LEN, "CALL 0, __store_string_values");

	emitComment("On return, we leave the allocated address on the stack");
	emitStmt(STMT_LEN, "ADJUST -%d", strlen + 1);
	
	emitComment("Now we change the address we save such that elements");
	emitComment("appear in increasing order from this address so it is");
	emitComment("as if they were on the stack (for compatability reasons)");
	emitStmt(STMT_LEN, "CONSTI -%d", strlen - 1);
	emitStmt(STMT_LEN, "ADDI");
}




