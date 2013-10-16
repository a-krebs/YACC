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
	int colno; /* the column position of the error occurence in the line */
	
};

extern int nErrors;
extern int colno; 

struct Error *recordError(const char *, int, int);
void createErrorString(char *, int, struct Error *);
void printError(struct Error *);
#endif
