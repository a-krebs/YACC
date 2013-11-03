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
 * Constructs a	named array symbol given a ptr to an array type symbol.
 * (so the new symbol will either be constructed from an anonymous array
 * type symbol or be a "copy" of another named array type symbol) 
 */
struct Symbol *
newArraySymFromSym(int lvl, char *id, struct Symbol *arrayTypeSym)
{
	struct Symbol *newArraySym = NULL;
	struct Array *oldArray = NULL;

	if (!arrayTypeSym) {
		return NULL;
	}

	if (!arrayTypeSym->kindPtr.TypeKind->typePtr.Array) {
		return NULL;
	}

	if (!id) {
		/* Error: trying to create named symbol from NULL id */
		return NULL;
	}


	oldArray = arrayTypeSym->kindPtr.TypeKind->typePtr.Array;

	/* TODO: check arrayTypeSym baseTypeSym and indexTypeSym */


	newArraySym = newAnonArraySym(lvl, oldArray->baseTypeSym,
					   oldArray->indexTypeSym);

	strcpy(newArraySym->name, id);
	newArraySym->kind = TYPE_KIND;
	newArraySym->kindPtr.TypeKind->type = ARRAY_T;	
	return newArraySym;
}

/*
 * Creates a new anonymous array type symbol given a pointer to a symbol
 * defining the base type and a pointer to a symbol defining the index type.
 */
struct Symbol *
newAnonArraySym(int lvl, struct Symbol *baseTypeSym, 
	    struct Symbol *indexTypeSym)
{
	struct Symbol *newArraySym = NULL;
	if ((!baseTypeSym) || (!indexTypeSym)) {
		errMsg = customErrorString("Semantic Error: cannot define"
					   "array, base type or index type"
					   "incorrect/undefined? (%d, %d)", 
					    yylineno, colno);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}
	if ((indexTypeSym->kindPtr.TypeKind->type != SCALAR_T) &&
	    (indexTypeSym->kindPtr.TypeKind->type != SUBRANGE_T)) {
		/* Error */
		return NULL;
	}

	newArraySym = calloc(1, sizeof(struct Symbol));
	if (!newArraySym) {
		err(1, "Failed to allocate memory for new array!");
		exit(1);
	}

	/* Set symbol entries for this symbol */

	 
	newArraySym->name = NULL;
	newArraySym->kind = TYPE_KIND;
	
	newArraySym->kindPtr.TypeKind = calloc(1, sizeof(Type));
	if (!newArraySym->kindPtr.TypeKind) {
		err(1, "Failed to allocate memory for Type struct!");
		exit(1);
	}
	newArraySym->kindPtr.TypeKind->typePtr.Array = newArray(baseTypeSym,
								indexTypeSym);
	newArraySym->lvl = lvl;
	
	return newArraySym;
}


/* /\* */
/*  * Creates a new parameter to be attached to a function.  */
/*  * NOTE: each call to newParameter must be followed by a call to newVariable() */
/*  *       in order to make the parameter available as a local variable in */
/*  *       procedure/function definition body. */
/*  *\/ */
/* struct Param * */
/* newParameter(char *id, struct Symbol *typeSym) */
/* { */
/* 	struct Param *newParam = NULL; */
/* 	size_t len; */

/* 	if (!typeSym) { */
/* 		/\* Record error *\/ */
/* 		return NULL; */
/* 	} */
/* 	if (typeSym->kind != TYPE_KIND) { */
/* 		/\* Record error *\/ */
/* 		return NULL; */
/* 	} */

/* 	if (!id) { */
/* 		/\* Error: canot have anonymous parameters! *\/ */
/* 		return NULL; */
/* 	} */
	
/* 	len = strlen(id); */
/* 	if (!len) { */
/* 		/\* Cannot have param with 0 length name! *\/ */
/* 		return NULL; */
/* 	} */

