#ifndef UTILS_H
#define UTILS_H

#include "Definitions.h"

char *opToString(int);
int isLogicalOperator(int);
int isRelationalOperator(int);
int isUnaryOperator(int);
void opError(char *, int, char *);
void alreadyDefinedError(char *id);
void notDefinedError(char *id);
void symbolTableInsertFailure();
int getStrlen(struct String s);
/*
 * Conform that strtod did not set errno.
 * Set errno to 0 before calling
 */
void checkErrnoStrtoX();
#endif
