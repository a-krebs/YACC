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
