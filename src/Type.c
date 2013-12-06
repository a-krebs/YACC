/*
 * Some nice comments about what this module is.
 *
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Type.h"
#include "Hash.h"
#include "Kind.h"
#include "SymbolAPI.h"
#include "SymbolArray.h"

//////////////////////////////////////////////////////////////////////////
/*
 * 			TYPE API FUNCTIONS:
 */
//////////////////////////////////////////////////////////////////////////

/*
 * Determines the type of symbol we have (from type_t enum). Throughts error is
 * type is not a valid type.
 */
type_t
getType(Symbol *s)
{
	if (!s) return VOID_T;

	/* Handle special case of the program head */
	//if (!s->kindPtr.FuncKind->typeSym) return VOID_T;


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
		// return VOID_T;
		err(1, "Symbol 'kind' not set.");
		exit(1);		
	}	
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
	return &(s->kindPtr.TypeKind->typePtr);
}


/*
 * Gets the string value of the passed type.
 */
char *
typeToString(type_t type)
{
	switch (type) {
	case ARRAY_T:
		return "ARRAY";
	case BOOLEAN_T:
		return "BOOLEAN";
	case CHAR_T:
		return "CHARACTER";
	case INTEGER_T:
		return "INTEGER";
	case REAL_T:
		return "REAL";
	case RECORD_T:
		return "RECORD";
	case SCALAR_T:
		return "SCALAR";
	case STRING_T:
		return "STRING";
	case SUBRANGE_T:
		return "SUBRANGE";
	case VOID_T:
		return "VOID";
	default:
		/* NOT REACHED */
		return "UNKNOWN";
	}
}


//////////////////////////////////////////////////////////////////////////
/*
 * 			TYPE CHECKING FUNCTIONS:
 */
//////////////////////////////////////////////////////////////////////////

/*
 * Returns true if the two Symbols of kind TYPE are the EXACT same type.
 */
