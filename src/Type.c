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
 * Returns true if the two Symbols are arithmetic compatible.
 */
int
areArithmeticCompatible(Symbol *s1, Symbol *s2)
{
	type_t s1_t, s2_t;

	s1_t = getType(s1);
	s2_t = getType(s2);

	return (((s1_t == INTEGER_T) || (s1_t == REAL_T)) && 
	    ((s2_t == INTEGER_T) || (s2_t == REAL_T)));	
}

/*
 * Returns true if both symbols are of integer type.
 */
int
areBothInts(Symbol *s1, Symbol *s2)
{
	return ((getType(s1) == INTEGER_T) && (getType(s2) == INTEGER_T));
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
	if (!(s1->kind == TYPE_KIND) || !(s2->kind == TYPE_KIND)) return 0;

	s1_t = s1->kindPtr.TypeKind->type;
	s2_t = s2->kindPtr.TypeKind->type;

	/* If one is a string, then both need to be strings to be compatible */
	if (s1_t == STRING_T)
	    return areCompatibleStrings(s1, s2);

	/* 
	 * Already handled case where operators are strings, so now
	 * we know if either type is not a simple type then they are not
	 * operator compatible (even if they are the exact same type as no
	 * operator we support works on non-simple, non-string types 
	 */
	if ((!isSimpleType(s1_t)) || !(isSimpleType(s1_t))) {
		return 0;
	}

	/* If we get here, we have two simple types.  So if they are
	 * of the type_t, we know they are operator compatible (for at least
	 * relational operators) */
	if (s1_t == s2_t)
		return 1;

	/* Finally, if types is a mixed int/real pair, they're compatible */
	if ( ((s1_t == INTEGER_T) && (s2_t == REAL_T)) ||
	    ((s1_t == REAL_T) && (s2_t == INTEGER_T)) ) return 1;

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
 * Determines if the given type is a simple type (i.e., a bool, char, int,
 * or real)
 */
int
isSimpleType(type_t type)
{
	switch (type) {
	case BOOLEAN_T:
	case CHAR_T:
	case INTEGER_T:
	case REAL_T:
		return 1;
	default:
		return 0;
	}
}

/*
 * Appropriately sets the typeSym field for Symbols of kind != TYPE_KIND given
 * a pointer to the typeSym defining the type for the given Symbol s.
 * WARNING: assumes the kindPtr for the given symbol s has been allocated.
 */
void
setTypeSym(Symbol *s, Symbol *typeSym)
{
	switch (s->kind) {
	case CONST_KIND:
		s->kindPtr.ConstKind->typeSym = typeSym;
		break;
	case FUNC_KIND:
		s->kindPtr.FuncKind->typeSym = typeSym;
		break;
	case VAR_KIND:
		s->kindPtr.VarKind->typeSym = typeSym;
		break;
	default:
		/* Should not be reached */
		break;
	}
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
	switch (s->kind) {
	case CONST_KIND:
		return s->kindPtr.ConstKind->typeSym->kindPtr.TypeKind->type;
	case PARAM_KIND:
		return s->kindPtr.ParamKind->typeSym->kindPtr.TypeKind->type;
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
	static char typeStr[TYPESTR_LEN];
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

/*
 * Return a pointer to the typePtr for the given Symbol of kind TYPE_KIND.
 * Returns null if the given Symbol is not of kind TYPE_KIND.
 */
Type *
getTypePtr(Symbol *s)
{
	if (!s) return NULL;
	if (s->kind != TYPE_KIND) return NULL;
	printf("\n\n\n--------------------------------------\n\n\n");
	return &(s->kindPtr.TypeKind->typePtr);

}
