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
#include "SymbolAll.h"
#include "Hash.h"
#include "Globals.h"

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
	Symbol *typeSym = NULL;

	typeSym = createTypeSymbol("testType", TYPEORIGINATOR_NO);
	typeSym->kindPtr.TypeKind->typePtr.Integer =
	     calloc(1, sizeof(struct Integer));

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
	if (!constSym) {
		err(1, "Failed to allocate memory for test type symbol!");
		exit(1);
	}

	setSymbolName(constSym, id);
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
	Symbol *subrangeSym = newSubrangeSym(lowConst, highConst);
	Symbol *baseTypeSym = setUpTypeSymbol();
	newArraySym = newAnonArraySym(baseTypeSym, subrangeSym);

	mu_assert("newArraySym should not be NULL", newArraySym); 
	mu_assert("newArraySym should have subrange as expected",
	    getTypePtr(newArraySym)->Array->indexTypeSym == subrangeSym);
	mu_assert("newArraySym should have base type as expecte",
	    getTypePtr(newArraySym)->Array->baseTypeSym == baseTypeSym);
	mu_assert("newArraySym should be at the expected lexical level",
	    newArraySym->lvl == 0);

	return NULL;
}

char *
test_newParamSym()
{
	Symbol *s = NULL;
	Symbol *typeSym = setUpTypeSymbol();
	char id[] = "testParam";
	
	s = newParamSym(id, typeSym);
	mu_assert("newParamSYm should not be null", s);
	mu_assert("newParamSym should have type as expected",
	    getTypeSym(s) == typeSym);
	mu_assert("newParamSym should be at expected lexical level",
	   s->lvl == getCurrentLexLevel(symbolTable));
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
	constProxySym = newConstProxySym(NULL, &(intResult), typeSym);

	mu_assert("newConstProxySym() should not return NULL ProxySymbol"
	    " when given valid input", constProxySym);

	mu_assert("newConstProxySym() should return boolean const kind Proxy "
	    "Symbol with the expected attributes",
	    (constProxySym->kind == CONST_KIND) &&
	    (getConstVal(constProxySym)->Boolean.value == intResult) &&
	    (getTypeSym(constProxySym) == typeSym));
	

	typeSym->kindPtr.TypeKind->type = REAL_T;
	constProxySym = newConstProxySym(NULL, &(doubleResult), typeSym);

	mu_assert("newConstProxySym() should not return NULL ProxySymbol"
	    " when given valid input", constProxySym);

	mu_assert("newConstProxySym() should return real const kind Proxy "
	    "Symbol with the expected attributes",
	    (constProxySym->kind == CONST_KIND) &&
	    (getConstVal(constProxySym)->Real.value == doubleResult) &&
	    (getTypeSym(constProxySym) == typeSym));

	typeSym->kindPtr.TypeKind->type = INTEGER_T;
	constProxySym = newConstProxySym(NULL, &(intResult), typeSym);

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

	setLexLevel(symbolTable, 10);

	newTypeSym = newTypeSymFromSym(id, typeSym);
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

	newVar = newVariableSym(id, NULL);
	mu_assert("newVariable() should return NULL if NULL typeSym passed",
		!newVar);
	
	newVar = newVariableSym(NULL, typeSym);
	mu_assert("newVariable() should return NULL if NULL id passed",
		!newVar);

	typeSym->kind = VAR_KIND;
	newVar = newVariableSym(id, typeSym);
	mu_assert("newVariable() should return NULL if passed VAR_KIND symbol",
		!newVar);

	typeSym->kind = TYPE_KIND;

	newVar = newVariableSym(id, typeSym);
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

	getTypeSym(testSymLow)->kindPtr.TypeKind->type = INTEGER_T;
	getTypeSym(testSymHigh)->kindPtr.TypeKind->type = INTEGER_T;
	getConstVal(testSymLow)->Integer.value = INTLOW_VAL;
	getConstVal(testSymHigh)->Integer.value = INTHIGH_VAL;
	
	subrangeSym = newSubrangeSym(testSymLow, NULL);
	mu_assert("newSubrangeSym() should return NULL if a symbol arg is NULL",
		  !subrangeSym);


	subrangeSym = newSubrangeSym(testSymHigh, testSymLow);
	mu_assert("newSubRangeSym() should return NULL if low >= high",
		  !subrangeSym);


	subrangeSym = newSubrangeSym(testSymLow, testSymHigh);
	mu_assert("newSubRangeSym() should return expected subrange",
	    (getTypePtr(subrangeSym)->Subrange->low == INTLOW_VAL));

	getTypeSym(testSymLow)->kindPtr.TypeKind->type = SCALAR_T;
	subrangeSym = newSubrangeSym(testSymLow, testSymHigh);
	mu_assert("newSubrangeSym() should return null when symbol types \
		   mistmatch.", !subrangeSym);

	return NULL;
}

