/*
 * Some nice comments about what this module is.
 *
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Type.h"

char typeStr[TYPESTR_LEN];

/*
 * Returns true if the two Symbols of kind TYPE are the EXACT same type.
 */
int
areSameType(Symbol *s1, Symbol *s2)
{
	if ((!s1) || (!s2)) return 0;
	if ( !(s1->kind == TYPE_KIND) || !(s2->kind == TYPE_KIND)) return 0;
	return (s1->kindPtr.TypeKind == s2->kindPtr.TypeKind);
}


/*
 * Returns true if the two symbols are compatible string types (i.e.,
 * both strings of the same length)
 */
int
areCompatibleStrings(Symbol *s1, Symbol *s2)
{
	/* TODO: record errors */
	if ((!s1) || (!s2)) return 0;
	if (!(s1->kind == TYPE_KIND) || (s2->kind == TYPE_KIND)) return 0;
	if (!(s1->kindPtr.TypeKind->type == STRING_T) ||
	    !(s2->kindPtr.TypeKind->type == STRING_T)) return 0;
	
	return (s1->kindPtr.TypeKind->typePtr.String->strlen ==
	    s2->kindPtr.TypeKind->typePtr.String->strlen);	
}


/*
 * Returns true if the two type symbols are of operator compatible types.
 */
int
areOpCompatible(Symbol *s1, Symbol *s2) 
{
	/*TODO: record errors */
	type_t s1_t, s2_t;	

	if ((!s1) || (!s2)) /* record error */ return 0;
	if (!(s1->kind == TYPE_KIND) || (s2->kind == TYPE_KIND)) return 0;

	s1_t = s1->kindPtr.TypeKind->type;
	s2_t = s2->kindPtr.TypeKind->type;

	if (s1_t == STRING_T)
	    return areCompatibleStrings(s1, s2);

	if (!(s1_t == s2_t) && !((s1_t == INTEGER_T) && (s2_t == REAL_T)) &&
	    !( (s1_t == REAL_T) && (s2_t == INTEGER_T))) {
		/* print error stuff */
		return 0;
	}

	if ((s1_t == INTEGER_T) || (s1_t == REAL_T)) return 1;
	return 0;
}

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
newArray(Symbol *baseTypeSym, Symbol *indexTypeSym)
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
newSubrange(Symbol * lowSym, Symbol *highSym)
{
	struct Subrange *s = NULL;
	Symbol *typeSym = lowSym->kindPtr.ConstKind->typeSym;
	AnonConstVal *lowVal = &(lowSym->kindPtr.ConstKind->value),
		* highVal = &(highSym->kindPtr.ConstKind->value);
	int low = 0, high = 0;

	s = calloc(1, sizeof(struct Subrange));
	if (!s) {
		err(1, "Failed to allocate memory for new subrange!");
		exit(1);
	}
	
	/* Do a switch based on type to set low, high vals ... */
	switch(typeSym->kindPtr.TypeKind->type) {
	case BOOLEAN_T:
		low = lowVal->Boolean.value;
		high = highVal->Boolean.value;
		break;
	case CHAR_T:
		low = lowVal->Char.value;
		high = highVal->Char.value;
		break;
	case INTEGER_T:
		low = lowVal->Integer.value;
		high = highVal->Integer.value;
		break;
	default:
		/* NOT REACHED */
		return NULL;
	    
	}

	s->low = low;
	s->high = high;
	s->baseTypeSym = lowSym;
	return s;
}

type_t
getType(Symbol *s)
{
	if (!s) /* should probably exit program */ return VOID_T;
	if (!s->kindPtr.ConstKind) /* kindPtr no allocated  */ return VOID_T;
	switch (s->kind) {
	case CONST_KIND:
		return s->kindPtr.ConstKind->typeSym->kindPtr.TypeKind->type;
	case PROC_KIND:
		return VOID_T;
	case FUNC_KIND:
		return s->kindPtr.FuncKind->typeSym->kindPtr.TypeKind->type;
	case TYPE_KIND:
		return s->kindPtr.TypeKind->type;
	case VAR_KIND:
		return s->kindPtr.VarKind->typeSym->kindPtr.TypeKind->type;
	default:
		/* NOT REACHED */
		return VOID_T;
	}	
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
		/* NOT REACHED */
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

char *
typeToString(type_t type)
{
	memset(typeStr, '\0', TYPESTR_LEN);
	switch (type) {
	case ARRAY_T:
		strcpy(typeStr, "ARRAY");
		break;
	case BOOLEAN_T:
		strcpy(typeStr, "BOOLEAN");
		break;
	case CHAR_T:
		strcpy(typeStr, "CHARACTER");
		break;
	case INTEGER_T:
		strcpy(typeStr, "INTEGER");
		break;
	case REAL_T:
		strcpy(typeStr, "REAL");
		break;
	case RECORD_T:
		strcpy(typeStr, "RECORD");
		break;
	case SCALAR_T:
		strcpy(typeStr, "SCALAR");
		break;
	case STRING_T:
		strcpy(typeStr, "STRING");
		break;
	case SUBRANGE_T:
		strcpy(typeStr, "SUBRANGE");
		break;
	case VOID_T:
		strcpy(typeStr, "VOID");
	default:
		/* NOT REACHED */
		strcpy(typeStr, "UNKNOWN");
	}

	return typeStr;
}
