#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ElementArray.h"
#include "Error.h"
#include "ErrorLL.h"
#include "Type.h"
#include "SymbolAll.h"
#include "Hash.h"
#include "PreDef.h"

/*For error reporting*/
extern int yylineno;
extern int colno;
static char *errMsg;
struct Error *e;



/*
 * Create a new type symbol for an array type.
 *
 * Parameters:
 * 	id: the type's name
 * 	typeOriginator: typeOriginator flag
 * 	base: the array base type
 * 	index: the array index type
 *
 * Return:
 * 	Return a pointer to the new symbol.
 */
Symbol *createArrayTypeSymbol(
   char *id, int typeOriginator, Symbol *base, Symbol *index)
{
	Symbol *symbol = NULL;
	struct TypeKind *kindPtr = NULL;
	if ((base == NULL) || (index == NULL)) {
		err(EXIT_FAILURE, "Trying to create array type with NULL "
		    "index or base types. This should be caught further "
		    "up in Symbols.c");
	}
	
	symbol = createTypeSymbol(id, typeOriginator);
	
	/* get kindPtr */
	kindPtr = getKindPtrForTypeKind(symbol);

	/* set array's Array struct */
	kindPtr->type = ARRAY_T;
	kindPtr->typePtr.Array = newArray(base, index);
 	
	return symbol;
}


/*
 * Create a new type symbol for a scalar list type.
 *
 * Parameters:
 * 	id: the type's name
 * 	typeOriginator: typeOriginator flag
 * 	scalars: the list of constants that are part of this type
 *
 * Return:
 * 	A pointer to the new symbol
 */
Symbol *createScalarListTypeSymbol(
    char *id, int typeOriginator, struct ElementArray *scalars)
{
	Symbol *symbol = NULL;
	struct TypeKind *kindPtr = NULL;
	if (scalars == NULL) {
		err(EXIT_FAILURE, "Trying to make a new scalar list type "
		    "with empty list. This should be caught further up in "
		    "Symbols.c");
	}

	symbol = createTypeSymbol(id, typeOriginator);
	kindPtr = getKindPtrForTypeKind(symbol);

	/* set scalar list's Scalar struct */
	kindPtr->type = SCALAR_T;
	kindPtr->typePtr.Scalar = newScalar(scalars);

	return symbol;
}


/* Creates a varable symbol adds the inner type symbol. 
 *
 * Parameters:
 *              id: name of symbol
 *		typeSym: type symbol to be put in new var symbol
 *
 * Return: Newly created symbol
 */
Symbol *newVariableSym(char *id, Symbol* typeSym) {
	Symbol *newVar = NULL;	/* new symbol to be created */

	/*
	 * Before making any allocations, we assure that the given
	 * symbol typeSym is in fact a type and that we can use it
	 * to create a new variable.
	 */
	if (typeSym == NULL) {
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
		// getKindPtrForTypeKind
	}

	if (id == NULL) {
		/*Error: cannot have anonymous variable! */
		return NULL;
	}
	
	newVar = createVarSymbol(id);
	setInnerTypeSymbol(newVar, typeSym);
	
	return newVar;
}


/* Creates a parameter symbol and sets the inner type symbol
 *
 * Parameters:
 *              id: name of symbol
 *		typeSym: type symbol to be put in new var symbol
 *
 * Return: Newly created symbol
 */
Symbol *newParamSym(char *id, Symbol *typeSym) {
	Symbol *newParamSym = NULL;
	if (!typeSym) {
		return NULL;
	}

	if (!id) {
		return NULL;
	}

	newParamSym = createParamSymbol(id);
	setInnerTypeSymbol(newParamSym, typeSym);

	return newParamSym;	
}


/* Creates a procedure symbol 
 *
 * Parameters:
 *              id: name of symbol
 *		ea: element of parameters to procdure
 *
 * Return: Newly created symbol
 */
Symbol *newProcSym(char *id, struct ElementArray *ea) {
	Symbol *s =  createProcSymbol(id);
	s->kindPtr.ProcKind->params = ea;

	return s;	
}


/* Creates a fucntion symbol and sets the inner type symbol
 *
 * Parameters:
 *              id: name of symbol
 *		typeSym: type symbol to be put in new var symbol
 *
 * Return: Newly created symbol
 */
