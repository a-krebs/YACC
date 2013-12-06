
#include <stdio.h>
#include <stdlib.h>

#ifndef TYPE_H
#define TYPE_H

#define TYPESTR_LEN 64

#include "Definitions.h"

#define TYPEORIGINATOR_YES 1
#define TYPEORIGINATOR_NO 0

/*
 * The types of a values which can be associated with various kinds.
 */


/* Function declarations */
int areArithmeticCompatible(Symbol *, Symbol *);

int areBothInts(Symbol *, Symbol *);

int areOpCompatible(Symbol *, Symbol *);

int areCompatibleStrings(Symbol *, Symbol *);

int areSameType(Symbol *, Symbol *);

int isOrdinal(type_t);

int isSimpleType(type_t);

char *typeToString(type_t);

struct Array *newArray(Symbol *, Symbol *);

struct Subrange *newSubrange(Symbol*, Symbol *);

struct Record *newRecord();

struct Scalar *newScalar(struct ElementArray *scalars);
Type *getTypePtr(Symbol *);

type_t getType(Symbol *);

void setInnerTypeSymbol(Symbol *, Symbol *);

void typeMemoryFailure();

struct TypeKind *getKindPtrForTypeKind(Symbol *);
struct ConstantKind *getKindPtrForConstKind(Symbol *);

/* Type symbol size calculation functions */
int calculateSymbolSize(Symbol *);

int calculateArraySize(Symbol *);

int calculateScalarSize(Symbol *);

int calculateSubrangeSize(Symbol *);

Symbol *getInnerTypeSymbol(Symbol *symbol);


/* Allocates memory for the StringType struct
 *
 * Parameters:
 *
 * Return: Pointer to newly allocated memory chunk
 */
struct StringType *allocateStringType();


/* Set the str member of the struct String
 *
 * Parameters:
 * 		string: struct String
 * 		str: char* to be copied into struct
 *		len: lenght of str
 *
 * Return: void
 */
void setStringStr(struct String *string, char *str, unsigned int len);


/*
 * Creates a new StringType struct
 * 
 * Parameters:
 * 	strlen: length for the new string type
 * Returns:
 * 	a pointer the the new struct
 */
struct StringType *newStringType(unsigned int strlen);

/*
 * Boolean function to determine if passed type is an 
 * either real, int, or bool.
 * 
 * Parameters:
 * 	type: 
 *
 * Returns:
 * 	boolean 0/1
 */
int isRealIntBool(type_t type);


int isScalarMember(Symbol *sym);

int isScalarVar(Symbol *sym);
#endif
