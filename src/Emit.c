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
 * TODO: make this a var args func in the vein of customErrorString()?
 * Parameters:
 *		s : the string to be made into an ASC comment
 */
void emitComment(char *s)
{
	size_t len = 0;
	char *comment = NULL; 

	CHECK_CAN_EMIT(s);
	
	len = strlen(s) + 3;	/* + 3 for '#', '\n', and safety '\0' */
	allocStmt(&comment, len);
	
	/* Turn string s into a asc comment */
	comment[0] = '#';
	strncat(comment + 1, s, len - 3); 
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
 *		s: the symbol form whom we need to declare space on the stack
 */
void emitVarDecl(Symbol *s)
{
	char *stmt = NULL;

	CHECK_CAN_EMIT(s);
	allocStmt(&stmt, STMT_LEN);
	snprintf(stmt, STMT_LEN - 1,"\t\tADJUST %d\n", s->size);
	appendStmt(&stmts, stmt);
}