Symbol *newFuncSym(
    int lvl, char *id, Symbol *typeSym, struct ElementArray *ea)
{
	Symbol *s = createFuncSymbol(id); 

	s->kindPtr.FuncKind->params = ea;
	setInnerTypeSymbol(s, typeSym);

	return s;
}


/*
 * Create a new symbol for a record type defintion to be added to the symbol
 * table.
 * 
 * Parameters:
 *              id: name of symbol
 *
 * Return a pointer to the new type symbol.
 */
Symbol *newRecordTypeSym(char *id) {
	/* this is an anonymous type */
	Symbol *newRecType = createTypeSymbol(id, TYPEORIGINATOR_YES);

	newRecType->kindPtr.TypeKind->type = RECORD_T;
	newRecType->kindPtr.TypeKind->typePtr.Record = newRecord();

	return newRecType;
}


 /*
 * Constructs an anonymous subrange symbol.
 * 
 * Parameters:
 *              constSymLow: pointer to symbol holding lower bound info
 *              constSymHigh: pointer to symbol holding uppper bound info
 *
 * Return a pointer to the new subrange symbol.
 */
Symbol *newSubrangeSym(ProxySymbol *constSymLow, ProxySymbol *constSymHigh) {
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
		break;
	}

	newSubrangeSym = createTypeSymbol(NULL, TYPEORIGINATOR_YES);
	newSubrangeSym->kindPtr.TypeKind->type = SUBRANGE_T;
	newSubrangeSym->kindPtr.TypeKind->typePtr.Subrange = newSubrange(
								  constSymLow,
								  constSymHigh);
	return newSubrangeSym;
}


/*
 * Constructs a non-anonymous type symbol given a ptr to another type symbol.
 * (so the new symbol will either be constructed from an anonymous type symbol
 * or be a copy of another named symbol)
 *
 * Lexical level is NOT set, and symbol is NOT inserted into symbol table.
 *
 * Parameters:
 * 	id: name of created symbol
 * 	typeSym: symbol from which type is to be taken. Must be TYPE_KIND
 *
 * Returns: pointer to created symbol, or NULL on error
 *
 */
Symbol *newTypeSymFromSym(char *id, Symbol *typeSym) {
	Symbol *newTypeSym = NULL;
	if (!typeSym) {
		/* action that gets type has already added an error message */
		return NULL;
	}

	if (typeSym->kind != TYPE_KIND) {
		/* Trying to construct type symbol from non-type symbol */
		errMsg = customErrorString("Identifier %s is not a type.",
		    typeSym->name);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}

	if (!id) {
		/* Error: trying to create named symbol from NULL id */
		err(EXIT_FAILURE, "Trying to create named type symbol "
		    "but name is NULL.");
	}

	/* 
	 * Type is being constructed from anonymous type, it is NOT a type
	 * originator
	 */
	newTypeSym = createTypeSymbol(id, 0);

	/* set type pointer to same as typeSym */
	newTypeSym->kindPtr = typeSym->kindPtr;
	
	return newTypeSym;
}


/*
 * Creates a new anonymous array type symbol given a pointer to a symbol
 * defining the base type and a pointer to a symbol defining the index type.
 *
 * Parameters:
 * 	baseTypeSym: the symbol for the base type. Should be TYPE_KIND
 * 	indexTypeSym: the symbol for the index type. Should be TYPE_KIND
 *
 * Return:
 * 	pointer to new symbol with kind TYPE_KIND and kindPtr type ARRAY_T
 */
