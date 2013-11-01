#ifndef ERROR_H
#define ERROR_H

#include "ErrorLL.h"

#define MAXERRORS 100

/* For reporting the type of error. */
enum ErrorType {
	GENERIC,
	SYNTAX,
	SEMANTIC,
};

/*
 * typedef which stores the info necessary to record error when it
 * occurs and have it  printed to stderr and the program listing.
 */ 
struct Error {
	char *msg; /* dynamically allocate?  static prob okay */	
	int lineno; /* the line on which the error occured */
	int colno; /* the column position of the error occurence in the line */
	enum ErrorType type; /* type for reporting */
	
};

extern int colno; 
extern int nErrors;

struct Error *recordError(const char *, int, int, enum ErrorType);
void createErrorString(char **, struct Error *);
void printError(struct Error *);
void freeError(struct Error *);
char *getErrorTypeString(enum ErrorType);
#endif
