#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "Definitions.h"
#include "ElementArray.h"
#include "Error.h"
#include "Globals.h"
#include "Hash.h"
#include "PreDef.h"
#include "Type.h"
#include "SymbolAll.h"
#include "Utils.h"
#include "ActionsAll.h"

#ifndef TESTBUILD
#include "parser.tab.h"	/* token definitions used in operator compat checks */
#endif
#ifdef TESTBUILD
#include "tokens.h"
#endif

/*For error reporting:*/
extern int yylineno;
extern int colno;
static char *errMsg;


/*
 * Do a lookup in the symbol table for the type with the given id.
 *
 * Raise an error if the type is not available.
 *
 * Return a pointer to the type.
 */
Symbol *simpleTypeLookup(char *id) {
	Symbol *s = getGlobalSymbol(symbolTable, id);
	if (!s) {
		errMsg = customErrorString("The identifier %s has not been "
		  "defined.", id);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}

	if (s->kind != TYPE_KIND) {
		errMsg = customErrorString("The identifier %s is not a type. ",
		    s->name);
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return getTypeSym(s);
	}
	/* Else, we return the given type */
	return s;
}


/*
 * Add new_id as a mamber to sclalar_list.
 *
 * Return scalar_list
 */
struct ElementArray *appendToScalarListType(struct ElementArray *ea,
    char *id) {
	Symbol *s = NULL;
	if (!ea) return NULL;
	
	s = getLocalSymbol(symbolTable, id);
	if (s) {
		alreadyDefinedError(id);
		return NULL;
	}
	s = (Symbol *) newConstProxySym(id, &ea->nElements, 
	    getPreDefInt(preDefTypeSymbols));
	s->lvl = getCurrentLexLevel(symbolTable);
	addToSymbolTable(symbolTable, s);
	appendElement(ea, s);
	return ea;
}


/*
 * Create a new list of scalars (later used in constructing a scalar list type).
 * The list will contain a single constant named by the given id
 *
 * Parameters:
 * 	id: the name of the scalar to add to the new list
 *
 * Return:
 * 	A pointer to an ElementArray struct representing the list of scalars.
 *		The given id will be the only member.
 *	NULL if id is already defined in scope.
 */
struct ElementArray * createScalarList(char *id) {
	Symbol *s = NULL;	
	struct ElementArray *ea = NULL;
	/* first constant in list always has value 0 */
	int value = 0;

	if (id == NULL) {
		err(EXIT_FAILURE, "Passed NULL id into createScalarList");
	}

	s = getLocalSymbol(symbolTable, id);
	if (s != NULL) {
		alreadyDefinedError(id);
		return NULL;
	}

	s = (Symbol *) newConstProxySym(
	    id, &value, getPreDefInt(preDefTypeSymbols));

	if (addToSymbolTable(symbolTable, s) != 0) {
		symbolTableInsertFailure();
	}
	
	ea = newElementArray();
	appendElement(ea, s);
	
	return ea;
}


/*
 * Create a new scalar list type with ea as the scalars in the list
 *
 * Parameters:
 * 	ea: an ElementArray of the scalars that should be in the list
 * Return:
 * 	a pointer to the new scalar list or NULL if ea is NULL
 */
Symbol *createScalarListType(struct ElementArray *ea) {
	Symbol *s = NULL;

	if (!ea) return NULL;

	s = newAnonScalarListTypeSym(ea);
	if (s == NULL) {
		err(EXIT_FAILURE, "Failed to create scalar list symbol.");
	}
	
	if (addToSymbolTable(symbolTable, s) != 0) {
		symbolTableInsertFailure();
	}

	/* Each element in the scalar list will be a local var with
	 * appropriate offset */
	setSymbolOffset(s, symbolTable);

	return s;
}


/*
 * Create a new array type given the index type and base type.
 *
 * Parameters:
 * 	index: symbol for index type of kind TYPE_KIND
 * 	base: symbol for base type of kind TYPE_KIND
 *
 * Return:
 * 	new symbol of kind TYPE_KIND
 * 	
 */
