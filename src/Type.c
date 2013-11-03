/*
 * Some nice comments about what this module is.
 *
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Type.h"

/*
 * Determines if the given type_t is an ordinal type.
 */
int
isOrdinal(type_t type)
{
	if ((type == BOOLEAN_T) || (type == CHAR_T) || (type == INTEGER_T)) {
		return 1;
	}
	return 0;
}

/*
 * Set type pointer new to point to type old of type passed as arg.
 */
void
setTypePtr(Type *new, Type old, type_t type)
{
	switch (type) {

	case ARRAY_T:
		new->Array = old.Array;
		break;
	case BOOLEAN_T:
		new->Boolean->value = old.Boolean->value;
		new->Boolean = old.Boolean;
		break;
	case CHAR_T:
		new->Char->value = old.Char->value;
		new->Char = old.Char;
		break;
	case INTEGER_T:
		new->Integer->value = old.Integer->value;
		new->Integer = old.Integer;
		break;
	case FUNCTION_T:
		new->Function = old.Function;
		break;
	case PROCEDURE_T:
		new->Procedure = old.Procedure;
		break;	
	case REAL_T:
		new->Real->value = old.Real->value;
		new->Real = old.Real;
		break;
	case RECORD_T:
		new->Record = old.Record;
		break;
	case SCALAR_T:
		new->Scalar = old.Scalar;
		break;
	case STRING_T:
		new->String = old.String;

	case SUBRANGE_T:
		new->Subrange = old.Subrange;
		break;
	default:
		/* Not reached */
		break;
	}
}

struct Array *
newArray(struct Symbol *baseTypeSym, struct Symbol *indexTypeSym)
{
	struct Array *a;
	/* Error checking */

	a = calloc(1, sizeof(struct Array));
	if (!a) {
		err(1, "Could not allocate memory for new array!");
		exit(1);
	}
	a->baseTypeSym = baseTypeSym;
	a->indexTypeSym = indexTypeSym;
	return a;
}

/* 
 * Constructs new subrange from the given symbols, assumes symbols have
 * been vetted and are valid.
 * TODO: maybe move error checking to this function
 */
struct Subrange * 
newSubrange(struct Symbol * lowSym, struct Symbol *highSym)
{
	struct Subrange *s = NULL;

	s = calloc(1, sizeof(struct Subrange));
	if (!s) {
		err(1, "Failed to allocate memory for new subrange!");
		exit(1);
	}
	
	/* Do a switch based one type to set low, high vals ... */

	s->baseTypeSym = lowSym;
	return s;
}


Type
newAnonConstType(AnonConstVal value, type_t type)
{
	Type anonConstType;
	switch(type) {
	case BOOLEAN_T: {
		struct Boolean constVal = value.Boolean;
		struct Boolean *constValPtr = calloc(1, sizeof(struct Boolean));
		if (!constValPtr) typeMemoryFailure();
		constValPtr->value = constVal.value;
		anonConstType.Boolean = constValPtr;
		break;
	}

	case CHAR_T: {
		struct Char constVal = value.Char;
		struct Char *constValPtr = calloc(1, sizeof(struct Char));
		if (!constValPtr) typeMemoryFailure();
		constValPtr->value = constVal.value;
		anonConstType.Char = constValPtr;
		break;
	}
	case INTEGER_T: {
		struct Integer constVal = value.Integer;
		struct Integer *constValPtr = calloc(1, sizeof(struct Integer));
		if (!constValPtr) typeMemoryFailure();
		constValPtr->value = constVal.value;
		anonConstType.Integer = constValPtr;
		break;
	}
	case REAL_T: {
		struct Real constVal = value.Real;
		struct Real *constValPtr = calloc(1, sizeof(struct Real));
		if (!constValPtr) typeMemoryFailure();
		constValPtr->value = constVal.value;
		anonConstType.Real = constValPtr;
		break;
	}
	case STRING_T: {
		struct String constVal = value.String;
		struct String *constValPtr = calloc(1, sizeof(struct String));
		if (!constValPtr) typeMemoryFailure();
				
		constValPtr->strlen = constVal.strlen;
		constValPtr->str = calloc(1, sizeof(char)*constVal.strlen);
		if(!constValPtr->str) typeMemoryFailure();
		strncpy(constValPtr->str, constVal.str, constVal.strlen);
		break;
	}
	default:
		/* NOT SUPPOSED TO BE REACHED */
		break;
	}

	return anonConstType;
}

void
typeMemoryFailure()
{
	err(1, "Failed to allocate memory for new anonymous constant type!");
	exit(1);
}
