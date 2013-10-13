/* 
 * Cmput 415 - Team YACC
 * Linked list implementation to store all errors which occur during
 * compilation such that they can be added to the program listing.
 */

#ifndef ERRORLL_H
#define ERRORLL_H

#include <stdio.h>
#include <stdlib.h>

#include "Error.h"

struct ErrorLL {
	struct Error *error;
	struct ErrorLL *next;
} ErrorLL;

extern struct ErrorLL * errors;

void appendError(struct ErrorLL **, struct Error *);
struct Error *getNextError(struct ErrorLL **);
void freeErrorList(struct ErrorLL *);
#endif
