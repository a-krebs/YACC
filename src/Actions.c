#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Hash.h"
#include "Symbol.h"
#include "parser.tab.h"	/* token definitions used in operator compat checks */

extern struct hashElement *symbolTable[TABLE_SIZE];

/*
 * Utility functions. Can maybe be refactored into own module.
 */

/*
 * Check that the given types are compatible when using the given
 * operator.
 *
 * Return a pointer to a Symbol struct THAT IS NOT IN THE SYMBOL TABLE
 * that is populated with the resulting type when performing the operation, and
 * the value of the expression if it can be evaluated (like when dealing with
 * constants).
 *
 * If the types are not combatible for this operator, set error and return NULL.
 */
struct Symbol *assertOpCompat(
    struct Symbol *type1, int opToken, struct Symbol *type2) {
	// TODO implement
	switch (opToken) {
		case EQUAL:
			break;
		default:
			// TODO error
			break;
	}
	return NULL;
}

/*
 * Return 0 if the given types are assignment compatible, otherwise return
 * non-zero
 */
int assignmentCompatEh(struct Symbol type1, struct Symbol type2) {
	// TODO implement
	return -1;
}

/*
 * Parser action functions, in the order they appear in parser.y
 */

/*
 * Perform actions necessary when exiting const decl part.
 */
void exitConstDeclPart(void) {
	// function does nothing.
}

/*
 * Assign a constant.
 */
void doConstDecl(char *id, struct Symbol *tmp) {
	// TODO implementation. Check that they're assignment compatible.
}

/*
 * Perform actions necessary when exiting type decl part.
 */
void exitTypeDeclPart(void) {
	// TODO implementation.
}

/*
 * Set the ID's type.
 */
// TODO change types
void doTypeDecl(char *id, struct Symbol *tmp) {
	// TODO assign type to id
}

struct Symbol *simpleTypeLookup(char *id) {
	return NULL;
}


/*
 * Add new_id as a mamber to scalar_list.
 *
 * Return scalar_list
 */
struct Symbol *appendToScalarListType(struct Symbol *scalar_list, char *new_id) {
	return scalar_list;
}

/*
 * Create a new scalar list type with id as the only member.
 *
 * Return a pointer to the new scalar list
 */
struct Symbol *createScalarListType(char *id) {
	return NULL;
}

/*
 * Create a new arrau type given the index type and base type.
 */
struct Symbol *createArrayType(struct Symbol *index, struct Symbol *base) {
	return NULL;
}

/*
 * Check that the given type is a valid array index type.
 *
 * Raise an error if the type is not valid as an index type.
 *
 * Return the given type.
 */
struct Symbol *assertArrIndexType(struct Symbol *index_type) {
	return index_type;
}

/*
 * Create a new subrange type. The arguments are temporary symbols that should
 * constain constant values for the range bounds.
 *
 * Return a pointer to the new subrange type.
 */
struct Symbol *createRangeType(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

/*
 * Create a new record type from the given temporary field.
 *
 * Return a pointer to the new type symbol.
 */
struct Symbol *createRecordType(struct Symbol *tmp) {
	return NULL;
}

/*
 * Add the given temporary field to the record as a proper field.
 *
 * Return a pointer to the record type.
 */
struct Symbol *appendFieldToRecordType(
    struct Symbol *record_type, struct Symbol *tmp) {
	return record_type;
}

/*
 * Make a new temporary symbol (do not add to symbol table) that
 * constains the name and type of a record field.
 *
 * Return a pointer to the new tmp symbol.
 */
struct Symbol *newTmpRecordField(char *id, struct Symbol *type) {
	return NULL;
}

struct Symbol *assignOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *hashLookupToTmp(char *id) {
	return NULL;
}

struct Symbol *recordAccessToTmp(char *id1, char *id3) {
	return NULL;
}

struct Symbol *eqOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *notEqOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *lessOrEqOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *lessOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *gtOrEqOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *gtOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *unaryPlusOp(struct Symbol *tmp2) {
	return NULL;
}

struct Symbol *unaryMinusOp(struct Symbol *tmp2) {
	return NULL;
}

struct Symbol *plusOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *minusOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *orOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *multOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *divideOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *divOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *modOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *andOp(struct Symbol *tmp1, struct Symbol *tmp3) {
	return NULL;
}

struct Symbol *getTmpFromSymbol(struct Symbol *symbol) {
	return NULL;
}

struct Symbol *unaryNotOp(struct Symbol *tmp2) {
	return NULL;
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
