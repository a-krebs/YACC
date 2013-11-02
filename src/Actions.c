#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Hash.h"
#include "parser.tab.h"

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

/*
 * Set the ID's type.
 */
// TODO change types
void doTypeDecl(void *id, void* type) {
	// TODO assign type to id
}

/*
 * Perform actions necessary when entering type decl part.
 */
void enterTypeDeclPart(void) {
	// TODO implementation.
}

/*
 * Assign a constant.
 */
// TODO change types
void doConstDecl(void *id, void *type) {
	// TODO implementation. Check that they're assignment compatible.
}

/*
 * Perform actions necessary when entering const decl part.
 */
void enterConstDeclPart(void) {
	// TODO implement.
}

/*
 * Make a new anonymous symbol with type integer and given value.
 * Return pointer to the hash symbol.
 */
// TODO change return type
void *anonIntLiteral(int value) {
	// TODO implement
	return NULL;
}
	
/*
 * Make a new anonymous symbol with type real and given value.
 * Return a pointer to the hash symbol.
 */
// TODO change return type
void *anonRealLiteral(double value) {
	// TODO implement
	return NULL;
}

/*
 * Make a new anonymous symbol with the given string.
 * Return a pointer to the hash symbol.
 */
// TODO change return type
void *anonStringLiteral(char *value) {
	// TODO implment
	return NULL;
}

/*
 * Check that the given types are compatible when using the given
 * operator.
 *
 * Return a pointer to the resulting type when performing the operation.
 *
 * If the types are not combatible for this operator, set error and return NULL.
 */
// TODO change return type and arg types
void *assertOpCompat(void *type1, int opToken, void *type2) {
	// TODO implment
	switch (opToken) {
		case EQUAL:
			break;
		default:
			// TODO error
			break;
	}
	return NULL;
}
