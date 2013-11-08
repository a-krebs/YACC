#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Error.h"
#include "Type.h"
#include "Symbol.h"
#include "Hash.h"

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

	setSymbolName(newTypeSym, id);
	newTypeSym->kind = TYPE_KIND;
	newTypeSym->kindPtr = typeSym->kindPtr;
	
	/* 
	 * Type is being constructed from anonymous type, it is NOT a type
	 * originator
	 */
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
		    " array, base type or index type incorrect/undefined?");
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}

	if ((baseTypeSym->kind != TYPE_KIND) || 
	    (baseTypeSym->kind != TYPE_KIND)) {
		errMsg = customErrorString("Cannot create array with given"
		    "base type");
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}
	if ((getType(indexTypeSym) != SCALAR_T) &&
	    (getType(indexTypeSym) != SUBRANGE_T)) {
		errMsg = customErrorString("Trying to index array using non-"
		    "index type %s", typeToString(getType(indexTypeSym)));
		recordError(errMsg, yylineno, colno, SEMANTIC);
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


/*
 * Creates a new variable struct to be added to the symbol table
 * given an identifier and an entry in the symbol table which is a type.
 */

Symbol *
newVariableSym(int lvl, char *id, Symbol* typeSym)
{
	Symbol *newVar = NULL;	/* new symbol to be created */
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
	
	setSymbolName(newVar, id);
	newVar->kind = VAR_KIND;
	allocateKindPtr(newVar);
	newVar->kindPtr.VarKind->typeSym = typeSym;
	newVar->lvl = lvl;
	return newVar;
}

Symbol *
newParameterSym(int lvl, char *id, Symbol *typeSym)
{
	Symbol *newParamSym = NULL;
	if (!typeSym) {
		return NULL;
	}

	if (!id) {
		return NULL;
	}

	newParamSym = calloc(1, sizeof(Symbol));
	if (!newParamSym) {
		err(1, "Failed to allocate memory for new parameter symbol!");
		exit(1);
	}

	setSymbolName(newParamSym, id);
	newParamSym->kind = PARAM_KIND;
	allocateKindPtr(newParamSym);
	newParamSym->kindPtr.ParamKind->typeSym = typeSym;
	newParamSym->lvl = lvl;
	return newParamSym;	
}
/*
 * Constructs an anonymous subrange symbol.
 */
Symbol *
newSubrangeSym(int lvl, ProxySymbol *constSymLow,
	        ProxySymbol *constSymHigh)
{
	Symbol *newSubrangeSym = NULL;
	
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

	if (getType(constSymLow) != getType(constSymHigh)) {
		/* Error:  Mismatched types for subrange indices */
		return NULL;
	}

	if (!isOrdinal(getType(constSymLow))) {
		/*
		 * Error: trying to construct subrange from non ordinal
		 * types
		 */
		return NULL;
	}

	/*
	 * Insure that values are bounded correctly (dependent on type ).
	 */

	switch(getType(constSymLow)) {
	case INTEGER_T:
		if (getConstVal(constSymLow)->Integer.value >
		    getConstVal(constSymHigh)->Integer.value) return NULL;
		break;
	case BOOLEAN_T:
		if (getConstVal(constSymLow)->Boolean.value >
		    getConstVal(constSymHigh)->Boolean.value) return NULL;
		break;
	case CHAR_T:
		if (getConstVal(constSymLow)->Char.value >
		    getConstVal(constSymHigh)->Char.value) return NULL;
		break;
	default:
		return NULL;
	}


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
	newSubrangeSym->name = NULL;
	newSubrangeSym->lvl = lvl;
	newSubrangeSym->typeOriginator = 1;	
	return newSubrangeSym;
}

/*
 * Creates a new procedure symbol entry to be placed in the symbol table.
 */
Symbol *
newProcedureSym(int lvl, char *id, struct ElementArray *pa)
{
	return NULL;
	/*
	Symbol *newProcSym = NULL;
	size_t len;
	if (!pa) {

	if (!id) {
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
		return NULL;
	}
	strcpy(newProcSym->name, id);
	newProcSym->kindPtr.ProcKind->params = pa;
	newProcSym->lvl = lvl;
	return newProcSym;
	*/
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
	case PARAM_KIND:
		return s->kindPtr.ParamKind->typeSym;
	case PROC_KIND: 
		/* Procedures do not have associate type symbols */
		return NULL;
	case FUNC_KIND:
		return s->kindPtr.FuncKind->typeSym;
	case TYPE_KIND:
		return s;
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
	Symbol *constSym = NULL;
	double *doubleResult;
	int *intResult;
	
	constSym = calloc(1, sizeof(ProxySymbol));
	if (!constSym) {
		err(1, "Failed to allocate memory for new constant proxy "
		    "symbol!");
		exit(1);
	}

	constSym->name = NULL;
	constSym->kind = CONST_KIND;
	allocateKindPtr(constSym);
	setTypeSym(constSym, typeSym);
	
	switch (getType(typeSym)) {
	case BOOLEAN_T:
		intResult = (int *) result;
		getConstVal(constSym)->Boolean.value = *intResult;
		break;
	case INTEGER_T:
		intResult = (int *) result;
		getConstVal(constSym)->Integer.value = *intResult;
		break;
	case REAL_T:
		doubleResult = (double *) result;
		getConstVal(constSym)->Real.value = *doubleResult;
		break;
	default:
		/* Shouldn't be reached */
		return NULL;
	}
	return (ProxySymbol *) constSym;
}

ProxySymbol *
newStringProxySym(int lvl, char *str, int strlen)
{
	ProxySymbol *newStringSym = NULL;
	newStringSym = calloc(1, sizeof (ProxySymbol));
	newStringSym->name = NULL;
	newStringSym->kind = TYPE_KIND;
	allocateKindPtr(newStringSym);
	getTypePtr(newStringSym)->String->strlen = strlen;
	
	if (strlen) {
		getTypePtr(newStringSym)->String->str = 
		    calloc(1, sizeof(char)*strlen);
		if (!getTypePtr(newStringSym)->String->str) {
			err(1, "Failed to allocate memory for new string");
			exit(1);
		}
	}
	newStringSym->lvl = lvl;
	newStringSym->typeOriginator = 1;
	return newStringSym;	
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

/*
 * Create a new symbol for a record type defintion to be added to the symbol
 * table.
 * 
 * Return a pointer to the new type symbol.
 */

Symbol *newRecordTypeSym(int lvl, char *id)
{
	Symbol *newRecType = NULL;	/* new symbol to be created */

	if (!id) {
		/*Error: cannot have anonymous variable! */
		return NULL;
	}
		

	newRecType = calloc(1, sizeof(Symbol));
	if (!newRecType) {
		err(1, "Failed to allocate memory for new symbol!");
		exit(1);
	}
	
	setSymbolName(newRecType, id);
	newRecType->kind = TYPE_KIND;
	allocateKindPtr(newRecType);
	newRecType->kindPtr.TypeKind->type = RECORD_T;
	newRecType->kindPtr.TypeKind->typePtr.Record = newRecord();

	newRecType->lvl = lvl;

	/* this is an anonymous type */
	newRecType->typeOriginator = 1;

	return newRecType;
}

/*
 * Add the given field to the record type.
 *
 * Return 0 on success and non-zero on error.
 * 	return 	-2 if adding hash element to record fails
 * 		-1 on argument error
 * 		1 on recType type error
 * 		2 on field type error
 */
int addFieldToRecord(Symbol *recType, ProxySymbol *field) {

	Symbol *newField = NULL;
	int recordLvl = -1;
	char *id = NULL;
	struct hash *recordHash = NULL;

	/* check arguments */
	if (!recType) {
		return -1;
	}
	if (!newField) {
		return -1;
	}

	/* check record symbol for correct kind */
	if (recType->kind != TYPE_KIND) {
		return 1;
	}
	if (recType->kindPtr.TypeKind->type != RECORD_T) {
		return 1;
	}

	/* check field symbol for correct kind */
	if (newField->kind != VAR_KIND) {
		return 2;
	}

	recordHash = recType->kindPtr.TypeKind->typePtr.Record->hash;
	recordLvl = getCurrentLexLevel(recordHash);
	id = strdup(field->name);

	newField = newVariableSym(
	    recordLvl, id, field->kindPtr.VarKind->typeSym);

	if (createHashElement(recordHash, id, newField) != 0) {
		return -2;
	}

	return 0;
}