int areSameType(Symbol *s1, Symbol *s2) {
	if ((!s1) || (!s2)) return 0;
	if ( !(s1->kind == TYPE_KIND) || !(s2->kind == TYPE_KIND)) return 0;

	if(s1->kindPtr.TypeKind == s2->kindPtr.TypeKind) {
		return 1;
	} else {
		return 0;
	}
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
 * Determines if the given type_t is an ordinal type.
 */
int
isOrdinal(type_t type)
{
	if ((type == BOOLEAN_T) ||
		(type == CHAR_T) || 
		(type == INTEGER_T) ||
		(type == SCALAR_T)) {
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
 * Check if two type symbols represent compatible string types. (i.e.,
 * 	one or both is/are an array of chars and the other or both is/are
 *	a string literal and both are of the same length)
 * 
 * Parameters:
 * 	s1, s2: symbols of kind TYPE_KIND for compatibility check
 * Return:
 * 	1 if if the two symbols are compatible string types
 * 	0 otherwise
 */
int areCompatibleStrings(Symbol *s1, Symbol *s2)
{
	Symbol *subTypeSym1;
	Symbol *subTypeSym2;
	/* Upper bound & lower bound */
	int high1 = 0;
	int low1 = 0;
	
	int high2 = 0;
	int low2 = 0;
	/* two string lengths */
	int l1 = 0;
	int l2 = 0;

	/* error checking */
	if ((!s1) || (!s2)) {
		return 0;
	}
	if (!(s1->kind == TYPE_KIND) || !(s2->kind == TYPE_KIND)) {
		return 0;
	}
	
	if ( (getType(s1) != STRING_T) && (getType(s1) != ARRAY_T) ) return 0;
	if ( (getType(s2) != STRING_T) && (getType(s2) != ARRAY_T) ) return 0;

	if ( (getType(s1) == ARRAY_T) && 
	    (getType(getArrayBaseSym(s1)) != CHAR_T) ) {
		return 0;
	} 

	if ( (getType(s2) == ARRAY_T) && 
	    (getType(getArrayBaseSym(s2)) != CHAR_T) ) {
		return 0;
	}
	
	if ( (getType(s1) == ARRAY_T) && (getType(s2) == STRING_T) ) {
		 l1 = getArrayLength(s1);
		 l2 = getTypePtr(s2)->String->strlen;
		 
		 low1 = getArrayLowIndexValue(s1);
		 high1 = getArrayHighIndexValue(s1);
		 
		 if (getType(getArrayIndexSym(s1)) != SUBRANGE_T) return 0;
		 
		 subTypeSym1 = getSubrangeBaseTypeSym(getArrayIndexSym(s1));
		 
		 if (getType(subTypeSym1) != INTEGER_T) return 0;
		 
		 if ((low1 == 1) && (high1 > 1) && (l1 == l2)) {
			return 1;
		 } else {
			return 0;		 
		 }
	}
	
	if ( (getType(s1) == ARRAY_T) && (getType(s2) == ARRAY_T) ) {
		l1 = getArrayLength(s1);
		l2 = getArrayLength(s2);
		
		low1 = getArrayLowIndexValue(s1);
		high1 = getArrayHighIndexValue(s1);
		
		low2 = getArrayLowIndexValue(s2);
		high2 = getArrayHighIndexValue(s2);
		
		if (getType(getArrayIndexSym(s1)) != SUBRANGE_T) return 0;
		if (getType(getArrayIndexSym(s2)) != SUBRANGE_T) return 0;
		
		subTypeSym1 = getSubrangeBaseTypeSym(getArrayIndexSym(s1));
		subTypeSym2 = getSubrangeBaseTypeSym(getArrayIndexSym(s2));
		
		if (getType(subTypeSym1) != INTEGER_T) return 0;
		if (getType(subTypeSym2) != INTEGER_T) return 0;
		
		if ((low1 == 1) && (high1 > 1) && 
			(low2 == 1) && (high2 > 1) && 
			(l1 == l2)
		) {
			return 1;
		} else {
			return 0;		 
		}
	}

	if (getType(s1) == STRING_T) l1 = getTypePtr(s1)->String->strlen;
	else l1 = s1->size;
	if (getType(s2) == STRING_T) l2 = getTypePtr(s2)->String->strlen;
	else l2 = s2->size;


	if ( l1 == l2 ) {
		return 1;
	}
	else {
		return 0;
	}
}


/*
 * Check if the two type symbols are operator compatible.
 *
 * Records no errors. Calling function should record errors.
 * 
 * Parameters:
 * 	s1, s2: the two symbols to check for compatibility. Should be of
 * 		kind TYPE_KIND
 * Return:
 * 	0 if the two type symbols are not of operator compatible types.
 * 	non-zero otherwise
 */
int areOpCompatible(Symbol *s1, Symbol *s2) 
{
	type_t s1_t, s2_t;	

	if ((!s1) || (!s2)) {
		return 0;
	}
	if (!(s1->kind == TYPE_KIND) || !(s2->kind == TYPE_KIND)) {
		return 0;
	}

	s1_t = s1->kindPtr.TypeKind->type;
	s2_t = s2->kindPtr.TypeKind->type;

	/*
	 * If one of the types is a string or an array, we only have operation
	 * compatibility (with regard to relation operators) if the array is
	 * an array of chars of the same size as the other operator.
 	 */
	if ( (s1_t == STRING_T) || (s1_t == ARRAY_T) ) 
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


//////////////////////////////////////////////////////////////////////////
/*
 * 			TYPE CREATION FUNCTIONS:
 */
//////////////////////////////////////////////////////////////////////////

/*
 * Create a new array struct
 *
 * Parameters:
 * 	baseTypeSym: the base type for the array.
 * 	indexTypeSym: the index type for the array.
 *
 * Returns:
 * 	a pointer to the new array struct
 */
struct Array *newArray(Symbol *baseTypeSym, Symbol *indexTypeSym)
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
 * Return a pointer to a new record struct with no fields.
 * 
 * Fields can be added to the record struct later.
 */
struct Record *newRecord() {
	struct Record *r = NULL;

	r = calloc(1, sizeof(struct Record));
	if (!r) {
		err(1, "Failed to allocate memory for new record!");
		exit(1);
	}
	/* give the record its own hash table */
	r->hash = createHash(&getHashedKeyNormal);

	return r;
}


/*
 * Create a new struct Scalar
 * 
 * Parameters:
 * 	scalars: the list of scalars that are part of the scalar list
 *
 * Return:
 * 	a pointer to the new Scalar struct
 */
struct Scalar *newScalar(struct ElementArray *scalars) {
	struct Scalar *s = NULL;

	s = calloc(1, sizeof(struct Record));
	if (s == NULL) {
		err(EXIT_FAILURE, "Failed to allocate memory for new scalar!");
	}

	/* set scalar type constants */
	s->consts = scalars;

	return s;
}


//////////////////////////////////////////////////////////////////////////
/*
 * 			OTHER STUFF:
 */
//////////////////////////////////////////////////////////////////////////

void
typeMemoryFailure()
{
	err(1, "Failed to allocate memory for new anonymous constant " 		"type!");
	exit(1);
}


/*
 * Utility function to access kindPtr for TYPE_KIND
 *
 * Parameters:
 * 	symbol: The symbol from which to extract the kindPtr.
 * 		Must be of kind TYPE_KIND
 * Return:
 * 	A pointer to the TypeKind struct that is the kindPtr for symbol.
 */
struct TypeKind *getKindPtrForTypeKind(Symbol *symbol) {
	if ((symbol == NULL) || ( symbol->kind != TYPE_KIND)) {
		err(EXIT_FAILURE, "Called getKindPtrForTypeKind on "
		    "symbol that is not TYPE_KIND.");
	}

	return symbol->kindPtr.TypeKind;
}


/*
 * Utility function to access kindPtr for CONST_KIND
 *
 * Parameters:
 * 	symbol: The symbol from which to extract the kindPtr.
 * 		Must be of kind CONST_KIND
 * Return:
 * 	A pointer to the ConstKind struct that is the kindPtr for symbol.
 */
struct ConstantKind *getKindPtrForConstKind(Symbol *symbol) {
	if ((symbol == NULL) || (symbol->kind != CONST_KIND)) {
		err(EXIT_FAILURE, "Called getKindPtrForConstKind on "
		    "symbol that is not CONST_KIND.");
	}

	return symbol->kindPtr.ConstKind;
}


// struct Array *allocateArrayType() {
// 	struct Array *arrayType = NULL;

// 	arrayType = calloc(1, sizeof(struct Array));
// 	if ( arrayType == NULL ) {
// 		err(1, "Could not alloc memory for array type.");
// 		exit(EXIT_FAILURE);		
// 	}

// 	return arrayType;
// }



/* Allocates memory for the Subrange struct
 *
 * Parameters:
 *
 * Returns: pointer to memery allocated for a struct Subrange
 */
struct Subrange *allocateSubRangeType() {
	struct Subrange *subRangeType = NULL;

	subRangeType = calloc(1, sizeof(struct Subrange));
	if ( subRangeType == NULL ) {
		err(1, "Failed to allocate memory for subrange type.");
		exit(EXIT_FAILURE);		
	}

	return subRangeType;
}


/* TODO simplify look up calls with api functions
 * Creates a subrange symbol.
 *
 * Parameters:
 *		lowSym: symbol forming lower bound on range
 *		highSym: symbol forming upper bound on range
 *
 * Returns: New Subrange struct
 */
struct Subrange *
newSubrange(Symbol * lowSym, Symbol *highSym)
{
	type_t rangeType;
	struct Subrange *subRange = allocateSubRangeType();
	int low = 0, high = 0;
	if(getType(lowSym) == SCALAR_T){
		rangeType = getType(lowSym);
	}else{
		rangeType = getInnerTypeSymbol(lowSym)->kindPtr.TypeKind->type;
	}
	switch(rangeType) {
		case BOOLEAN_T:
			low = lowSym->kindPtr.ConstKind->value.Boolean.value;
			high = highSym->kindPtr.ConstKind->value.Boolean.value;
			break;
		case CHAR_T:
			low = lowSym->kindPtr.ConstKind->value.Char.value;
			high = highSym->kindPtr.ConstKind->value.Char.value;
			break;
		case INTEGER_T:
			low = lowSym->kindPtr.ConstKind->value.Integer.value;
			high = highSym->kindPtr.ConstKind->value.Integer.value;
			break;
		case SCALAR_T:
			low = lowSym->kindPtr.ConstKind->value.Integer.value;
			high = highSym->kindPtr.ConstKind->value.Integer.value;
			break;
		default:
			/* NOT REACHED */
			return NULL;
	}

	subRange->low = low;
	subRange->high = high;
	subRange->baseTypeSym = getInnerTypeSymbol(lowSym);

	return subRange;
}


/* Returns the pointer to the inner type symbol inside other symbols
 *
 * Parameters:
 *		symbol:
 *
 * Returns: see above
 */
Symbol *getInnerTypeSymbol(Symbol *symbol) {
	switch (symbol->kind) {
		case CONST_KIND:
			return symbol->kindPtr.ConstKind->typeSym;
		case PARAM_KIND:
			return symbol->kindPtr.ParamKind->typeSym;
		case FUNC_KIND:
			return symbol->kindPtr.FuncKind->typeSym;
		case VAR_KIND:
			return symbol->kindPtr.VarKind->typeSym;
		default:
			err(1, "Could not determine inner type of symbol");
	}
}


/* Formally setTypeSym(Symbol *s, Symbol *typeSym) changed for consistently 
 * getter.
 *
 * Sets the inner type symbol of the passed symbol
 * WARNING: assumes the kindPtr for the given symbol s has been allocated.
 *
 * Parameters:
 *		symbol: symbol where type symbol with be attached
 *		typeSym: type symbol
 *
 * Returns: void
 */
void setInnerTypeSymbol(Symbol *s, Symbol *typeSym) {
	switch (s->kind) {
		case CONST_KIND:
			s->kindPtr.ConstKind->typeSym = typeSym;
			break;
		case PARAM_KIND:
			s->kindPtr.ParamKind->typeSym = typeSym;
			break;		
		case FUNC_KIND:		
			s->kindPtr.FuncKind->typeSym = typeSym;
			break;
		case VAR_KIND:
			s->kindPtr.VarKind->typeSym = typeSym;
			break;
		default:
			err(1, "Could not determine inner type of symbol");
	}
}

/*
 * Calculate the size (in ASC memory units) of the given symbol of kind
 * TYPE_KIND.
 * Parameters
 *		s: the symbol whose size is to be calculated
 * Return
 *		the size of the symbol as an integer
 */
int calculateSymbolSize(Symbol *s)
{
	if (!s) {
		fprintf(stderr, "Cannot calculate size of null symbol!\n");
		exit(EXIT_FAILURE);
	}
	if (s->kind != TYPE_KIND) {
		fprintf(stderr, "Cannot calculate size of symbol which is not "
		    "of kind TYPE_KIND.\n");
		exit(EXIT_FAILURE);
	}

	switch (getKindPtrForTypeKind(s)->type) {
	case ARRAY_T:
		return calculateArraySize(s);
	case BOOLEAN_T:
	case CHAR_T:
	case INTEGER_T:
	case REAL_T:		/* basic pre-defined types have size == 1 */
	case SCALARINT_T:	/* a scalar int is just an int */
	case STRING_T:		/* string stored as pointer to heap */
		return 1;
	case RECORD_T:
		return 0;
	case SCALAR_T:
		return calculateScalarSize(s);
	case SUBRANGE_T:
		return calculateSubrangeSize(s);
	case VOID_T:
		return 0;
	default:
		/* NOT REACHED */
		return 0;
	}

}

/*
 * Calculates the size of the given symbol defining an array type (in ASC
 * memory units)
 * Parameters
 * 		s: the symbol, which if of kind TYPE_KIND and defines an 
 *		    array type, whose size is to be calculated.
 * Return:
 *		the size of the array symbol in ASC memory units (as an
 * 		    integer)
 */
int calculateArraySize(Symbol *s)
{
	struct Array *array = getTypePtr(s)->Array;
	int baseTypeSize = 0;

	/* Need to consider special case of array of records or scalars,in 
	 * this case, calculateSymbolSize() will not return correct results. */
	if (getType(array->baseTypeSym) == RECORD_T) {

		baseTypeSize = array->baseTypeSym->size;

	} else if(getType(array->baseTypeSym) == SCALAR_T) {

		baseTypeSize = 1;


	} else baseTypeSize = calculateSymbolSize(array->baseTypeSym);
	

	
	return ( (baseTypeSize) * (calculateSymbolSize(array->indexTypeSym)) );		
}

/*
 * Calculates the size of the given symbol defining a scalar list type (in ASC
 * memory units)
 * Parameters
 * 		s: the symbol, which if of kind TYPE_KIND and defines a 
 *		    scalar type, whose size is to be calculated.
 * Return:
 *		the size of the scalar list symbol in ASC memory units (as an
 * 		    integer)
 * TODO: probably dead code
 */
int calculateScalarSize(Symbol *s)
{
	struct Scalar *scalar = getTypePtr(s)->Scalar;
	return (scalar->consts->nElements); 
}


/*
 * Calculates the size of the given symbol defining a subrange type (in ASC
 * memory units)
 * Parameters
 * 		s: the symbol, which if of kind TYPE_KIND and defines a 
 *		    subrange type, whose size is to be calculated.
 * Return:
 *		the size of the subrange symbol in ASC memory units (as an
 * 		    integer)
 */
int calculateSubrangeSize(Symbol *s)
{	
	struct Subrange *subrange = getTypePtr(s)->Subrange;
	return ( ((subrange->high - subrange->low) + 1) *
	    calculateSymbolSize(subrange->baseTypeSym) );
}


/* Allocates memory for the StringType struct
 *
 * Parameters:
 *
 * Return: Pointer to newly allocated memory chunk
 */
struct StringType *allocateStringType() {
	struct StringType *newString = NULL;

	newString = calloc(1, sizeof(struct StringType));
	if ( newString == NULL ) {
		err(1, "Could not allocate memory for struct StringType!");
		exit(EXIT_FAILURE);
	}

	return newString;
}


/* Set the str member of the struct String
 *
 * Parameters:
 * 		string: struct String
 * 		str: char* to be copied into struct
 *		len: lenght of str
 *
 * Return: void
 */
void setStringStr(struct String *string, char *str, unsigned int len) {
	if (str == NULL) {
		string->str = NULL;
		string->strlen = 0;
		return;
	}
	else {
		/* extra byte for null termination */
		string->str = calloc(1, sizeof(char)*(len+1));
		if ( string->str == NULL) {
			err(EXIT_FAILURE, 
			    "Failed to allocate memory for string!");
		}

		strncpy(string->str, str, len);
		string->strlen = len;
		return;
	}
}


/*
 * Creates a new StringType struct
 * 
 * Parameters:
 * 	strlen: length for the new string type
 * Returns:
 * 	a pointer the the new struct
 */
struct StringType *newStringType(unsigned int strlen) {
	struct StringType *newStringType = allocateStringType();

	newStringType->strlen = strlen;

	return newStringType;
}



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
int isRealIntBool(type_t type) {
	if ( (type == REAL_T) 
		|| (type == INTEGER_T)
		|| (type == BOOLEAN_T) ) 
	{
		return 1;
	}

	return 0;
}


/* if the symbol is a scalar variable symbol 
 * returns 1 ,otherwise 0
 */
int isScalarVar(Symbol *sym){
	if (sym->kind == VAR_KIND){
		if(getType(sym) == SCALAR_T){
			return 1;
		}
	} 
	return 0;
}


/* if the symbol is a scalar member symbol 
 * returns 1 ,otherwise 0
 */
int isScalarMember(Symbol *sym){
	if (sym->kind == CONST_KIND){
		if(getType(sym) == SCALAR_T){
			return 1;
		}
	} 
	return 0;
}

/* 
 * Given that the symbol s is an array of chars or a string literal, returns
 * the length of the array/string.
 * Parameters
 *		s : the symbol (an array of chars or string literal) whose
 *		    length is to be returned
 */
int getStrSymLen(Symbol *s)
{
	switch (getType(s)) {
	case ARRAY_T:
		return s->size;
	case STRING_T:
		return getConstVal(s)->String.strlen;
	default:
		/* Should not be reached */
		fprintf(stderr, "Trying to get strlen of symbol which is not "
		    "a string literal or an array of chars.\n");
		exit(1);
	}
}
