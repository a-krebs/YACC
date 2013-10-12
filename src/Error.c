/*
 * Provides/defines functionality as it regards to 
 * error reporting and tracking.
 *
*/

#include <ctype.h>
#include <err.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Error.h"
#include "ErrorLL.h"


int nErrors = 0;
static int eof = 0; /* flag set to detect the end of file */


/* 
 * Creates a new Error object based on the function args and appends
 * the error to the linked list of error kept during compilation.
 * Returns a pointer to the newly created Error for easier debugging.
 */
struct Error *
recordError(const char *s, int lineno) 
{
	struct Error * newError = NULL;
	
	/* Update number of error which have appeared during compilation  */
	nErrors++;

	/* Construct new error given function args */
	newError = calloc(1, sizeof(struct Error));
	if (newError == NULL) {
		/* 
		 * we've run out of memory ... 
		 * do we stop compiling?
		 */
		err(1, "Failed to allocate memory to record new error.");
		return;
	}
	newError->lineno = lineno;
	strncpy(newError->msg, s, ERR_STRSIZE);

	/* Append to linked list of errors appearing during compilation */
	appendError(&errors, newError);

	return newError;
}


void 
printError(struct Error *e)
{
	fprintf(stdout, "%d Error: %s\n", e->lineno, e->msg);
}

