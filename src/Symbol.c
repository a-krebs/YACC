#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Error.h"
#include "Type.h"
#include "Symbol.h"

extern int yylineno;
extern int colno;

static char *errMsg;

/*
 * 
 */
struct Symbol *
newArraySym(int lvl, char *id, struct Symbol *baseTypeSym,
	 struct Symbol *indexTypeSym)
{
	struct Symbol *newArraySym = NULL;
	size_t len;
	if ((!baseTypeSym) || (!indexTypeSym)) {
		errMsg = customErrorString("Semantic Error: cannot define array %s, \
				   base type or index type incorrect \
				   undefined? (%d, %d)", id, yylineno, colno);
		recordError(errMsg, yylineno, colno);
		return NULL;
	}
	if ((indexTypeSym->type != SCALAR_T) ||
	    (indexTypeSym->type != SUBRANGE_T)) {
		/* Error */
		return NULL;
	}

	newArraySym = calloc(1, sizeof(struct Symbol));
	if (!newArraySym) {
		err(1, "Failed to allocate memory for new array!");
		exit(1);
	}

	/* Set symbol entries for this symbol */

 	/* Have to explicitly check if id is set because we can have
	 * anonymous arrays (e.g., myArray : array[1..10] of array[1..10] of
	 * char )
	 */
	if (id) strcpy(newArraySym->name, id);
	else newArraySym->name = NULL;

	newArraySym->kind = TYPE_KIND;
	newArraySym->lvl = lvl;

	/* Now we proceed to creating the associated array type */

	/* Set array base type and base type pointer */
	newArraySym->typePtr.Array->baseType = baseTypeSym->type;	
	setTypePtr(&(newArraySym->typePtr.Array->baseTypePtr),
		    baseTypeSym->typePtr,
		    baseTypeSym->type);

	/* Set up index type and index type pointer */
	newArraySym->typePtr.Array->indexType = indexTypeSym->type;
	setTypePtr(&(newArraySym->typePtr.Array->indexTypePtr),
		    indexTypeSym->typePtr,
		    indexTypeSym->type);	

	
	return newArraySym;
}

/*
 * Creates a new parameter to be attached to a function. 
 * NOTE: each call to newParameter must be followed by a call to newVariable()
 *       in order to make the parameter available as a local variable in
 *       procedure/function definition body.
 * TODO: this function is UNTESTED
 */
struct Param *
newParameter(char *id, struct Symbol *typeSym)
{
	struct Param *newParam = NULL;

	if (!typeSym) {
		/* Record error */
		return NULL;
	}
	if (typeSym->kind != TYPE_KIND) {
		/* Record error */
		return NULL;
	}

	if (!id) {
		/* Error: canot have anonymous parameters! */
		return NULL;
	}

	
	newParam = calloc(1, sizeof(struct Param));
	if (!newParam) {
		err(1, "Failed to allocate memory for new parameter!");
		exit(1);
	}

	strcpy(newParam->name, id);
	newParam->type = typeSym->kind;
	return newParam;
}


/*
 * Creates a new variable struct to be added to the symbol table
 * given an identifier and an entry in the symbol table which is a type.
 */

struct Symbol *
newVariableSym(int lvl, char *id, struct Symbol* typeSym)
{
	struct Symbol *newVar = NULL;	/* new symbol to be created */
	size_t len;
	/*
	 * Before making any allocations, we assure that the given 
	 * symbol typeSym is in fact a type and that we can use it
	 * to create a new variable.
	 */
	if (!typeSym) {
		/* 
		 * ERROR: trying to create var for NULL symbol!
		 * --> probably using undefined type
		 * Call an error recording function.
		 */
		return NULL; 
	}

	if (typeSym->kind != TYPE_KIND) {
		/* ERROR: 
		 * Trying to create var using symbol other than a type.
		 * Call an error recording function.
		 */
		return NULL;	
	}

	if (!id) {
		/*Error: cannot have anonymous variable! */
		return NULL;
	}
		

	newVar = calloc(1, sizeof(struct Symbol));
	if (!newVar) {
		err(1, "Failed to allocate memory for new symbol!");
		exit(1);
	}
	
	/* Set variable name <- id */
	len = strlen(id);
	newVar->name = calloc(1, (sizeof(char))*len);
	if (!newVar->name) {
		err(1, "Failed to allocate memory for new symbol name!");
		exit(1);
	}	
	strcpy(newVar->name, id);

	newVar->kind = VAR_KIND;
	newVar->type = typeSym->type;
	newVar->typePtr = typeSym->typePtr;

	newVar->lvl = lvl;	
	return newVar;
}

/*
 * Constructs an anonymous subrange symbol.  
 * TODO: split this into two functions: newSubrangeSym() and newSubrange()
*	 where each one does the obvious thing.
 */
