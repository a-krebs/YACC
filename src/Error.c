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


/* 
 * Creates a new Error object based on the function args and appends
 * the error to the linked list of error kept during compilation.
 * Returns a pointer to the newly created Error for easier debugging.
 */
struct Error *
recordError(const char *s, int lineno, int colno) 
{
	struct Error * newError = NULL;
	size_t len = strlen(s);
	
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
	newError->msg = calloc(1, sizeof(char)*len+1);
	if (!newError->msg) {
		err(1, "Failed to allocate memory to record new error string");
		return;

	}
	newError->lineno = lineno;
	newError->colno = colno;
	strncpy(newError->msg, s, len);

	/* Append to linked list of errors appearing during compilation */
	appendError(&errors, newError);

	return newError;
}


/*
 * Creates a version of the error string suitable for printing
 * to the program listing and writes it to buf.
 * NOTE: it is incumbent upon the caller to free 
 */
void
createErrorString(char **buf, struct Error *e)
{

	int extraChars = 64;
	size_t size = sizeof(char)*(strlen(e->msg) + extraChars);
	if (!e) return; /* don't try to create string for NULL error */
	/* zero out buf in case it is being reused */
	*buf = calloc(1, size);
	if (!*buf) {
		err(1, "Failed to allocate memory to create err msg");
		return;
	}

	snprintf(*buf, size, "Error: %s (line %d, col %d)", 
		 e->msg, e->lineno, e->colno);
}

void 
printError(struct Error *e)
{
	fprintf(stdout, "%d Error: %s (%d, %d)\n", 
		e->lineno, e->msg, e->lineno, e->colno);
}

void
freeError(struct Error *e)
{
	if (!e) return;
	if (e->msg) free(e->msg);
	free(e);
}

