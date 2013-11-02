#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Hash.h"

extern struct hashElement *symbolTable[TABLE_SIZE];

/*
 * Look up an ID in the hash table.
 * Return a NULL pointer if id not in hash table.
 */
// TODO change to hashElement type
void *getHashElement(char* id) {
	// TODO implement hash table lookup
	return NULL;
}