Symbol *createArrayType(Symbol *index, Symbol *base) {
	Symbol * newArraySym = NULL;
	
	newArraySym = newAnonArraySym(base, index);

	if (newArraySym == NULL) {
		/* newAnonArraySym has already done error reporting. */
		return NULL;
	}
	if (addToSymbolTable(symbolTable, newArraySym) != 0) {
		symbolTableInsertFailure();
	}

	return newArraySym;
}


/*
 * Check that the given type is a valid array index type.
 *
 * Raise an error if the type is not valid as an index type.
 *
 * Return the given type.
 */
Symbol *assertArrIndexType(Symbol *index_type) {
	type_t sym_t;

	if (!index_type) return NULL;
	if (index_type->kind != TYPE_KIND) return NULL;

	sym_t = getType(index_type);
	if ( (sym_t != SUBRANGE_T) && (sym_t != SCALAR_T) ) {
		errMsg = customErrorString("Invalid array index type %s. "
		    " Must be of type SUBRANGE or of type SCALAR", 
		    typeToString(sym_t));
		recordError(errMsg, yylineno, colno, SEMANTIC);
		return NULL;
	}
	return index_type;
}


/*
 * Create a new subrange type. The arguments are proxy symbols that should
 * constain constant values for the range bounds.
 *
 * Return a pointer to the new subrange type.
 */
Symbol *createRangeType(ProxySymbol *lower, ProxySymbol *upper) {
	Symbol *s = NULL;
	if (!(lower) || !(upper)) return NULL;
	s = newSubrangeSym((Symbol *) lower, (Symbol *) upper);
	return s;
}


/*
 * Create a new record type from the array of fields.
 *
 * Return a pointer to the new record type symbol.
 */
Symbol *createRecordType(struct ElementArray *fields) {
	Symbol *recType = NULL;
	Symbol *newField = NULL;
	int recordLexLvl = -1;
	ProxySymbol *f = NULL;
	struct hash *recHash = NULL;
	char *fieldId;

	recType = newRecordTypeSym(NULL);
	recHash = recType->kindPtr.TypeKind->typePtr.Record->hash;

	recordLexLvl = getCurrentLexLevel(recHash);

	for (int i = 0; i < fields->nElements; i++) {
		f = getElementAt(fields, i);
		if (!f) continue;
		fieldId = f->name;

		if (!fieldId) {
			freeProxySymbol(f);
			continue;
		}

		newField = newVariableSym(fieldId, getTypeSym(f));
		newField->lvl = recordLexLvl;

		if (getLocalSymbol(recHash, fieldId) != NULL) {
			errMsg = customErrorString(
			    "Record field with name %s already defined.",
			    fieldId); 
			recordError(errMsg, yylineno, colno, SEMANTIC);
			freeProxySymbol(f);
			continue;
		}
		
		if (addToSymbolTable(recHash, newField) != 0) {
			setRecordFieldOffset(newField, recHash, symbolTable);
			freeProxySymbol(f);
			continue;
		}
		/* Give record field appropriate offset in record symbol table*/
		setSymbolOffset(newField, recHash);
	}

	return recType;
}


/*
 * Create a new element array from the given proxy symbol.
 *
 * Return a pointer to the new array.
 */
struct ElementArray *createRecordMemberList(ProxySymbol *field) {
	struct ElementArray *ea = NULL;

	ea = newElementArray();
	growElementArray(ea);
	if (field) {
		appendElement(ea, field);
	}
	return ea;
}


/*
 * Append the given proxySymbol to the array of fields.
 *
 * Return a pointer to the array.
 */
struct ElementArray *appendToRecordMemberList(
    struct ElementArray *array, ProxySymbol *field) {
	if (!array) return NULL;
	if (field)  {
		appendElement(array, field);
	}
	return array;
}


/*
 * Create a new ProxySymbol with the given id and type.
 *
 * Return a pointer to the new proxy.
 */
ProxySymbol *newRecordFieldProxy(char *id, Symbol *type) {
	ProxySymbol *newField = NULL;

	if (!id) return NULL;
	if (!type) return NULL;

	/* 
	 * this sets lex level to global symbolTable level, but that's
	 * fine since this is a proxySymbol and the correct lex level
	 * for the record field is set in createRecordType
	 */
	newField = newVariableSym(id, type);

	return newField;
}
