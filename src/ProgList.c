/*
 * Cmput 415 = Team YACC
 * Module implementation functionality related to the production
 * of the program listing (with errors) at parser end.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Error.h"
#include "ErrorLL.h"
#include "ProgList.h"

/*
 * Produces the program listing for the given compilation.
 * Pre: in is points to the input file which was parsed/compiled
 *      fileName is a null terminated string which is the name
 *               of the file which was parsed/compiled
 */
void
printProgramListing(FILE *in, char *fileName)
{
	char errMsg[ERRMSG_SIZE];
	struct ErrorLL *ell = errors;
	struct Error *nextError = NULL;
	long fileSize, bytesRead = 0;
	int nextErrLineno = 0, bufPos, lineno = 0, bufSize = 512;
	FILE *out = NULL;
	char *buf, c;

	/* 
	 * Try to open output file to which the program listing 
	 * will be written.
	 */
	out = fopen(fileName, "w");
	if (!out) {
		err(2, "Failed to open output file.  No listing generated.");
		return;
	}

	/*
	 * Get the line number of the first error in the program
	 * (if it exists, else this will be set to -1)
	 */
	if (ell) {
		nextError = ell->error;
		nextErrLineno = nextError->lineno;
	}

	/*
	 * The strategy is to read in the file one line at a time and
	 * dynamically grow the buffer if the line size is greater
	 * than the amount of space we have allocated.
	 */

	buf = malloc(sizeof(char)*bufSize);
	if (!buf) {
		err(1, "Failed to allocate memory to write program listing.");
		return;
	}

	do {
		lineno++;
		bufPos = 0;
		do {
			c = fgetc(in);
			if (c != EOF) buf[bufPos++] = c;
			if (bufPos >= bufSize-2) {
				/* Line will overfill our buffer,
				 * so let's make it bigger */
				bufSize *= 2;
				buf = realloc(buf, sizeof(char)*bufSize);
			}
		} while ( (c != EOF) && (c != '\n'));

		/* 
		 * Null-terminate in case last bufPos was greater than
		 * bufPos this time through the loop 
		 */
		buf[bufPos] = '\0'; 

		/* we now have a line in buf, so let's write it out to a file */
		
		fprintf(out, "%d\t|:\t%s", lineno, buf);

		/* 
		 * while we know that an error occured on this line,
		 * keep writing out the error message associated with
		 * this line.
		 */
		while (nextErrLineno == lineno) {
			createErrorString(errMsg, ERRMSG_SIZE, nextError);
			fprintf(out, "Error\t|:\t%s\n", errMsg);
			nextError = getNextError(&ell);
			if (nextError) nextErrLineno = nextError->lineno;
			else nextErrLineno = -1;
		}
	} while (c != EOF);


	free(buf);
}