char *
test_newAnonScalarSym()
{
	setLexLevel(symbolTable, 10);

	Symbol *ss = NULL;
	Symbol *c = setUpIntConst();
	struct ElementArray *ea = newElementArray();
	growElementArray(ea);
	appendElement(ea, c);

	ss = newAnonScalarListTypeSym(ea);
	mu_assert("newAnonScalar is not NULL when given valid inputs", ss);
	mu_assert("newAnonScalar should have lvl as epxected", ss->lvl == 10);
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
	int lvl = 10;
	char id[] = "hello";

	setLexLevel(symbolTable, lvl);

	ss = newAnonScalarListTypeSym(ea);
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
	Symbol *subrangeSym = newSubrangeSym(lowConst, highConst);
	Symbol *baseTypeSym = setUpTypeSymbol();
	Symbol *var = NULL;

	newArraySym = newAnonArraySym(baseTypeSym, subrangeSym);
	var = newVariableSym("hello", newArraySym);

	ProxySymbol *index1 = (ProxySymbol *) lowConst;

	index1->kindPtr.ConstKind->typeSym =
	    lowConst->kindPtr.ConstKind->typeSym;

	mu_assert("isValidArrayAccess() should recognize valid array access",
	    isValidArrayAccess(newArraySym, lowConst)); 
	mu_assert("isValidArrayAccess() should recognize invalid array access",
	    isValidArrayAccess(newArraySym, var) == NULL); 

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

char *test_allocateSymbol() {
	Symbol *sym = NULL;

	sym = allocateSymbol();

	mu_assert("Symbol is NULL",
	    sym != NULL);

	return NULL;
}


char *test_createConstSymbol() {
	struct hash *table = createHash(&getHashedKeySimple);
	Symbol * symbol = NULL;
	char *id = malloc(5*sizeof(char));
	strncpy(id, "test\0", 5);

	symbol = createSymbol(table, id, CONST_KIND, 0);

	// free name, to make sure it's copied
	free(id);

	mu_assert("Symol name not copied",
	    strncmp(symbol->name, "test", 4) == 0);
	mu_assert("Symbol kind not set to CONST_KIND",
	    symbol->kind == CONST_KIND);
	mu_assert("Symbol typeOriginator not set properly",
	    symbol->typeOriginator == 0);

	destroyHash(&table);

	return NULL;
}


char *test_createFuncSymbol() {
	struct hash *table = createHash(&getHashedKeySimple);
	Symbol * symbol = NULL;
	char *id = malloc(5*sizeof(char));
	strncpy(id, "test\0", 5);

	symbol = createSymbol(table, id, FUNC_KIND, 0);

	// free name, to make sure it's copied
	free(id);

	mu_assert("Symol name not copied",
	    strncmp(symbol->name, "test", 4) == 0);
	mu_assert("Symbol kind not set to CONST_KIND",
	    symbol->kind == FUNC_KIND);
	mu_assert("Symbol typeOriginator not set properly",
	    symbol->typeOriginator == 0);

	destroyHash(&table);

	return NULL;
}



char *test_createParamSymbol() {
	struct hash *table = createHash(&getHashedKeySimple);
	Symbol * symbol = NULL;
	char *id = malloc(5*sizeof(char));
	strncpy(id, "test\0", 5);

	symbol = createSymbol(table, id, PARAM_KIND, 0);

	// free name, to make sure it's copied
	free(id);

	mu_assert("Symol name not copied",
	    strncmp(symbol->name, "test", 4) == 0);
	mu_assert("Symbol kind not set to CONST_KIND",
	    symbol->kind == PARAM_KIND);
	mu_assert("Symbol typeOriginator not set properly",
	    symbol->typeOriginator == 0);

	destroyHash(&table);

	return NULL;
}


char *test_createProcSymbol() {
	struct hash *table = createHash(&getHashedKeySimple);
	Symbol * symbol = NULL;
	char *id = malloc(5*sizeof(char));
	strncpy(id, "test\0", 5);

	symbol = createSymbol(table, id, PROC_KIND, 0);

	// free name, to make sure it's copied
	free(id);

	mu_assert("Symol name not copied",
	    strncmp(symbol->name, "test", 4) == 0);
	mu_assert("Symbol kind not set to CONST_KIND",
	    symbol->kind == PROC_KIND);
	mu_assert("Symbol typeOriginator not set properly",
	    symbol->typeOriginator == 0);

	destroyHash(&table);

	return NULL;
}


char *test_createTypeSymbol() {
	struct hash *table = createHash(&getHashedKeySimple);
	Symbol * symbol = NULL;
	char *id = malloc(5*sizeof(char));
	strncpy(id, "test\0", 5);

	symbol = createSymbol(table, id, TYPE_KIND, 0);

	// free name, to make sure it's copied
	free(id);

	mu_assert("Symol name not copied",
	    strncmp(symbol->name, "test", 4) == 0);
	mu_assert("Symbol kind not set to CONST_KIND",
	    symbol->kind == TYPE_KIND);
	mu_assert("Symbol typeOriginator not set properly",
	    symbol->typeOriginator == 0);

	destroyHash(&table);

	return NULL;
}


char *test_createVarSymbol() {
	struct hash *table = createHash(&getHashedKeySimple);
	Symbol * symbol = NULL;
	char *id = malloc(5*sizeof(char));
	strncpy(id, "test\0", 5);

	symbol = createSymbol(table, id, VAR_KIND, 0);

	// free name, to make sure it's copied
	free(id);

	mu_assert("Symol name not copied",
	    strncmp(symbol->name, "test", 4) == 0);
	mu_assert("Symbol kind not set to CONST_KIND",
	    symbol->kind == VAR_KIND);
	mu_assert("Symbol typeOriginator not set properly",
	    symbol->typeOriginator == 0);

	destroyHash(&table);

	return NULL;
}


char *test_all_Symbol() {
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
	mu_run_test(test_allocateSymbol);
	mu_run_test(test_createConstSymbol);
	mu_run_test(test_createFuncSymbol);
	mu_run_test(test_createParamSymbol);
	mu_run_test(test_createProcSymbol);
	mu_run_test(test_createTypeSymbol);
	mu_run_test(test_createVarSymbol);
	return NULL;
}

