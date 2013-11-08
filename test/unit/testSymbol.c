/*
 * Cmput 415 - Team YACC
 * Unit tests for the Symbol module.
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ElementArray.h"
#include "testSymbol.h"
#include "Type.h"
#include "Symbol.h"

#define INTLOW_VAL 12
#define INTHIGH_VAL 23423

int yylineno;
int colno;

double REAL_VAL = 123.321;


Symbol *
setUpTypeSymbolForSimple(char *name, type_t type, int lexLevel)
{
	struct Symbol *symbol = calloc(1, sizeof(struct Symbol));
	if ( symbol == NULL ) {
		err(1, "Failed to allocate memory for test type symbol!");
		exit(EXIT_FAILURE);		
	}

	setSymbolName(symbol, name);
	symbol->kind = TYPE_KIND;

	allocateKindPtr(symbol);
	symbol->kindPtr.TypeKind->type = type;


	if ( type == BOOLEAN_T ) {
		getTypePtr(symbol)->Boolean = malloc(sizeof(struct Boolean));
	}
	else if ( type == CHAR_T ) {
		getTypePtr(symbol)->Char = malloc(sizeof(struct Char));
	}
	else if ( type == INTEGER_T ) {
		getTypePtr(symbol)->Integer = malloc(sizeof(struct Integer));
	}
	else if ( type == REAL_T ) {
		getTypePtr(symbol)->Real = malloc(sizeof(struct Real));
	}
	else if ( type == STRING_T ) {
		getTypePtr(symbol)->String = malloc(sizeof(struct String));
	}	
	else {
		err(2, "Could not determine type asked in setUpTypeSymbolForSimple");
		exit(EXIT_FAILURE);
	}

	symbol->lvl = lexLevel;
	symbol->typeOriginator = 1;
	symbol->next = NULL;

	return symbol; 	
}

Symbol *
setUpTypeSymbol()
{
	char id[] = "testType";
	Symbol *typeSym = calloc(1, sizeof(Symbol));
	size_t len = strlen(id);
	if (!typeSym) {
		err(1, "Failed to allocate memory for test type symbol!");
		exit(1);
	}

	typeSym->name = calloc(1, (sizeof(char))*len);
	if (!typeSym->name) {
		err(1, "Failed to allocate memory for test type symbol name!");
		exit(1);
	}
	strcpy(typeSym->name, id);
	typeSym->kind = TYPE_KIND;
	
	allocateKindPtr(typeSym);
	typeSym->kindPtr.TypeKind->typePtr.Integer =
	     calloc(1, sizeof(struct Integer));
	if (!typeSym->kindPtr.TypeKind->typePtr.Integer) {
		err(1, 
		    "Failed to allocate memory for test type symbol typeptr!");
		exit(1);
	}
	
	typeSym->kindPtr.TypeKind->type = INTEGER_T;
	typeSym->kindPtr.TypeKind->typePtr.Integer->value = INTLOW_VAL;
	return typeSym; 	
}




Symbol *
setUpIntConst()
{
	char id[] = "testType";
	Symbol *constSym = calloc(1, sizeof(Symbol));
	if (!constSym) {
		err(1, "Failed to allocate memory for test type symbol!");
		exit(1);
	}

	setSymbolName(constSym, id);
	constSym->kind = CONST_KIND;
	allocateKindPtr(constSym);
	constSym->kindPtr.ConstKind->typeSym = setUpTypeSymbol();
	constSym->kindPtr.ConstKind->value.Integer.value = INTLOW_VAL;
	return constSym; 	
}


Symbol *
setUpConstSymbol()
{
	char id[] = "testType";
	Symbol *constSym = calloc(1, sizeof(Symbol));
	size_t len = strlen(id);
	if (!constSym) {
		err(1, "Failed to allocate memory for test type symbol!");
		exit(1);
	}

	constSym->name = calloc(1, (sizeof(char))*len);
	if (!constSym->name) {
		err(1, "Failed to allocate memory for test type symbol name!");
		exit(1);
	}
	strcpy(constSym->name, id);
	constSym->kind = CONST_KIND;
	
	allocateKindPtr(constSym);
	constSym->kindPtr.ConstKind->typeSym = setUpTypeSymbol();
	constSym->kindPtr.ConstKind->typeSym->kindPtr.TypeKind->type = REAL_T;
	constSym->kindPtr.ConstKind->value.Real.value = REAL_VAL;
	
	return constSym; 	
}

char *
test_newAnonArraySym()
{
	Symbol *newArraySym = NULL;
	Symbol *lowConst = setUpIntConst();
	Symbol *highConst = setUpIntConst();
	Symbol *subrangeSym = newSubrangeSym(10, lowConst, highConst);
	Symbol *baseTypeSym = setUpTypeSymbol();
	newArraySym = newAnonArraySym(10, baseTypeSym, subrangeSym);

	mu_assert("newArraySym should not be NULL", newArraySym); 
	mu_assert("newArraySym should have subrange as expected",
	    getTypePtr(newArraySym)->Array->indexTypeSym == subrangeSym);
	mu_assert("newArraySym should have base type as expecte",
	    getTypePtr(newArraySym)->Array->baseTypeSym == baseTypeSym);
	mu_assert("newArraySym should be at the expected lexical level",
	    newArraySym->lvl == 10);

	return NULL;
}

char *
test_newParamSym()
{
	Symbol *s = NULL;
	Symbol *typeSym = setUpTypeSymbol();
	char id[] = "testParam";
	int lvl = 12;
	
	s = newParamSym(lvl, id, typeSym);
	mu_assert("newParamSYm should not be null", s);
	mu_assert("newParamSym should have type as expected",
	    getTypeSym(s) == typeSym);
	mu_assert("newParamSym should be at expected lexical level",
	   s->lvl == lvl);
	mu_assert("newParamSym should have the name as expected",
	    strcmp(id, s->name) == 0);
	return NULL;

}

char *
test_newConstProxySym()
{
	ProxySymbol *constProxySym = NULL;
	Symbol *typeSym = setUpTypeSymbol();
	int intResult = 123;
	double doubleResult = 123.321;

	typeSym->kindPtr.TypeKind->type = BOOLEAN_T;
	constProxySym = newConstProxySym(&(intResult), typeSym);

	mu_assert("newConstProxySym() should not return NULL ProxySymbol"
	    " when given valid input", constProxySym);

	mu_assert("newConstProxySym() should return boolean const kind Proxy "
	    "Symbol with the expected attributes",
	    (constProxySym->kind == CONST_KIND) &&
	    (getConstVal(constProxySym)->Boolean.value == intResult) &&
	    (getTypeSym(constProxySym) == typeSym));
	

	typeSym->kindPtr.TypeKind->type = REAL_T;
	constProxySym = newConstProxySym(&(doubleResult), typeSym);

	mu_assert("newConstProxySym() should not return NULL ProxySymbol"
	    " when given valid input", constProxySym);

	mu_assert("newConstProxySym() should return real const kind Proxy "
	    "Symbol with the expected attributes",
	    (constProxySym->kind == CONST_KIND) &&
	    (getConstVal(constProxySym)->Real.value == doubleResult) &&
	    (getTypeSym(constProxySym) == typeSym));

	typeSym->kindPtr.TypeKind->type = INTEGER_T;
	constProxySym = newConstProxySym(&(intResult), typeSym);

	mu_assert("newConstProxySym() should not return NULL ProxySymbol"
	    " when given valid input", constProxySym);

	mu_assert("newConstProxySym() should return integer const kind Proxy "
	    "Symbol with the expected attributes",
	    (constProxySym->kind == CONST_KIND) &&
	    (getConstVal(constProxySym)->Integer.value == intResult) &&
	    (getTypeSym(constProxySym) == typeSym));

	return NULL;
}

char *
test_newConstSymFromProxy()
{
	ProxySymbol *proxySym = (ProxySymbol *) setUpConstSymbol();
	Symbol *newConstSym = NULL;
	char id[] = "testSymbol";
	int lvl = 10;

	newConstSym = newConstSymFromProxy(lvl, id, proxySym);
	mu_assert("newConstSymFromProxy() should not return null when passed"
	    " valid input", newConstSym);
	mu_assert("newConstSymFromProxy() should return a new symbol of kind"
	    " CONST_KIND", newConstSym->kind == CONST_KIND);

	free(proxySym->kindPtr.ConstKind);
	mu_assert("newConstSymFromProxy() should have copy of value it got"
	    " from proxysymbol evern after proxy is freed",
	    getConstVal(newConstSym)->Real.value == REAL_VAL);
	return NULL;
}


char *
test_newTypeSymFromSym()
{
	Symbol *typeSym = setUpTypeSymbol();
	Symbol *newTypeSym = NULL;
	int lvl = 10; 
	char id[] = "testArray";	


	newTypeSym = newTypeSymFromSym(lvl, id, typeSym);
	mu_assert("newTypeSym should not be null", newTypeSym);
	mu_assert("newTypeSym should have kindPtr equivalent to kindPtr of test"
	    "type", newTypeSym->kindPtr.TypeKind = typeSym->kindPtr.TypeKind);
	mu_assert("newTypeSym should have expected id",
	    strcmp(id, newTypeSym->name) == 0);
	mu_assert("newTypeSym should be at expected lexical level",
	    newTypeSym->lvl = lvl);
	mu_assert("newTypeSym should NOT be a type originator",
	    newTypeSym->typeOriginator == 0);

	return NULL;
}


char *
test_newVariableSym()
{
	Symbol *typeSym = setUpTypeSymbol();
	Symbol *newVar = NULL;
	Symbol *varTypeSym = NULL;
	char id[] = "testVariable";
	int lvl = 100;

	newVar = newVariableSym(lvl, id, NULL);
	mu_assert("newVariable() should return NULL if NULL typeSym passed",
		!newVar);
	
	newVar = newVariableSym(lvl, NULL, typeSym);
	mu_assert("newVariable() should return NULL if NULL id passed",
		!newVar);

	typeSym->kind = VAR_KIND;
	newVar = newVariableSym(lvl, id, typeSym);
	mu_assert("newVariable() should return NULL if passed VAR_KIND symbol",
		!newVar);

	typeSym->kind = TYPE_KIND;

	newVar = newVariableSym(lvl, id, typeSym);
	varTypeSym = newVar->kindPtr.VarKind->typeSym;
	mu_assert("newVariable() should return symbol of kind VAR_KIND",
		newVar->kind == VAR_KIND);
	mu_assert("newVariable() should return symbol w/name \"testVariable\"",
		strcmp(newVar->name, id) == 0);
	mu_assert("newVariable() should be a variable with type defined by"
		  "the symbol expected",
		(varTypeSym == typeSym));
	return NULL;
}

char *
test_newSubrangeSym() 
{
	Symbol *subrangeSym = NULL;
	Symbol *testSymLow = setUpConstSymbol();
	Symbol *testSymHigh = setUpConstSymbol();
	int lvl = 102;
	getTypeSym(testSymLow)->kindPtr.TypeKind->type = INTEGER_T;
	getTypeSym(testSymHigh)->kindPtr.TypeKind->type = INTEGER_T;
	getConstVal(testSymLow)->Integer.value = INTLOW_VAL;
	getConstVal(testSymHigh)->Integer.value = INTHIGH_VAL;
	
	subrangeSym = newSubrangeSym(lvl, testSymLow, NULL);
	mu_assert("newSubrangeSym() should return NULL if a symbol arg is NULL",
		  !subrangeSym);


	subrangeSym = newSubrangeSym(lvl, testSymHigh, testSymLow);
	mu_assert("newSubRangeSym() should return NULL if low >= high",
		  !subrangeSym);

	subrangeSym = newSubrangeSym(lvl, testSymLow, testSymHigh);
	mu_assert("newSubRangeSym() should return expected subrange",
	    (getTypePtr(subrangeSym)->Subrange->low == INTLOW_VAL));

	getTypeSym(testSymLow)->kindPtr.TypeKind->type = SCALAR_T;
	subrangeSym = newSubrangeSym(lvl, testSymLow, testSymHigh);
	mu_assert("newSubrangeSym() should return null when symbol types \
		   mistmatch.", !subrangeSym);
	return NULL;
}

char *
test_newAnonScalarSym()
{
	Symbol *ss = NULL;
	Symbol *c = setUpIntConst();
	struct ElementArray *ea = newElementArray();
	growElementArray(ea);
	appendElement(ea, c);
	int lvl = 0;

	ss = newAnonScalarSym(lvl, ea);
	mu_assert("newAnonScalar is not NULL when given valid inputs", ss);
	mu_assert("newAnonScalar should have lvl as epxected", ss->lvl == lvl);
	mu_assert("newAnonScalar should have expected symbol in its element "
	    "array", getElementAt(getTypePtr(ss)->Scalar->consts, 0) == c); 
	
	return NULL;
}

char *
test_isConstInScalar()
{
	Symbol *ss = NULL;
	Symbol *c1 = setUpIntConst();
	Symbol *c2 = setUpIntConst();
	Symbol *c3 = setUpIntConst();
	struct ElementArray *ea = newElementArray();
	growElementArray(ea);
	appendElement(ea, c1);
	appendElement(ea, c2);
	int lvl = 0;
	char id[] = "hello";

	ss = newAnonScalarSym(lvl, ea);
	mu_assert("isConstInScalar() should recognize c1 appears in scalar",
	    isConstInScalar(c1, ss));
	c3->lvl = 102;
	mu_assert("isConstInScalar() should recognize c3 does not appear in "
	    "scalar", !isConstInScalar(c3, ss));
	c1->name = id;
	mu_assert("isConstInScalar() should recognize c1 is not in scalar "
	    "even though it appears in element array", 
	    !isConstInScalar(ss, c1));

	
	return NULL;
}

char *
test_isValidArrayAccess()
{
	Symbol *newArraySym = NULL;
	Symbol *lowConst = setUpIntConst();
	Symbol *highConst = setUpIntConst();
	Symbol *subrangeSym = newSubrangeSym(10, lowConst, highConst);
	Symbol *baseTypeSym = setUpTypeSymbol();
	Symbol *var = NULL;
	newArraySym = newAnonArraySym(10, baseTypeSym, subrangeSym);
	var = newVariableSym(10, "hello", newArraySym);	
	ProxySymbol *index1 = (ProxySymbol *) lowConst;
	index1->kindPtr.ConstKind->typeSym =
	    lowConst->kindPtr.ConstKind->typeSym;
	mu_assert("isValidArrayAccess() should recognize valid array access",
	    isValidArrayAccess(newArraySym, lowConst)); 
	mu_assert("isValidArrayAccess() should recognize invalid array access",
	    !isValidArrayAccess(newArraySym, setUpConstSymbol()));

	return NULL;
}


char * 
test_isElementArraySimple() 
{
	struct Symbol *symbol = setUpIntConst();
	struct Symbol *integer = setUpTypeSymbolForSimple("billy", INTEGER_T, 0);
	struct Symbol *real = setUpTypeSymbolForSimple("bob", REAL_T, 0);
	struct Symbol *boolean = setUpTypeSymbolForSimple("bonnie", BOOLEAN_T, 0);
	struct Symbol *string = setUpTypeSymbolForSimple("ben", STRING_T, 0);
	struct Symbol *chars = setUpTypeSymbolForSimple("booo", CHAR_T, 0);

	struct ElementArray *elementArray = newElementArray();
	appendElement(elementArray, integer);

	mu_assert("Unexpected valued returned from isElementArraySimple, test1.",
		isElementArraySimple(elementArray) == 1 );

	appendElement(elementArray, real);
	mu_assert("Unexpected valued returned from isElementArraySimple, test2.",
		isElementArraySimple(elementArray) == 1 );

	appendElement(elementArray, boolean);
	mu_assert("Unexpected valued returned from isElementArraySimple, test3.",
		isElementArraySimple(elementArray) == 1 );

	appendElement(elementArray, string);
	mu_assert("Unexpected valued returned from isElementArraySimple, test4.",
		isElementArraySimple(elementArray) == 1 );

	appendElement(elementArray, chars);
	mu_assert("Unexpected valued returned from isElementArraySimple, test5.",
		isElementArraySimple(elementArray) == 1 );

	appendElement(elementArray, symbol);
	mu_assert("Unexpected valued returned from isElementArraySimple, test6.",
		isElementArraySimple(elementArray) == 0 );
	
	return NULL;
}

char *
test_all_Symbol()
{
	mu_run_test(test_newParamSym);
	mu_run_test(test_newAnonArraySym);
	mu_run_test(test_newConstProxySym);
	mu_run_test(test_newConstSymFromProxy);
	mu_run_test(test_isValidArrayAccess);
	mu_run_test(test_newTypeSymFromSym);
	mu_run_test(test_newSubrangeSym);
	mu_run_test(test_newAnonScalarSym);
	mu_run_test(test_newVariableSym);
	mu_run_test(test_isConstInScalar);
	mu_run_test(test_isElementArraySimple);
	return NULL;
}