struct Symbol *
newSubrangeSym(int lvl, struct Symbol *constSymLow, 
	        struct Symbol *constSymHigh)
{
	struct Symbol *newSubrange = NULL;
	int high, low;
	/* 
	 * We must assure that we are constructing a subrange
	 * from two ordinal types of the same type of kind const such that
	 * the value of constSymLow is less than the value of constSymHigh.
	 */
	if ((!constSymLow) || (!constSymHigh)) {
		/* Error */
		return NULL;
	}

	if ((constSymLow->kind != CONST_KIND) ||
	    (constSymHigh->kind != CONST_KIND)) {
		/*Error: subranges indices not constants */
		return NULL;
	}

	if (constSymLow->type != constSymHigh->type) {
		/* Error:  Mismatched types for subrange indices */
		return NULL;
	}

	if (!isOrdinal(constSymLow->type)) {
		/* 
		 * Error: trying to construct subrange from non ordinal
		 * types
		 */
		return NULL;
	}

	/*
	 * Insure that values are bounded correctly (dependent on type ).
	 */
	switch (constSymLow->type) {
		case BOOLEAN_T:
		{
			low = constSymLow->typePtr.Boolean->value;
			high = constSymLow->typePtr.Boolean->value;	
			if (low >= high) {
				/* Error: lhs value not less than rhs value */
				return NULL;
			}
			break;
		}
		case CHAR_T:
		{
			low = constSymLow->typePtr.Char->value;
			high = constSymHigh->typePtr.Char->value;
			if (low >= high ) {
				/* Error: lhs value not less than rhs value */
				return NULL;
			}
			break;
		}
		case INTEGER_T:
		{
			low = constSymLow->typePtr.Integer->value;
			high = constSymHigh->typePtr.Integer->value;
			if (low >= high ) {
				/* Error: lhs value not less than rhs value */
				return NULL;
			}
			break;
		}
		default:
		{
			/* This shouldn't happen ... */
			return NULL;
		}
	}



	newSubrange = calloc(1, sizeof(struct Symbol));
	if (!newSubrange) {
		err(1, "Failed to allocate memory for new subrange symbol!");
		exit(1);
	}

	newSubrange->typePtr.Subrange = calloc(1, sizeof(struct Subrange));
	if (!newSubrange->typePtr.Subrange) {
		err(1, "Failed to allocate memory for new subrange!");
		exit(1);
	}
	
	newSubrange->kind = TYPE_KIND;
	newSubrange->typePtr.Subrange->low = low;
	newSubrange->typePtr.Subrange->high = high;
	newSubrange->type = SUBRANGE_T;
	newSubrange->typePtr.Subrange->baseType = constSymLow->type;
	newSubrange->name = NULL;
	newSubrange->lvl = lvl;
	/* Set base type pointer for new subrange */
	switch (newSubrange->typePtr.Subrange->baseType) {
		case BOOLEAN_T:
		{
			newSubrange->typePtr.Subrange->baseTypePtr.Boolean =
			    constSymLow->typePtr.Boolean;
			break;
		}
		case CHAR_T:
		{
			newSubrange->typePtr.Subrange->baseTypePtr.Char =
			    constSymLow->typePtr.Char;
			break;
		}
		case INTEGER_T:
		{
			newSubrange->typePtr.Subrange->baseTypePtr.Integer =
			    constSymLow->typePtr.Integer;
			break;
		}
		default:
			break;
	}
	
	return newSubrange;
}

/*
 * Creates a new procedure symbol entry to be placed in the symbol table.
 * TODO: split this into two functions: newProcedureSym() and newProcedure() 
 */
struct Symbol *
newProcedureSym(int lvl, char *id, struct ParamArray *pa)
{

	struct Symbol *newProcSym = NULL;
	unsigned int i;
	size_t len;
	if (!pa) {
		/* Don't pass NULL if no params, pass empty param array. */
		return NULL;
	}

	if (!id) {
		/* Cannot create anonymous procedure! */
		return NULL;
	}

	newProcSym = calloc(1, sizeof(struct Symbol));
	if (!newProcSym) {
		err(1, "Failed to allocate memory for new procedure symbol!");
		exit(1);		
	}
	newProcSym->typePtr.Procedure = calloc(1, sizeof(struct Procedure));
	if (!newProcSym->typePtr.Procedure) {
		err(1, "Failed to allocate memory for new procedure symbol!");
		exit(1);
	}	

	len = strlen(id);
	if (!len) {
		/* procdure cannot have 0 length name */
		return NULL;	
	}
	strcpy(newProcSym->name, id);
	newProcSym->kind = PROC_KIND;
	newProcSym->type = PROCEDURE_T;
	newProcSym->typePtr.Procedure->params = pa;
	newProcSym->lvl = lvl;
	return newProcSym;	
}


