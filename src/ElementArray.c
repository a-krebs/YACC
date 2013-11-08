/*
 * Module implement a simple list type struct for function/procedure params.
 * Cmput 415 - Team YACC
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "ElementArray.h"

/*
 * Returns a pointer to an initialized, malloced, empty ElementArray.
 */
struct ElementArray *
newElementArray()
{
	struct ElementArray *ea = NULL;

	ea = calloc(1, sizeof(struct ElementArray));
	if (!ea) {
		err(1, "Failed to allocate memory for elements array!");
		exit(1);
	}

	ea->data = calloc(1, (sizeof(void *)*EA_DEFAULT_SZ));
	
	if (!ea->data) {
		err(1, "Failed to allocate memory for elements array data!");
		exit(1);
	}
	ea->len = EA_DEFAULT_SZ;
	ea->nElements = 0;

	return ea;
}

/*
 * Doubles the size of the array if is full.
 */
void
growElementArray(struct ElementArray *ea)
{		
	if (!ea) {
		return;
	}
	ea->len = (ea->len) * 2;
	ea->data = realloc(ea->data,sizeof(void *)*(ea->len));
	if (!ea->data) {
		err(1, "Failled reallocate memory to grow elements array!");
		exit(1);
	}
}

/*
 * Appends the given element to the given elements array.
 */
void
appendElement(struct ElementArray *ea, void *element)
{
	if (ea->nElements == (ea->len - 1)) {
		growElementArray(ea);	
	}

	ea->data[ea->nElements] = element;
	ea->nElements++;
}

/*
 * Appends the given elements array to another elements array
 */

struct ElementArray *
appendElementArray(struct ElementArray *ea1, struct ElementArray *ea2){	

	void **tmp = NULL;		
	int i ;
	int appendIndex ; /* the starting index of second array.*/
	

	if(!ea1 || !ea2){
		err(1, "One of the element arrays is a null pointer!");
		exit(1);
	}
	
	appendIndex = ea1->nElements;
	ea1->len += ea2->len; /*new length of allocated memory space*/
	
	ea1->nElements += ea2->nElements; 
	
	tmp = realloc(ea1->data,sizeof(void *)*(ea1->len));
	
	if(!tmp){
		err(1, "Failled reallocate memory to grow elements array!");
		exit(1);
	}
	
	tmp = ea1->data;

	for(i= appendIndex; i < ea1->nElements ; i++ ){
		ea1->data[i] = ea2->data[i-appendIndex];
	}
	
	free(ea2);
	return ea1;
}
/*
 * Returns a pointer to the element in the given ElementArray at index i.
 */
void *
getElementAt(struct ElementArray *ea, unsigned int i)
{
	if (i > (ea->nElements-1)) {
		/* Print error?  Exit? */
		return NULL;
	}
	return ea->data[i];
}

/*
 * Free all memory associated with the given elements array.
 */
void freeElementArray(struct ElementArray *ea) {
	int i;
	for (i = 0; i < (ea->nElements-1); i++) {
		if(!ea->data[i]){
			free(((Symbol **)ea->data)[i]->name);
			free(ea->data[i]);
		}
	}
	free(ea);
	
	
}