Symbol *newAnonArraySym(Symbol *baseTypeSym, Symbol *indexTypeSym) {
	Symbol *newArraySym = NULL;

	if ((!baseTypeSym) || (!indexTypeSym)) {
		errMsg = customErrorString("Cannot define array. "
		    "Base type or index type incorrect or undefined.");
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}

	if ((baseTypeSym->kind != TYPE_KIND) || 
	    (baseTypeSym->kind != TYPE_KIND)) {	
		errMsg = customErrorString("Cannot create array with given "
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

	/* create with no name and set as type originator */
	newArraySym = createArrayTypeSymbol(
	     NULL, TYPEORIGINATOR_YES, baseTypeSym, indexTypeSym);
	if (!newArraySym) {
		err(EXIT_FAILURE, "Failed to allocate memory for new array!");
	}

	return newArraySym;
}


/*
 * Create a new symbol for an anonymous scalar list type.
 *
 * Parameters:
 * 	ea: the list of scalars that are part of this list
 *
 * Return:
 * 	a symbol to the new type.
 */
Symbol *newAnonScalarListTypeSym(struct ElementArray *ea) {
	Symbol *newAnonScalarList = NULL;

	if (ea == NULL) {
		err(EXIT_FAILURE, "Trying to create anon scalar list with "
		    "NULL list of scalars.");
	}

	/* anonymous, so name is NULL */
	newAnonScalarList = createScalarListTypeSymbol(
	    NULL, TYPEORIGINATOR_YES, ea);

	return newAnonScalarList;
}

/* 
 * Create a new symbol for String Type Symbol using the given length
 *
 * Parameters:
 * 	strlen: length of string 
 *
 * Return:
 * 	a symbol to the new type.
 */
Symbol *newStringTypeSym(int strlen) {
	Symbol *newStringSym = createTypeSymbol(NULL, TYPEORIGINATOR_YES);
	
	/* get kindPtr */
	struct TypeKind *kindPtr = getKindPtrForTypeKind(newStringSym);

	kindPtr->type = STRING_T;
	kindPtr->typePtr.String = newStringType(strlen);

	return newStringSym;
}


/*
 * Determines if the given symbol is a const which appears in the given
 * symbol of kind TYPE_KIND and type SCALAR_T
 * Why checking by name and lexical level is enough: each identifier
 * only appears once per scope.  If def hidden later, lvl is enough
 * to tell us that the id no longer refers to a const inside the
 * scalar list.
 */
int
isConstInScalar(Symbol *constSym, Symbol *scalarSym)
{
	struct ElementArray *consts = NULL;
	Symbol *c = NULL;
	int i;
	if (!(constSym) || !(scalarSym)) return 0;
	if ((getType(constSym) != INTEGER_T) ||
	    (getType(scalarSym) != SCALAR_T) ||
	    (constSym->kind != CONST_KIND) ||
	    (scalarSym->kind != TYPE_KIND)) {
		return 0;
	} 

	if (!constSym->name) return 0;

	consts = getTypePtr(scalarSym)->Scalar->consts;

	for(i = 0; i < consts->nElements; i++) {
		c = (Symbol *) getElementAt(consts, i);
		if ((strcmp(c->name, constSym->name) == 0) &&
		    (c->lvl == constSym->lvl)) {
			return 1;	
		}
	}	
	return 0;
}

/*
 * Sets the given Symbol's offset as  appropriate and increments the offset
 * value in the symbol table for the current lexical level.
 * Parameter:
 * 		s: the symbol whose offset value is to be set
 *		table : the symbol table in which s appears
 */
void setSymbolOffset(Symbol *s, struct hash *table)
{
	if (!s) return;
	s->offset = getOffset(table);
	addToOffset(table, s->size);
}

/*
 * Sets the offset of the given Symbol which is of kind VAR_KIND derived from 
 * a Symbol of PARAM_KIND. 
 * Parameters:
 *		s: the symbol whose offset value is to be calculated
 * 		params: the array of parameters for the proc/func to which
 *		    s belongs
 */

void setParamOffset(Symbol *s, struct ElementArray *params)
{
	Symbol *param = NULL;
	int offset = 0, i;

	/*
	 * Strategy: calculate offset of var by the formula
	 *	offset = -(sum of sizes of variables appearing before s
	 *		    in the parameter array) + -(size of s) - 2
	 * 	where size of s = 1 if s is passed by reference
 	 */
	for (i = 0; i < params->nElements; i++) {
		
		param = getElementAt(params, i);
		if (isByReference(param)) offset += 1;
		else offset += param->size;
		
		if (strcmp(param->name, s->name) == 0) {
			/* We found s in the parameter array */
			break;	
		}
	}
	offset += 2;	/* add 2 for saved value of old pc and old dipslay reg*/

	offset *= -1; 	/* make it negative since parameters saved below 
			 * display register in the call frame */
	s->offset = offset;		
}
