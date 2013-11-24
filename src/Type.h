
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

Type *getTypePtr(Symbol *);

Type newAnonConstType(AnonConstVal, type_t);

type_t getType(Symbol *);

void setTypeSym(Symbol *, Symbol *);

void setTypePtr(Type *, Type, type_t);

void typeMemoryFailure();

struct TypeKind *getKindPtrForTypeKind(Symbol *);

Symbol *getInnerTypeSymbol(Symbol *symbol);
#endif
