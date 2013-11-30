/*
 * Module implementing asc code generation functions needed by various
 * other code generation modules.
 */
#include "EmitUtils.h"


char *getAscFileName(char *palFileName)
{
 	int len = 0;
 	char *ascFileName = NULL;

 	len = strlen(palFileName) + 1;
 	if (len < 5) return NULL;	/* len < 5 => no .pal exten on file */ 

 	ascFileName = calloc(len, sizeof(char)); 

 	strncpy(ascFileName, palFileName, len); 
 	strncpy(ascFileName + len - 5, ".asc", 4); 

 	return ascFileName;
 } 


/*
 * Allocates memory for a statement of the given size and sets the given
 * character pointer to point to the allocated memory.  Performs error checking
 * such that it does not have to be done in every statement emitting function.
 * Parameters
 *		stmt: the address of a pointer to which we would like to
 *		    assign the address of the allocated memory
 *		len: the amount of memory to allocate
 */
void allocStmt(char **stmt, size_t len)
{
	*stmt = calloc(len, sizeof(char));
	if (!(*stmt)) err(1, "Failed to allocate memory for asc statement.");
}


/*
 * Produces asc comment from the given string and appends it to list of
 * ASC statements (to help with debugging)
 * Parameters:
 *		s : the string to be made into an ASC comment
 */
void emitComment(char *s, ...)
{
	static char cmt[MAX_COMMENT_LEN];
	va_list args;
	size_t len = 0;
	char *comment = NULL; 

	memset(cmt, '\0', MAX_COMMENT_LEN);

	va_start(args, s);
	vsnprintf(cmt, MAX_COMMENT_LEN - 1, s, args);
	va_end(args);

	cmt[MAX_COMMENT_LEN - 1] = '\0';
	
	len = strlen(cmt) + 4;	/* + 4 for '#', ' ', '\n', and safety '\0' */
	allocStmt(&comment, len);
	
	/* Turn string s into a asc comment */
	comment[0] = '#';
	comment[1] = ' ';
	strncat(comment + 2, cmt, len - 4); 
	comment[len - 2] = '\n';
	comment[len - 1] = '\0';

	/* Append comment to list of statements */
	appendStmt(&stmts, comment);
}

/*
 * Turns the given format string s into an ASC statement given additional
 * args and appends it to list of stmts.
 * Parameters
 *		len : length >= length of string s after being formatted
 *		s : the statement to be formatted
 *		... : arguments to format the string
 */
void emitStmt(int len, char *s, ...)
{
	va_list args;
	char *stmt = NULL, *formattedStr = NULL;

	allocStmt(&formattedStr, len);

	/* Create formatted string from args */
	va_start(args, s);
	vsnprintf(formattedStr, len - 1, s, args);	
	va_end(args);

	/* we add 4 to make room for '\t', '\t', '\n', '\0' */
	len = strlen(formattedStr) + 4;

	allocStmt(&stmt, len);
	
	/* Turn formatted string into ASC statement */
	stmt[0] = '\t';
	stmt[1] = '\t';
	strncat(stmt + 2, formattedStr, len - 4);
	stmt[len - 2] = '\n';
	stmt[len - 1] = '\0';

	free(formattedStr);
	appendStmt(&stmts, stmt);
}

 
/*  
 * Constructs the asc statement necessary to push the value of the variable 
 * constant symbol s on the top of the stack and appends it to the list 
 * of asc statements. 
 * Parameters: 
 *		s : the symbol whose value is to be placed on top of the stack
 * 
 */ 
void emitPushVarValue(Symbol *s) {
	emitPushVarValueCommon(s, s->offset, s->lvl);
}


/*  
 * Constructs the asc statement necessary to push the value of the variable 
 * constant symbol s from a function/procedure parameter on the top of the 
 * stack and appends it to the list of asc statements. The offset and level
 * must be passed by the caller
 *
 * Parameters: 
 *		s : the symbol whose value is to be placed on top of the stack
 * 
 */ 
void emitPushParmVarValue(Symbol *s, int offset, int level) {
	emitPushVarValueCommon(s, offset, level);
}


/*  
 * Constructs the asc statement necessary to push the value of the variable 
 * constant symbol s on the top of the stack and appends it to the list 
 * of asc statements. 
 *
 * Parameters: 
 *		s : the symbol whose value is to be placed on top of the stack
 *		offset: 
 *		level: display (lexical level)
 * 
 */ 
