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
struct Error *recordError(const char *s, int lineno, int colno) 
{
	struct Error * newError = NULL;
	size_t len = strlen(s);
	
	/* 
	 * Update number of error which have appeared during compilation  
	 * We will not try to report more errors than a given maximum.
	 */
	if (nErrors < MAXERRORS) nErrors++;

	/* Construct new error given function args */
	newError = calloc(1, sizeof(struct Error));
	if (newError == NULL) {
		err(1, "Failed to allocate memory to record new error.");
		return NULL;
	}
	newError->msg = calloc(1, sizeof(char)*len+1);
	if (!newError->msg) {
		err(1, "Failed to allocate memory to record new error string");
		return NULL;

	}
	newError->lineno = lineno;
	newError->colno = colno;
	strncpy(newError->msg, s, len);

	/* Append to linked list of errors appearing during compilation */
	if (nErrors < MAXERRORS) {
		appendError(&errors, newError);
		return newError;
	} else return NULL;
}


/*
 * Creates a version of the error string suitable for printing
 * to the program listing and writes it to buf.
 * NOTE: it is incumbent upon the caller to free memory allocated. 
 */
void createErrorString(char **buf, struct Error *e)
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

/*
 * Creates an error string from a variable number of parameters.
 * e.g.,
 * customErrorString("Semantic error on line %d column %d, variable %s is
 *		      not of the correct type.", 10, 12, "whatever");
 * Will return a pointer to the string:
 * "Semantic error on line 10 column 12, variable whatever is not of the
 *  correct type" 
 * 
 * WARNING: do NOT pass this function string literals read in from the
 *	    .pal program being parsed! (could contain null bytes and ruin
 * 	    the outputted string)
 *
 * TODO: remove explanatory comments once everyone understands how var args
 * works.
 */
char *
customErrorString(char * errMsg, ...)
{	
	static char msg[CUSTOM_ERRMSG_SZ];/* static => declared/initialized once
				           * and persists between function 
					   * calls */
	va_list args;

	va_start(args, errMsg);	/* initializes args for subsequent use by
				 * args = the last variable before the start of
				 * of the variable length argument list */
	
	vsprintf(msg, errMsg, args);
	va_end(args);		/* required by the api for whatever reason */

	msg[CUSTOM_ERRMSG_SZ - 1] = '\0';/* null terminate in case string passed
					 * was too long to fit into buffer */
	return msg;
}

/*
 * Prints the given error to stdout.
 */
void printError(struct Error *e)
{
	if (!e) return;
	fprintf(stdout, "%d Error: %s (%d, %d)\n", 
		e->lineno, e->msg, e->lineno, e->colno);
}

/*
 * Frees memory associated with the given error.
 */
void freeError(struct Error *e)
{
	if (!e) return;
	if (e->msg) free(e->msg);
	free(e);
}