/* 	newParam = calloc(1, sizeof(struct Param)); */
/* 	if (!newParam) { */
/* 		err(1, "Failed to allocate memory for new parameter!"); */
/* 		exit(1); */
/* 	} */

/* 	strcpy(newParam->name, id); */
/* 	newParam->type = typeSym->type; */
/* 	setTypePtr(&(newParam->typePtr), typeSym->typePtr, typeSym->type); */
/* 	return newParam; */
/* } */


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

	newVar->kindPtr.VarKind = calloc(1, sizeof(Type));
	if (!newVar->kindPtr.VarKind) {
		err(1, "Failed to allocate memory for new symbol name!");
		exit(1);
	}
	newVar->kindPtr.VarKind->typeSym = typeSym;
	newVar->lvl = lvl;
	return newVar;
}

/*
 * Constructs an anonymous subrange symbol.
 */
struct Symbol *
newSubrangeSym(int lvl, struct Symbol *constSymLow,
	        struct Symbol *constSymHigh)
{
	struct Symbol *newSubrangeSym = NULL;
	struct Symbol *lowSymType = constSymLow->kindPtr.ConstKind->typeSym;
	struct Symbol *highSymType = constSymHigh->kindPtr.ConstKind->typeSym;
	
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

	if (lowSymType->kindPtr.TypeKind->type != 
	    highSymType->kindPtr.TypeKind->type) {
		/* Error:  Mismatched types for subrange indices */
		return NULL;
	}

	if (!isOrdinal(lowSymType->kindPtr.TypeKind->type)) {
		/*
		 * Error: trying to construct subrange from non ordinal
		 * types
		 */
		return NULL;
	}

	/*
	 * Insure that values are bounded correctly (dependent on type ).
	 */

	newSubrangeSym = calloc(1, sizeof(struct Symbol));
	if (!newSubrangeSym) {
		err(1, "Failed to allocate memory for new subrange symbol!");
		exit(1);
	}

	newSubrangeSym->kindPtr.TypeKind = calloc(1, sizeof(Type));
	if (!newSubrangeSym->kindPtr.TypeKind) {
		err(1, "Failed to allocate memory for type struct!");
		exit(1);
	}

	newSubrangeSym->kindPtr.TypeKind->type = SUBRANGE_T;
	newSubrangeSym->kindPtr.TypeKind->typePtr.Subrange = newSubrange(
								  constSymLow,
								  constSymHigh);

	newSubrangeSym->kind = TYPE_KIND;
	newSubrangeSym->name = NULL;
	newSubrangeSym->lvl = lvl;
	
	return newSubrangeSym;
}

/*
 * Creates a new procedure symbol entry to be placed in the symbol table.
 */
struct Symbol *
newProcedureSym(int lvl, char *id, struct ParamArray *pa)
{

	struct Symbol *newProcSym = NULL;
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
	newProcSym->kindPtr.ProcKind = calloc(1, sizeof(struct ProcedureKind));
	if (!newProcSym->kindPtr.ProcKind) {
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
	newProcSym->kindPtr.ProcKind->params = pa;
	newProcSym->lvl = lvl;
	return newProcSym;
}

/* struct Symbol* */
/* newConstSym(int lvl, char * id, struct Symbol * constTypeSym) */
/* { */
/* 	return NULL; */
/* } */

/* struct Symbol* */
/* newConstSymFromType(int lvl, Type constType, type_t type) */
/* { */
/* 	struct Symbol *newConstSym = calloc(1, sizeof(struct Symbol)); */
/* 	if (!newConstSym) { */
/* 		err(1, "Failed to allocate memory for new const symbol!"); */
/* 		exit(1); */
/* 	} */
	
	
/* 	setTypePtr(&(newConstSym->typePtr), constType, type); */
/* 	newConstSym->name = NULL; */
/* 	newConstSym->kind = CONST_KIND; */
/* 	newConstSym->lvl = lvl; */

/* 	return newConstSym; */
/* } */
