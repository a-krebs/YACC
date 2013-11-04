
#include <stdio.h>
#include <stdlib.h>

#ifndef TYPE_H
#define TYPE_H

#include "Definitions.h"


/*
 * The types of a values which can be associated with various kinds.
 */


/* Function declarations */
int isOrdinal(type_t);
struct Array *newArray(Symbol *, Symbol *);
struct Subrange *newSubrange(Symbol*, Symbol *);
Type newAnonConstType(AnonConstVal, type_t);
type_t getType(Symbol *);
void setTypePtr(Type *, Type, type_t);
void typeMemoryFailure();
#endif
