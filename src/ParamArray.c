/*
 * Module implement a simple list type struct for function/procedure params.
 * Cmput 415 - Team YACC
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "ParamArray.h"

/*
 * Returns a pointer to an initialized, malloced, empty ParamArray.
 */
struct ParamArray *
newParamArray()
{
	struct ParamArray *pa = NULL;

	pa = calloc(1, sizeof(struct ParamArray));
	if (!pa) {
		err(1, "Failed to allocate memory for param array!");
		exit(1);
	}

	pa->data = calloc(1, (sizeof(struct ParamArray))*PA_DEFAULT_SZ);
	if (!pa->data) {
		err(1, "Failed to allocate memory for param array data!");
		exit(1);
	}
	pa->len = PA_DEFAULT_SZ;
	pa->nElements = 0;

	return pa;
}

/*
 * Doubles the size of the array if is full.
 */
void
growParamArray(struct ParamArray *pa)
{
	if (!pa) {
		return;
	}

	pa->len *= 2;
	pa->data = realloc(pa->data, sizeof(struct Param)*(pa->len));

	if (!pa->data) {
		err(1, "Failled reallocate memory to grow param array!");
		exit(1);
	}
}

/*
 * Appends the given parameter to the given parameter array.
 */
void
appendParam(struct ParamArray *pa, struct Param *p)
{
	if (pa->nElements == (pa->len - 1)) {
		growParamArray(pa);	
	}

	pa->data[pa->nElements] = p;
	pa->nElements++;
}

/*
 * Returns a pointer to the element in the given ParamArray at index i.
 */
struct Param *
getParam(struct ParamArray *pa, unsigned int i)
{
	if (i > (pa->nElements-1)) {
		/* Print error?  Exit? */
		return NULL;
	}
	return pa->data[i];
}

/*
 * Free all memory associated with the given parameter array.
 */
void freeParamArray(struct ParamArray *pa) {
	int i;
	for (i = 0; i < (pa->nElements-1); i++) {
		free(pa->data[i]->name);
		free(pa->data[i]);
	}
	free(pa);
}
