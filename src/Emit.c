/*
 * Module implementing ASC code generating functionality.
 */

#include "Emit.h"

int doNotEmit;

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

	CHECK_CAN_EMIT(s);

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
	strncat(comment + 2, cmt, len - 3); 
	comment[len - 2] = '\n';
	comment[len - 1] = '\0';

	/* Append comment to list of statements */
	appendStmt(&stmts, comment);
}

/*
 * Constructs the asc statement necessary to push the value of the variable
 * / constant symbol s on the top of the stack and appends it to the list
 * of asc statements.
 * Parameters:
 *		s : the symbol whose value is to be placed on top of the stack
 */
void emitPushVarValue(Symbol *s)
{
	char *stmt = NULL;

	CHECK_CAN_EMIT(s);

	allocStmt(&stmt, STMT_LEN);
	
	if (!isByReference(s)) {
		/* 
		 * The variable has not been passed by reference, just
		 * push the value stored in the stack
		 */
		snprintf(stmt, STMT_LEN - 1, "\t\tPUSH %d[%d]\n", s->offset,
		    s->lvl);	
	} else {
		/* 
		 * Else the variable has been passed by reference 
		 * and we have to push the value of the variable referenced by
		 * the address in the stack
		 */
		snprintf(stmt, STMT_LEN -1, "\t\tPUSH %d[%d]\n", s->offset,
		    s->lvl);
		appendStmt(&stmts, stmt);
		allocStmt(&stmt, STMT_LEN);
		snprintf(stmt, STMT_LEN - 1, "\t\tPUSHI\n");
		appendStmt(&stmts, stmt);
	}
}

/*
 * Creates asc statement necessary to make room on the stack for the given
 * variable.
 * Parameters
 *		s: the symbol for whom we need to declare space on the stack
 */
void emitVarDecl(Symbol *s)
{
	char *stmt = NULL;

	CHECK_CAN_EMIT(s);

	emitComment("Make room on the stack for new var %s", s->name);	
	allocStmt(&stmt, STMT_LEN);
	snprintf(stmt, STMT_LEN - 1,"\t\tADJUST %d\n", s->size);
	appendStmt(&stmts, stmt);
}

/*
 * Creates asc statement necessary to make room on the stack for the given
 * constant and stores the value of the given constant in the location
 * allocated.
 * Parameters:
 *		s: the constant symbol whose value we need to store
 */
void emitConstDecl(Symbol *s)
{
	char *stmt = NULL;

	CHECK_CAN_EMIT(s);

	emitComment("Make room on the stack for new const %s.", s->name);
	allocStmt(&stmt, STMT_LEN);
	snprintf(stmt, STMT_LEN - 1, "\t\tADJUST 1\n");
	appendStmt(&stmts, stmt);

	switch (getType(s)) {
	case BOOLEAN_T:
		emitIntConstDecl(s, getConstVal(s)->Boolean.value);
		break;
	case CHAR_T:
		emitIntConstDecl(s, getConstVal(s)->Char.value);
		break;
	case INTEGER_T:
		emitIntConstDecl(s, getConstVal(s)->Integer.value);
		break;
	case REAL_T:
		emitRealConstDecl(s, getConstVal(s)->Real.value);
		break;
	case STRING_T:
		//TODO: implement this case
		break;
	default:
		/* Should not be reached */
		break;
	}

}

/*
 * Creates asc statement necessary to make room on the stack for the given
 * integer constant and stores the value of the constant in the location
 * allocated.
 * Parameters:
 *		s : the integer constant symbol whose value is to be stored
 *		value : the integer value of the constant symbol s 
 *
 */
void emitIntConstDecl(Symbol *s, int value)
{
	char *stmt = NULL;

	emitComment("Push const val = %d on stack, pop it into place.", value);
	allocStmt(&stmt, STMT_LEN);
	snprintf(stmt, STMT_LEN - 1, "\t\tCONSTI %d\n", value);
	appendStmt(&stmts, stmt);

	allocStmt(&stmt, STMT_LEN);
	snprintf(stmt, STMT_LEN - 1, "\t\tPOP %d[%d]\n", s->offset, s->lvl);
	appendStmt(&stmts, stmt);
}

void emitRealConstDecl(Symbol *s, float value)
{
	char *stmt = NULL;

	emitComment("Push const val = %f on stack, pop it into place.", value);
	allocStmt(&stmt, STMT_LEN);
	snprintf(stmt, STMT_LEN - 1, "\t\tCONSTR %f\n", value);
	appendStmt(&stmts, stmt);

	allocStmt(&stmt, STMT_LEN);
	snprintf(stmt, STMT_LEN - 1, "\t\tPOP %d[%d]\n", s->offset, s->lvl);
	appendStmt(&stmts, stmt);
	
}

void emitAddition(Symbol *x, Symbol *y)
{
	char *stmt = NULL;
	CHECK_CAN_EMIT(x);
	CHECK_CAN_EMIT(y);

	if ((getType(x) == INTEGER_T) && (getType(y) == INTEGER_T)) {
	
		/* Emit code to add two integers */
		emitAdditionIntInt(x, y);

	} else if ((getType(x) == REAL_T) && (getType(y) == REAL_T)) {

		/* Emit code to add two integers */
		emitAdditionRealReal(x, y);

	} else if ((getType(x) == INTEGER_T) && (getType(y) == REAL_T)) {
		/* 
		 * Emit code to change x to a real, then emit code to add
		 * two reals 
		 */		
	}
}

void emitAdditionIntInt(Symbol *x, Symbol *y)
{

}

void emitAdditionRealReal(Symbol *x, Symbol *y)
{
	
}

