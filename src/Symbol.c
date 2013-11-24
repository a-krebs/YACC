#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ElementArray.h"
#include "Error.h"
#include "ErrorLL.h"
#include "Type.h"
#include "Symbol.h"
#include "Hash.h"
#include "PreDef.h"

extern int yylineno;
extern int colno;


static char *errMsg;
struct Error *e;

/*
 * Constructs a	named type symbol given a ptr to another type symbol.
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
Symbol *newTypeSymFromSym(char *id, Symbol *typeSym)
{
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

Symbol *
newAnonScalarSym(int lvl, struct ElementArray *ea)
{
	Symbol *newAnonScalar = NULL;
	newAnonScalar = calloc(1, sizeof(Symbol));

	newAnonScalar->name = NULL;
	newAnonScalar->kind = TYPE_KIND;
	allocateKindPtr(newAnonScalar);

	newAnonScalar->kindPtr.TypeKind->type = SCALAR_T;
	getTypePtr(newAnonScalar)->Scalar = calloc(1, sizeof(struct Scalar));	

	getTypePtr(newAnonScalar)->Scalar->consts = ea;
	newAnonScalar->typeOriginator = 1;
	newAnonScalar->lvl = lvl;
	return newAnonScalar;
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
newParamSym(int lvl, char *id, Symbol *typeSym)
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
 * Constructs a new procedure symbol.
 */
Symbol *
newProcSym(int lvl, char *id, struct ElementArray *ea)
{
	Symbol *s = NULL;
	/* Error checking */
	
	s = calloc(1, sizeof(Symbol));
	setSymbolName(s, id);
	s->kind = PROC_KIND;
	allocateKindPtr(s);
	s->kindPtr.ProcKind->params = ea;
	s->lvl = lvl;
	s->typeOriginator = 0;
	return s;	
}

/*
 * Constructs a new function symbol.
 */
Symbol *
newFuncSym(int lvl, char *id, Symbol *typeSym, struct ElementArray *ea)
{
	Symbol *s = NULL;

	s = calloc(1, sizeof(Symbol));
	setSymbolName(s, id);
	s->kind = FUNC_KIND;
	allocateKindPtr(s);
	s->kindPtr.FuncKind->params = ea;
	s->kindPtr.FuncKind->typeSym = typeSym;
	return s;
}

/*
 * Constructs an anonymous subrange symbol.
 */
Symbol *
newSubrangeSym(ProxySymbol *constSymLow, ProxySymbol *constSymHigh)
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
		break;
	}

	newSubrangeSym = createTypeSymbol(NULL, 1);
	newSubrangeSym->kindPtr.TypeKind->type = SUBRANGE_T;
	newSubrangeSym->kindPtr.TypeKind->typePtr.Subrange = newSubrange(
								  constSymLow,
								  constSymHigh);
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
		/* Procedures do not have associated type symbols */
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

Symbol *
paramToVar(int lvl, Symbol * param)
{
	if (!param) return NULL;
	if (param->kind != PARAM_KIND) return NULL;
	Symbol *typeSym = getTypeSym(param);
	return newVariableSym(lvl, param->name, typeSym);
}
 

