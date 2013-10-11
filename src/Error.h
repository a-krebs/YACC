#ifndef ERROR_H
#define ERROR_H

#include "ErrorLL.h"

#define ERR_STRSIZE 128


/*
 * typedef which stores the info necessary to record error when it
 * occurs and have it  printed to stderr and the program listing.
 */ 
struct Error {
	char msg[ERR_STRSIZE]; /* dynamically allocate?  static prob okay */	
	int lineno; /* the line on which the error occured */
	
};

extern int nErrors;

struct Error *recordError(const char *, int);
void printError(char *errorstring, ...);
#endif
