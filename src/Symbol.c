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
 * Constructs a	named type symbol given a ptr to another type symbol.
 * (so the new symbol will either be constructed from an anonymous type symbol
 * or be a copy of another named symbol) 
 */
Symbol *
newTypeSymFromSym(int lvl, char *id, Symbol *typeSym)
{
	Symbol *newTypeSym = NULL;
	size_t len;
	if (!typeSym) {
		return NULL;
	}

	if (typeSym->kind != TYPE_KIND) {
		/* Trying to construct type symbol from non-type symbol */
		return NULL;
	}

	if (!id) {
		/* Error: trying to create named symbol from NULL id */
		return NULL;
	}

	newTypeSym = calloc(1, sizeof(Symbol));
	if (!newTypeSym) {exit(1); /* blah blah */ }

	len = strlen(id);
	newTypeSym->name = calloc(1, sizeof(char)*len);
	if (!newTypeSym->name) exit(1);

	strcpy(newTypeSym->name, id);
	newTypeSym->kind = TYPE_KIND;
	newTypeSym->kindPtr = typeSym->kindPtr;
	newTypeSym->typeOriginator = 0;
	return newTypeSym;
}

/*
 * Creates a new anonymous array type symbol given a pointer to a symbol
 * defining the base type and a pointer to a symbol defining the index type.
 */
Symbol *
newAnonArraySym(int lvl, Symbol *baseTypeSym, 
	    Symbol *indexTypeSym)
{
	Symbol *newArraySym = NULL;
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

	newArraySym = calloc(1, sizeof(Symbol));
	if (!newArraySym) {
		err(1, "Failed to allocate memory for new array!");
		exit(1);
	}

	/* Set symbol entries for this symbol */
	newArraySym->name = NULL;
	newArraySym->kind = TYPE_KIND;
	allocateKindPtr(newArraySym);
	newArraySym->kindPtr.TypeKind->typePtr.Array = newArray(baseTypeSym,
								indexTypeSym);
	newArraySym->lvl = lvl;
	newArraySym->typeOriginator = 1; /* should already be set */
	return newArraySym;
}


/* /\* */
/*  * Creates a new parameter to be attached to a function.  */
/*  * NOTE: each call to newParameter must be followed by a call to newVariable() */
/*  *       in order to make the parameter available as a local variable in */
/*  *       procedure/function definition body. */
/*  *\/ */
/* struct Param * */
/* newParameter(char *id, Symbol *typeSym) */
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

Symbol *
newVariableSym(int lvl, char *id, Symbol* typeSym)
{
	Symbol *newVar = NULL;	/* new symbol to be created */
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
		

	newVar = calloc(1, sizeof(Symbol));
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
	allocateKindPtr(newVar);
	newVar->kindPtr.VarKind->typeSym = typeSym;
	newVar->lvl = lvl;
	return newVar;
}

/*
 * Constructs an anonymous subrange symbol.
 */
