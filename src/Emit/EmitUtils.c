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
 * Concatenate the given prefix, s, and suffix, and append the resulting
 * string to the given StmtLL.
 * Parameters:
 * 	ll: the StmtLL to which to append
 * 	prefix: string to prefix to s
 * 	s: string
 * 	suffix: string to postfix to s
 */
void emitStr(StmtLL **ll, char *prefix, char *s, char *suffix) {
	char *stmt = NULL;
	int prefixLen = 0;
	int sLen = 0;
	int suffixLen = 0;
	int stmtLen = 0;

	prefixLen = strlen(prefix);
	sLen = strlen(s);
	suffixLen = strlen(suffix);

	stmtLen = prefixLen + sLen + suffixLen;

	/* allocate for statment. +1 for null-termination */
	stmt = calloc(stmtLen + 1, sizeof(char));
	if (!(stmt)) err(EXIT_FAILURE,
	    "Failed to allocate memory for asc statement.");

	/* copy prefix into stmt */
	strncpy(stmt, prefix, prefixLen);

	/* copy s into stmt */
	strncpy(stmt + prefixLen, s, sLen);

	/* copy suffix into stmt */
	strncpy(stmt + prefixLen + sLen, suffix, suffixLen);

	/* append to given StmtLL */
	appendStmt(ll, stmt);
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

	memset(cmt, 0, MAX_COMMENT_LEN);

	/* create a formatted string from args */
	va_start(args, s);
	vsnprintf(cmt, MAX_COMMENT_LEN - 1, s, args);
	va_end(args);

	emitStr(&stmts, "\t\t# ", cmt, "\n");
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
	char *stmt = NULL;

	stmt = calloc(len + 1, sizeof(char));

	/* Create formatted string from args */
	va_start(args, s);
	vsnprintf(stmt, len, s, args);	
	va_end(args);

	emitStr(&stmts, "\t\t", stmt, "\n");
}


/*
 * Emits a blank line.
 */
void emitBlankLine() {
	emitStr(&stmts, "", "", "\n");
}


/*
 * Emit a seperator line.
 */
void emitSepLine() {
	emitComment("#######################################################");
}

 
/*  
 * Constructs the asc statement necessary to push the value of the variable 
 * constant symbol s on the top of the stack and appends it to the list 
 * of asc statements. 
 * Parameters: 
 *		s : the symbol whose value is to be placed on top of the stack
 * 
 */ 
// void emitPushVarValue(Symbol *s) {
	// emitPushVarValueCommon(s, s->offset, s->lvl);
// }


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
// void emitPushParmVarValue(Symbol *s, int offset, int level) {
	// emitPushVarValueCommon(s, offset, level);
// }


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
// void emitPushVarValueCommon(Symbol *s, int offset, int level) { 
//  	CHECK_CAN_EMIT(s); 
 	
// 	switch (getType(s)) {
// 	case BOOLEAN_T:
// 	case CHAR_T:
// 	case INTEGER_T:
// 	case REAL_T:
// 	case RECORD_T:
// 	case SCALARINT_T:
// 	{
// 		if (!isByReference(s)) { 
//  			/*  
//  			 * The variable has not been passed by reference, just 
//  		 	* push the value stored in the stack 
//  		 	*/ 
// 	 		emitStmt(STMT_LEN, "PUSH %d[%d]", offset, level);	 
// 	 	} else { 
	 		  
//  			 * Else the variable has been passed by reference 
//  			 * and we have to push the value of the variable 
// 			 * referenced by the address in the stack 
 			 
//  			emitStmt(STMT_LEN, "PUSH %d[%d]", offset, level); 
//  			emitStmt(STMT_LEN, "PUSHI");	 
 	
// 		}
// 		break;
// 	}
// 	case STRING_T:
// 		//TODO implement this special case
// 		break;
// 	default:
// 		/* Function should not be called with var of any other type! */
// 		fprintf(stderr, "Trying to push value of a symbol of type which"
// 		    " has no type.\n");
// 		exit(1);
// 	}
// }


/*
 * Turns the given format string s into an ASC statement given additional
 * args and appends it to list of stmts.
 * Parameters
 *		len : length >= length of string s after being formatted
 *		s : the statement to be formatted
 *		... : arguments to format the string
 */
void emitLabel(int len, char *s, ...)
{
	va_list args;
	char *stmt = NULL;

	stmt = calloc(len + 1, sizeof(char));

	/* Create formatted string from args */
	va_start(args, s);
	vsnprintf(stmt, len, s, args);	
	va_end(args);

	emitStr(&stmts, "", stmt, "\n");	
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
 * Gets the adjust counter for the current lexical level.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
int getAdjustCounter() {
	return getLocalSymbolCount(symbolTable);
}


/*
 * Gets the return offset of a function
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
int getReturnOffset() {
	return getLocalParamSymbolCount(symbolTable);
}
