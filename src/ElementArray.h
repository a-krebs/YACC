/*
 * Module implementing a simple list type structure for function/procedure
 * parameters.
 */

#ifndef ELEMENTARRAY_H
#define ELEMENTARRAY_H

#include "Type.h"

#define EA_DEFAULT_SZ 10	/* default initial size of elements array */

struct ElementArray *newElementArray();
int hasDuplicateElement(struct ElementArray *);
void appendElement(struct ElementArray *, void *);
void *getElementAt(struct ElementArray *, unsigned int);
void freeElementArray(struct ElementArray *); 
void growElementArray(struct ElementArray *); 
struct ElementArray *appendElementArray(struct ElementArray *, struct ElementArray *);
#endif
