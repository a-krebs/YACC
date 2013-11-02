#ifndef ERROR_H
#define ERROR_H

#include "ErrorLL.h"

#define MAXERRORS 100
#define CUSTOM_ERRMSG_SZ 1024
/*
 * typedef which stores the info necessary to record error when it
 * occurs and have it  printed to stderr and the program listing.
 */ 
struct Error {
	char *msg; /* dynamically allocate?  static prob okay */	
	int lineno; /* the line on which the error occured */
	int colno; /* the column position of the error occurence in the line */
	
};

extern int colno; 
extern int nErrors;

struct Error *recordError(const char *, int, int);
char *customErrorString(char *, ...);
void createErrorString(char **, struct Error *);
void printError(struct Error *);
void freeError(struct Error *);
#endif