ProxySymbol *
newProxySymFromSym(Symbol *s)
{
	ProxySymbol *ps = NULL;
	if (!s) return NULL;

	ps = calloc(1, sizeof(ProxySymbol));
	if (s->name) {
		setSymbolName((Symbol *)ps, s->name);
	}

	ps->kind = s->kind;
	ps->kindPtr = s->kindPtr;
	ps->typeOriginator = 0;
	ps->lvl = s->lvl;
	return ps;
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
	char *charResult;
	
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
	case CHAR_T:
		charResult = (char *) result;
		getConstVal(constSym)->Char.value = *charResult;
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

// ProxySymbol *
// newStringProxySym(int lvl, char *str, int strlen)
// {
// 	ProxySymbol *newStringSym = NULL;
// 	AnonConstVal anonStr;

// 	newStringSym = calloc(1, sizeof (ProxySymbol));
// 	anonStr.String.str = str;
// 	anonStr.String.strlen = strlen;

// 	newStringSym->name = NULL;
// 	newStringSym->kind = TYPE_KIND;
// 	allocateKindPtr(newStringSym);
// 	newStringSym->kindPtr.TypeKind->type = STRING_T;
// 	newStringSym->kindPtr.TypeKind->typePtr = newAnonConstType(
// 	    anonStr, STRING_T);
// 	getTypePtr(newStringSym)->String->strlen = strlen;
	
// 	if (strlen) {
// 		getTypePtr(newStringSym)->String->str = 
// 		    calloc(1, sizeof(char)*strlen);
// 		if (!getTypePtr(newStringSym)->String->str) {
// 			err(1, "Failed to allocate memory for new string");
// 			exit(1);
// 		}
// 	}
// 	newStringSym->lvl = lvl;
// 	newStringSym->typeOriginator = 1;
// 	return newStringSym;	
// }

Symbol *
newStringTypeSym(int lexLevel, int strlen) {
	Symbol *newStringSym = newStringSym = calloc(1, sizeof (Symbol));

	newStringSym = calloc(1, sizeof (ProxySymbol));
	newStringSym->kind = TYPE_KIND;
	allocateKindPtr(newStringSym);
	newStringSym->name = NULL;
	newStringSym->lvl = lexLevel;
	newStringSym->kindPtr.TypeKind->type = STRING_T;
	newStringSym->kindPtr.TypeKind->typePtr.String = calloc(1, sizeof(struct String));
	getTypePtr(newStringSym)->String->strlen = strlen;
	return newStringSym;

}

ProxySymbol *
newStringProxySym(int lvl, char *str, int strlen)
{
	ProxySymbol *newStringSym = NULL;

	newStringSym = calloc(1, sizeof (ProxySymbol));

	newStringSym->name = NULL;
	newStringSym->kind = CONST_KIND;
	allocateKindPtr(newStringSym);

	newStringSym->kindPtr.ConstKind->value.String.str = calloc(1, (sizeof(char)* strlen));
	strncpy(newStringSym->kindPtr.ConstKind->value.String.str, str, strlen);
	newStringSym->kindPtr.ConstKind->value.String.strlen = strlen;

	newStringSym->kindPtr.ConstKind->typeSym = calloc(1, sizeof (struct ConstantKind));
	newStringSym->kindPtr.ConstKind->typeSym = getPreDefString(preDefTypeSymbols);

	return newStringSym;	
}


void
setSymbolName(Symbol *s, char *id)
{
	size_t len;
	if (id == NULL) {
		s->name = NULL;
		return;
	}
	
	len = strlen(id) + 1;
	s->name = calloc(1, sizeof(char)*len);
	if (!s->name) {
		err(1, "Failed to allocate memory for symbol name!");
		exit(EXIT_FAILURE);
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
	int nameLen = 0;

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
	
	nameLen = strlen(field->name);
	id = calloc(nameLen + 1, sizeof(char));
	id = strncpy(id, field->name, nameLen);

	newField = newVariableSym(
	    recordLvl, id, field->kindPtr.VarKind->typeSym);

	if (createHashElement(recordHash, id, newField) != 0) {
		return -2;
	}

	return 0;
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
 * Return 1 if valid invocation, 0 otherwise.
 */
int isValidProcInvocation(Symbol *s, struct ElementArray *ea)
{
	struct ElementArray *params = NULL;
	Symbol *passedParam, *expectedParam = NULL;
	int i;

	// make sure we're given a proc and not a func
	if (s->kind != PROC_KIND) {
		errMsg = customErrorString("Identifier %s cannot be called "
		    "as a procedure.", s->name);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}

	params = s->kindPtr.ProcKind->params;
	if (!params) {
		// special built-in proc that takes unlimited args
		// TODO for now just assuming all arguments are valid
		return 1;
	} else if (params->nElements != ea->nElements) {
		errMsg = customErrorString("Procedure %s expects %d "
		    "parameters, got %d", s->name, params->nElements,
		    ea->nElements);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;	
	}


	for (i = 0; (i < params->nElements) && (i < ea->nElements); i++) {
		passedParam = (Symbol *) getElementAt(ea, i);
		expectedParam = (Symbol *) getElementAt(params, i);
		if (!areSameType(passedParam, getTypeSym(expectedParam))) {
			errMsg = customErrorString("Procedure %s expects "
			    "argument of type %s at index %d, but got "
			    "argument of type %s", s->name, i,
			    typeToString(getType(expectedParam)),
			    typeToString(getType(passedParam)));
			e = recordError(errMsg, yylineno, colno,
			     SEMANTIC);
			printError(e);
			return 0;
		}
	}
	return 1;
}

Symbol *
isValidFuncInvocation(Symbol *s, struct ElementArray *ea)
{
	struct ElementArray *params = NULL;
	Symbol *passedParam, *expectedParam = NULL;
	int i;

	// make sure we're given a func and not a proc
	if (s->kind != FUNC_KIND) {
		errMsg = customErrorString("Identifier %s cannot be " 			"called as a function.", s->name);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}

	params = s->kindPtr.FuncKind->params;
	if (!params) {
		// special case of predefined-function
		// TODO check what types are acceptable,
		// for now assuming all types
		return getTypeSym(s);
	} else if (params->nElements != ea->nElements) {
		errMsg = customErrorString("Procedure %s expects %d "
		    "parameters, got %d", s->name, params->nElements,
		    ea->nElements);
		e = recordError(errMsg, yylineno, colno, SEMANTIC);
		printError(e);	
		return NULL;	
	}


	for (i = 0; i < params->nElements; i++) {
		passedParam = (Symbol *) getElementAt(ea, i);
		expectedParam = (Symbol *) getElementAt(params, i);
		if (!areSameType(passedParam, getTypeSym(expectedParam))) {
			errMsg = customErrorString("Procedure %s expects "
			    "argument of type %s at index %d, but got "
			    "argument of type %s", s->name, i,
			    typeToString(getType(expectedParam)),
			    typeToString(getType(passedParam)));
			e = recordError(errMsg, yylineno, colno, SEMANTIC);
			printError(e);
			return NULL;
		}
	}
	return getTypeSym(s);
}

/*
 * Given a linked list of ProxySymbols, returns the type which results
 * from using the linked list of ProxySymbols to access the array given
 * by var.
 * TODO: if index is const not part of scalar, see if its value falls in the
 * allowable range.
 *
 */
Symbol *
isValidArrayAccess(ProxySymbol *var, ProxySymbol *indices)
{
	Symbol *arrayTypeSym = NULL;
	Symbol *indexTypeSym = NULL;
	Symbol *arg = indices;
	int typeErr = 0;

	if (!var) {
		return NULL;
	}
	arrayTypeSym = getTypeSym(var);

	if (getType(arrayTypeSym) != ARRAY_T) {
		return arrayTypeSym;
	}
//	arrayDim = getArrayDim(arrayTypeSym);
//	nArgs = getSymbolListLength(indices);

//	if (arrayDim != nArgs) {
//		errMsg = customErrorString("Trying to access array %s of "
//		    "dimension %d with %d index/indices.", var->name,
//		    arrayDim, nArgs);
//		recordError(errMsg, yylineno, colno, SEMANTIC);
//		return NULL;
//	}

	indexTypeSym = getArrayIndexSym(arrayTypeSym);
	while ( (arg) && (getType(arrayTypeSym) == ARRAY_T)) {
		switch (getType(indexTypeSym)) {
		case SCALAR_T:
			if (!isConstInScalar(arg, indexTypeSym))
			    typeErr = 1;
			break;
		case SUBRANGE_T:
			if (!areSameType(
			    getSubrangeBaseTypeSym(indexTypeSym),
			    getTypeSym(arg))) typeErr = 1;
			break;
		default:
			if (!areSameType(indexTypeSym,
			     getTypeSym(arg))) typeErr = 1;
			break;	
		}
		if (typeErr) {
			errMsg = customErrorString("Invalid array "
			    "subscript.  Expected type %d "
			    "%d but got %s",
		    	    typeToString(getType(indexTypeSym)),
		    	    typeToString(getType(arg)));
			recordError(errMsg, yylineno, colno, SEMANTIC);
		}
		typeErr = 0;
		arrayTypeSym = getArrayBaseSym(arrayTypeSym);
		indexTypeSym = getArrayIndexSym(arrayTypeSym);
		arg = arg->next;
	}

	/* Else are ready to return the base type */

	if (arg) {
		/* Didn't exhaust args, but exhausted arrays.
		 * Return arrayTypeSym */
		recordError("Illegal array access -- too many indices.",
		    yylineno, colno, SEMANTIC);
		return arrayTypeSym;
	} 
	return arrayTypeSym;
}



/*
 * Returns a pointer to the type symbol defining the base type for the given
 * subrange symbol.
 */
Symbol *
getSubrangeBaseTypeSym(Symbol *sr) {
	if (!sr) return NULL;
	if (getType(sr) != SUBRANGE_T) return NULL;
	return getTypePtr(sr)->Subrange->baseTypeSym;

}
/*
 * Follows the chains of next pointer to get the size of the Symbol linked
 * list.
 */
int
getSymbolListLength(Symbol *s)
{	
	int len = 0;
	while (s) {
		len++;
		s = s->next;
	}
	return len;
}

/*
 * Returns the dimension of the given array (assumes that the given
 * Symbol describing the array is the "first dimensional array")
 */
int
getArrayDim(Symbol *s)
{
	Symbol *nextIndexSym = NULL;
	int dim = 0;	
	nextIndexSym = getArrayIndexSym(s);
	while (nextIndexSym != NULL) {
		dim++;
		nextIndexSym = getArrayIndexSym(nextIndexSym);
	}
	return dim;
}

/*
 * Returns the symbol which indexes the array.
 */
Symbol *
getArrayIndexSym(Symbol *s)
{
	if (!s) return NULL;
	if (getType(s) != ARRAY_T) return NULL;
	return getTypePtr(s)->Array->indexTypeSym;
}

Symbol *
getArrayTerminalTypeSym(Symbol *s)
{
	Symbol *baseSym = NULL;
	if (!s) return NULL;
	if (getType(s) != ARRAY_T) return NULL;
	baseSym = getTypePtr(s)->Array->baseTypeSym;
	while (getType(baseSym) == ARRAY_T) {
		baseSym = getTypePtr(baseSym)->Array->baseTypeSym;
	}
	return baseSym;

}

Symbol *
getArrayBaseSym(Symbol *s)
{
	if (!s) return NULL;
	if (getType(s) != ARRAY_T) return NULL;
	return getTypePtr(s)->Array->baseTypeSym;

}

/* Checks each memeber of the passed ElementArray to see if each
 * memeber is of simple type.
 *
 * Parameters:
 *              elementArray: elementArray passed
 *
 * Return: Boolean: 1 if elemetn array is simple
 *		    0 if not
 */
int isElementArraySimple(struct ElementArray *elementArray) {
	struct Symbol *symbol;
	type_t symbolsType;

	for (int i = 0; i < elementArray->nElements; ++i) {
		symbol = (struct Symbol *) getElementAt(elementArray, i);

		if ( symbol->kind != TYPE_KIND ) {
			return 0;
		}

		symbolsType = getType(symbol);

		if ( symbolsType != BOOLEAN_T
			&& symbolsType != CHAR_T
			&& symbolsType != INTEGER_T
			&& symbolsType != REAL_T
			&& symbolsType != STRING_T ) {
			return 0;
		}
	}

	return 1;
}

int
isIOProc(Symbol *s) {
	if (!s) return 0;
	if (s->kind != PROC_KIND) return 0;

	if (  (	(strcmp(s->name, "read") == 0)	 	||
	    	(strcmp(s->name, "readln") == 0) 	||
	    	(strcmp(s->name, "write") == 0) 	||
	    	(strcmp(s->name, "writeln") == 0) )	&&
		(s->lvl == 0) ) {
		return 1;
	}
	return 0;

}

int isPreDefFunc(Symbol *s) {
	char *name = NULL;

	if (!s) return 0;
	if (s->kind != FUNC_KIND) return 0;

	name = s->name;

	if ( (	(strcmp(name, "abs") == 0) ||
		(strcmp(name, "sqr") == 0) ||
		(strcmp(name, "sin") == 0) ||
		(strcmp(name, "cos") == 0) ||
		(strcmp(name, "exp") == 0) ||
		(strcmp(name, "ln") == 0) ||
		(strcmp(name, "sqrt") == 0) ||
		(strcmp(name, "arctan") == 0) ||
		(strcmp(name, "trunc") == 0) ||
		(strcmp(name, "round") == 0) ||
		(strcmp(name, "chr") == 0) ||
		(strcmp(name, "odd") == 0) ||
		(strcmp(name, "ord") == 0) ||
		(strcmp(name, "succ") == 0) ||
		(strcmp(name, "pred") == 0) ) &&
			s->lvl == 0) {
	   	return 1;
	}
	return 0;
}

int
isValidIOProcInvocation(Symbol *s, struct ElementArray *ea)
{
	Symbol *param = NULL;
	type_t type;
	int i, nArgs, valid = 1;

	nArgs = ea->nElements;

	if (!nArgs) {
		errMsg = customErrorString("Procedure %s cannot be "
		    "called without any arguments.", s->name);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}

	for (i = 0; i < nArgs; i++) {
		param = getElementAt(ea, i);
		type = getType(param);
		if ( (type != CHAR_T) && (type != INTEGER_T) &&
		    (type != REAL_T) && (type != STRING_T) ) {
			errMsg = customErrorString("Invalid argument "
			    "of type %s passed to procedure %s.",
			    typeToString(type), s->name);
			recordError(errMsg, yylineno, colno, SEMANTIC);
			valid = 0;
		}
	}
	if (!valid) return 0;
	return 1;
}

ProxySymbol *isValidPreDefFuncInvocation(Symbol *s, struct ElementArray *ea)
{
	Symbol *param = NULL;
	type_t type;
	int i = 0;
	int nArgs = 0;

	nArgs = ea->nElements;

	// check argument count
	if (nArgs != 1) {
		errMsg = customErrorString("Function %s expected "
		    "1 argument but %d given.", s->name, nArgs);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}
	
	param = getElementAt(ea, i);
	type = getType(param);
	
	if (typeIsInValidArgs(s, type)) {
		return getPreDefFuncReturnType(s, type);
			
	} else {
		errMsg = customErrorString("Function %s cannot be "
		    "called with argument of type %s.", s->name,
		    typeToString(type));
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return 0;
	}
}

int typeIsInValidArgs(Symbol *s, type_t type) {
	char *name = NULL;
	if (!s) return 0;
	name = s->name;

	if (
	    (strcmp(name, "abs") == 0) ||
	    (strcmp(name, "sqr") == 0) ||
	    (strcmp(name, "sin") == 0) ||
	    (strcmp(name, "cos") == 0) ||
	    (strcmp(name, "exp") == 0) ||
	    (strcmp(name, "ln") == 0) ||
	    (strcmp(name, "sqrt") == 0) ||
	    (strcmp(name, "arctan") == 0)
	) {
		if ((type == INTEGER_T) || (type == REAL_T)) {
			return 1;
		}
	} else if (
	    (strcmp(name, "trunc") == 0) ||
	    (strcmp(name, "round") == 0)
	){
		if (type == REAL_T) return 1;
	} else if (
	    (strcmp(name, "chr") == 0) ||
	    (strcmp(name, "odd") == 0)
	){
		if (type == INTEGER_T) return 1;
	} else if (
	    (strcmp(name, "ord") == 0) ||
	    (strcmp(name, "succ") == 0) ||
	    (strcmp(name, "pred") == 0)
	){
		if (isOrdinal(type)) return 1;
	}
	return 0;
}

Symbol *getPreDefFuncReturnType(Symbol *s, type_t argType) {
	char *name = NULL;
	
	if (!s) return NULL;

	name = s->name;

	if (
	    (strcmp(name, "abs") == 0) ||
	    (strcmp(name, "sqr") == 0) ||
	    (strcmp(name, "succ") == 0) ||
	    (strcmp(name, "pred") == 0)
	) {
		return getTypeSym(s);
	} else if (
	    (strcmp(name, "sin") == 0) ||
	    (strcmp(name, "cos") == 0) ||
	    (strcmp(name, "exp") == 0) ||
	    (strcmp(name, "ln") == 0) ||
	    (strcmp(name, "sqrt") == 0) ||
	    (strcmp(name, "arctan") == 0)
	) {
		return getPreDefReal(preDefTypeSymbols);
	} else if (
	    (strcmp(name, "trunc") == 0) ||
	    (strcmp(name, "round") == 0) ||
	    (strcmp(name, "ord") == 0)
	){
		return getPreDefInt(preDefTypeSymbols);
	} else if (
	    (strcmp(name, "chr") == 0)
	){
		return getPreDefChar(preDefTypeSymbols);
	} else if (
	    (strcmp(name, "odd") == 0)
	){
		return getPreDefBool(preDefTypeSymbols);
	}
	return NULL;
}

void freeProxySymbol(ProxySymbol *p) {
	free(p);
}


/* Creates a new symbol. Auto-determines all substructures
 * based on the parameter kind.
 *
 * Does not insert into the symbol table, use createAndInsertSymbol for that.
 *
 * Parameters:
 * 		table: the symbol table from which to get lexical level
 *              id: name of symbol
 *		kind: kind of symbol. Comes from kind_t enum
 *		typeOriginator: flag for if type originator 
 *
 * Return: Newly created symbol.
 */
Symbol *createSymbol(
    struct hash *table, char *id, kind_t kind, int typeOriginator)
{
	Symbol *symbol = allocateSymbol();

	if (symbol == NULL) {
		err(1, "Could not create new symbol.");
		exit(EXIT_FAILURE);			
	}

	// set symbol independent values
	setSymbolName(symbol, id);

	symbol->kind = kind;
	allocateKindPtr(symbol);
	
	symbol->lvl = getCurrentLexLevel(table);
	symbol->typeOriginator = typeOriginator;
	symbol->next = NULL;

	return symbol;
}


/* Allocates memeory for a struct symbol and only a struct symbol.
 *
 * Parameters:
 *
 * Return: Pointer to newly allocated memory chunk
 */
Symbol *allocateSymbol() {
	Symbol *symbol = NULL;

	symbol = calloc(1, sizeof(Symbol));
	if ( symbol == NULL ) {
		err(1, "Could not alloc memory for symbol.");
		exit(EXIT_FAILURE);		
	}

	return symbol;
}


/* Creates and inserts a symbol into the symbol table
 *
 * Parameters:
 * 		table: the symbol table into which to insert
 *              id: name of symbol
 *		kind: kind of symbol. Comes from kind_t enum
 *		typeOriginator: flag for if type originator 
 *
 * Return: a pointer to the created symbol
 */
Symbol *createAndInsertSymbol(
    struct hash *table, char *key, kind_t kind, int typeOriginator)
{
	Symbol *symbol = createSymbol(table, key, kind, typeOriginator);

	if (symbol == NULL) {
		err(1, "Could not create symbol.");
		exit(EXIT_FAILURE);
	}

	if (createHashElement(table, key, symbol) != 0) {
		err(1, "Could not insert into symbol table.");
		exit(EXIT_FAILURE);
	}

	return symbol;
}


/////////////////////////////////////////////////////////////////////////////
/*
 *			SYMBOL CREATION - BASED ON KIND
 */
/////////////////////////////////////////////////////////////////////////////


/* Creates const kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createConstSymbol(char *id) {
	return createSymbol(symbolTable, id, CONST_KIND, TYPEORIGINATOR_NO);
}


/* Creates func kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createFuncSymbol(char *id) {
	return createSymbol(symbolTable, id, FUNC_KIND, TYPEORIGINATOR_NO);
}


/* Creates Param kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createParamSymbol(char *id) {
	return createSymbol(symbolTable, id, PARAM_KIND, TYPEORIGINATOR_NO);
}


/* Creates proc kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createProcSymbol(char *id) {
	return createSymbol(symbolTable, id, PROC_KIND, TYPEORIGINATOR_NO);
}


/* Creates var kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *
 * Return: Newly created symbol
 */
Symbol *createVarSymbol(char *id) {
	return createSymbol(symbolTable, id, VAR_KIND, TYPEORIGINATOR_NO);
}


/* Creates type kind symbol using scope of global symbol table.
 *
 * Parameters:
 *              id: name of symbol
 *		typeOriginator: flag for if type originator 
 *
 * Return: Newly created symbol
 */
Symbol *createTypeSymbol(char *id, int typeOriginator) {
	return createSymbol(symbolTable, id, TYPE_KIND, typeOriginator);
}


/////////////////////////////////////////////////////////////////////////////
/*
 *			SYMBOL CREATION - BASED ON TYPE
 */
/////////////////////////////////////////////////////////////////////////////


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

