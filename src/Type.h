
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

void setTypePtr(Type *, Type, type_t);

void typeMemoryFailure();

struct TypeKind *getKindPtrForTypeKind(Symbol *);
struct ConstKind *getKindPtrForConstKind(Symbol *);

/* Type symbol size calculation functions */
int calculateSymbolSize(Symbol *);

int calculateArraySize(Symbol *);

int calculateScalarSize(Symbol *);

int calculateSubrangeSize(Symbol *);

Symbol *getInnerTypeSymbol(Symbol *symbol);


struct String *allocateString();
void setStringStr(struct String *string, char *str);
struct String *newString(char *str, unsigned int strlen);


#endif
