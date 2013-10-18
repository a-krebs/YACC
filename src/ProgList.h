/*
 * Cmput 415 = Team YACC
 * Module implementing functionality related to the production
 * of the program listing (with errors) at end of compilation.
 */

#ifndef PROGLIST_H
#define PROGLIST_H

#include "Error.h"
#include "ErrorLL.h"

#define ERRMSG_SIZE ERR_STRSIZE + 128

extern struct ErrorLL *errors;


void printProgramListing(FILE *, char *);
int getNextErrLineno(struct ErrorLL **);
char *getListingFileName(char*);



#endif
