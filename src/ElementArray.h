/*
 * Module implementing a simple list type structure for function/procedure
 * parameters.
 */

#ifndef ELEMENTARRAY_H
#define ELEMENTARRAY_H

#include "Type.h"

#define EA_DEFAULT_SZ 24	/* default initial size of elements array */

struct ElementArray *newElementArray();
void appendElement(struct ElementArray *, void *);
void *getElementAt(struct ElementArray *, unsigned int);
void freeElementArray(struct ElementArray *,element_t); 
void growElementArray(struct ElementArray *); 

#endif
