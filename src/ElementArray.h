/*
 * Module implementing a simple list type structure for function/procedure
 * parameters.
 */

#ifndef ELEMENTARRAY_H
#define ELEMENTARRAY_H

#include "Type.h"

#define EA_DEFAULT_SZ 10	/* default initial size of elements array */

/* 
 * Create a pointer to an initialized, malloced, empty ElementArray.
 * Parameters:  
 *
 * Returns:	struct ElementArray *ea success
 *		NULL failure	   
 */
struct ElementArray *newElementArray();
/* Checks if there is any duplicates in the given elementArray
 * 
 * Parameters: 
 *		ElementArray: a pointer to the elementArray
 * Return:
 *		1 has duplicates
 *		0 no duplicates
 */
int hasDuplicateElement(struct ElementArray *);
/*
 * appends the given element to the given elements array.
 * If the given ElementArray is already full, call growElementArray()
 * to double its size and then append the element.
 *
 * Parameters:
 * 		ElementArray: a pointer to an elementArray.
 *		void *element: a void pointer to an element
 * Return:
 *		void
 */
void appendElement(struct ElementArray *, void *);
/*
 * Returns a pointer to the element in the given ElementArray at index i.
 *
 * Parameters:  
 *		ElementArray: a ElementArray Pointer
 *		unsigned int : index 
 *
 * Return:	NULL if out of bounds
 * 		void **data : the data at i
 *		
 */
void *getElementAt(struct ElementArray *, unsigned int);
/*
 * Free all memory associated with the given elements array.
 * 
 * Parameters: 
 * 		ElementArray: a ElementArray
 * Return:
 *		void
 */
void freeElementArray(struct ElementArray *);
/*
 * Takes a ElementArray pointer and double its 
 * the size of the array if is full.
 * 
 * Parameters: 
 * 		ElementArray: a pointer to a elementArray
 * Return:
 *		void
 */ 
void growElementArray(struct ElementArray *); 
struct ElementArray *appendElementArray(struct ElementArray *, struct ElementArray *);
int hasDuplicateElement(struct ElementArray *);
#endif