void emitPushVarValueCommon(Symbol *s, int offset, int level) { 
 	CHECK_CAN_EMIT(s); 
 	
	switch (getType(s)) {
	case BOOLEAN_T:
	case CHAR_T:
	case INTEGER_T:
	case REAL_T:
	case RECORD_T:
	case SCALARINT_T:
	{
		if (!isByReference(s)) { 
 			/*  
 			 * The variable has not been passed by reference, just 
 		 	* push the value stored in the stack 
 		 	*/ 
	 		emitStmt(STMT_LEN, "PUSH %d[%d]", offset, level);	 
	 	} else { 
	 		/*  
 			 * Else the variable has been passed by reference 
 			 * and we have to push the value of the variable 
			 * referenced by the address in the stack 
 			 */
 			emitStmt(STMT_LEN, "PUSH %d[%d]", offset, level); 
 			emitStmt(STMT_LEN, "PUSHI");	 
 	
		}
		break;
	}
	case STRING_T:
		//TODO implement this special case
		break;
	default:
		/* Function should not be called with var of any other type! */
		fprintf(stderr, "Trying to push value of a symbol of type which"
		    " has no type.\n");
		exit(1);
	}
}


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
		emitComment("Pushing index_val - index_lowerbound_val for"
		    " location calculation.");
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
		emitStmt(STMT_LEN, "PUSHA %d[%d]", arrayBase->offset,
		    arrayBase->lvl);
	}
	emitStmt(STMT_LEN, "ADDI");
}


/*
 * Emits the asc code necessary to push the value of the given symbol to the 
 * top of the stack.
 * Parameters
 * 		s : the symbol whose value is to be pushed onto the stack
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
		fprintf(stderr, "Trying to push value of a symbol which is not"
		    "of kind CONST_KIND or VAR_KIND.\n");
		exit(1);
	}
}


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
			//TODO implement this special case
			break;
		default:
			/* Should not be reached */
			break;
		}		

	}

}


/*
 * Reserve n labels.
 *
 * Parameters:
 * 	stack: the stack on which to reserve labels
 * 	n: number of labels to reserve
 */
void reserveLabels(struct labelStack *stack, int n) {
	if (stack == NULL) {
		err(EXIT_FAILURE, "Trying to puch to NULL labelStack");
	}
	if (n < 1) {
		err(EXIT_FAILURE, "Trying to reserve less than 1 label");
	}

	/* make sure stack is not full */
	if (stack->stackSize == (stack->ltop + 1)) {
		growLabelStack(stack);
	}

	/* reserve the labels */
	stack->ltop += 1;
	stack->stack[stack->ltop] = stack->label;
	stack->label += n;
}


/*
 * Pop labels off the label stack.
 *
 * Parameters:
 * 	stack: the stack from which to pop labels.
 */
void popLabels(struct labelStack *stack) {
	stack->ltop -= 1;
}

/*
 * Check the value at the top of the stack without changing it.
 * Errors and exits if the stack does not have labels reserved
 *
 * Parameters:
 * 	stack: the stack at which to look
 *
 * Return:
 * 	the label at the top of the stack
 */
int peekLabelStackTop(struct labelStack *stack) {
	if (stack->ltop < 0) {
		err(EXIT_FAILURE, "Peeking at label stack without having any "
		    "labels reserved.");
	}

	return stack->stack[stack->ltop];
}


/*
 * Create a new struct labelStack from which labels can be reserved 
 *
 * Return:
 * 	A pointer to the new labelStack struct.
 */
struct labelStack *newLabelStack() {
	struct labelStack *newStack = NULL;
	
	newStack = calloc(1, sizeof(struct labelStack));
	if (newStack == NULL) {
		err(EXIT_FAILURE, "Failed to allocate memory for label stack!");
	}
	newStack->ltop = -1;
	growLabelStack(newStack);	
	return newStack;
}


/*
 * Grow a label stack by DEFAULT_LABEL_STACK_SIZE.
 *
 * Parameters:
 * 	stack: the label stack to grow
 */
void growLabelStack(struct labelStack *stack) {
	stack->stackSize += DEFAULT_LABEL_STACK_SIZE;
	stack->stack = realloc(stack->stack, stack->stackSize*sizeof(int));
	if (stack->stack == NULL) {
		err(EXIT_FAILURE, "Failed to allocate memory for label stack!");
	}

	/* clear new memory from head of old array to end*/
	memset(
	    stack->stack + stack->stackSize - DEFAULT_LABEL_STACK_SIZE,
	    0,
	    DEFAULT_LABEL_STACK_SIZE);
}


/*
 * Destroy a label stack and set the pointer to NULL.
 *
 * Parameters:
 * 	stack: a double pointer to the label stack to destory
 */
void destroyLabelStack(struct labelStack **stack) {
	struct labelStack *s = *stack;

	/* free the internat stack array */
	free(s->stack);
	/* free the struct */
	free(s);
	/* set pointer to NULL */
	*stack = NULL;
}


/*
 * Increases the adjust counter for the current lexical level.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void increaseAdjustCounter() {
	int lexLevel = getCurrentLexLevel(symbolTable);

	adjustCounter[lexLevel] += 1;
}


/*
 * Resets the adjust counter for the current lexical level.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void resetAdjustCounter() {
	int lexLevel = getCurrentLexLevel(symbolTable);

	adjustCounter[lexLevel] = 0;
}


/*
 * Gets the adjust counter for the current lexical level.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
int getAdjustCounter() {
	return adjustCounter[getCurrentLexLevel(symbolTable)];
}