Symbol *
newSubrangeSym(int lvl, Symbol *constSymLow,
	        Symbol *constSymHigh)
{
	Symbol *newSubrangeSym = NULL;
	Symbol *lowSymType = constSymLow->kindPtr.ConstKind->typeSym;
	Symbol *highSymType = constSymHigh->kindPtr.ConstKind->typeSym;
	
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

	newSubrangeSym = calloc(1, sizeof(Symbol));
	if (!newSubrangeSym) {
		err(1, "Failed to allocate memory for new subrange symbol!");
		exit(1);
	}

	newSubrangeSym->kind = TYPE_KIND;
	allocateKindPtr(newSubrangeSym);

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
Symbol *
newProcedureSym(int lvl, char *id, struct ParamArray *pa)
{

	Symbol *newProcSym = NULL;
	size_t len;
	if (!pa) {
		/* Don't pass NULL if no params, pass empty param array. */
		return NULL;
	}

	if (!id) {
		/* Cannot create anonymous procedure! */
		return NULL;
	}

	newProcSym = calloc(1, sizeof(Symbol));
	if (!newProcSym) {
		err(1, "Failed to allocate memory for new procedure symbol!");
		exit(1);
	}

	newProcSym->kind = PROC_KIND;
	allocateKindPtr(newProcSym);	

	len = strlen(id);
	if (!len) {
		/* procdure cannot have 0 length name */
		return NULL;
	}
	strcpy(newProcSym->name, id);
	newProcSym->kindPtr.ProcKind->params = pa;
	newProcSym->lvl = lvl;
	return newProcSym;
}

/* Symbol* */
/* newConstSym(int lvl, char * id, Symbol * constTypeSym) */
/* { */
/* 	return NULL; */
/* } */

/* Symbol* */
/* newConstSymFromType(int lvl, Type constType, type_t type) */
/* { */
/* 	Symbol *newConstSym = calloc(1, sizeof(Symbol)); */
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

/*
 * TODO: proxy symbol will have kindPtr to pre-defined kind?
 */
Symbol *
newConstSymFromProxy(int lvl, char * id, ProxySymbol * proxySym)
{
	Symbol * newConstSym = NULL;

	/* Error checking */
	if (!proxySym) {
		/* Record error */
		return NULL;
	}

	if (proxySym->kind != CONST_KIND) {
		/* Error: trying to declare constant with non-constant kind */
		return NULL;
	}

	newConstSym = calloc(1, sizeof(Symbol));
	if (!newConstSym) {
		err(1, "Failed to allocate memory for new const symbol!");
		exit(1);
	}	

	setSymbolName(newConstSym, id);
	
	newConstSym->kind = CONST_KIND;
	allocateKindPtr(newConstSym);
	newConstSym->kindPtr.ConstKind->typeSym = getTypeSym(proxySym);
	copyConstVal(&(newConstSym->kindPtr.ConstKind->value), 
	    getConstVal(proxySym), getType(proxySym));
	newConstSym->lvl = lvl;

	return newConstSym;
}


/*
 * Returns a pointer to the Symbol of TYPE_KIND defining the type for the
 * given CONST_KIND, FUNC_KIND, PROC_KIND, or VAR_KIND symbol.  Returns
 * NULL for Symbols of TYPE_KIND.
 */
Symbol *
getTypeSym(Symbol *s) 
{
	if (!s) return NULL;

	switch (s->kind) {
	case CONST_KIND:
		return s->kindPtr.ConstKind->typeSym;
	case PROC_KIND: 
		/* Procedures do not have associate type symbols */
		return NULL;
	case FUNC_KIND:
		return s->kindPtr.FuncKind->typeSym;
	case TYPE_KIND:
		/* 
		 * Symbol is itself a type symbol -- its typePtr may
		 * depend on other type (potentially multiple) Symbols
		 * so we need to call more specific functions */
		return NULL;
	case VAR_KIND:
		return s->kindPtr.VarKind->typeSym;
	default:
		/* NOT REACHED */
		return NULL;
	}
}

/*
 * Creates a new CONST_KIND ProxySymbol using the result of a arithmetic,
 * logical or arithmetic operation on two constants. 
 */
ProxySymbol *
newConstProxySym(void * result, Symbol *typeSym)
{
	switch (getType(typeSym)) {
	case BOOLEAN_T:
		return newBooleanConstProxySym((int *) result, typeSym);
	case INTEGER_T:
		return newIntegerConstProxySym((int *)result, typeSym);
	case REAL_T:
		return newRealConstProxySym((double *) result, typeSym);
	default:
		/* Shouldn't be reached */
		return NULL;
	}
}

ProxySymbol *
newBooleanConstProxySym(int *result, Symbol *typeSym)
{
	Symbol *constSym = NULL;
	constSym = calloc(1, sizeof(ProxySymbol));
	if (!constSym) {
		err(1, "Failed to allocate memory for new constant symbol!");
		exit(1);
	}
	constSym->name = NULL;
	constSym->kind = CONST_KIND;
	allocateKindPtr((Symbol *)constSym);
	setTypeSym(constSym, typeSym);	
	getConstVal(constSym)->Boolean.value = *result;
	return (ProxySymbol *) constSym;
}

ProxySymbol *
newIntegerConstProxySym(int *result, Symbol *typeSym)
{
	return NULL;
}

ProxySymbol *
newRealConstProxySym(double *result, Symbol *typeSym)
{
	return NULL;
}

void
setSymbolName(Symbol *s, char *id)
{
	size_t len;
	if (!id) return;
	
	len = strlen(id);
	s->name = calloc(1, sizeof(char)*len);
	if (!s->name) {
		err(1, "Failed to allocate memory for symbol name!");
		exit(1);
	}
	strcpy(s->name, id);
}
