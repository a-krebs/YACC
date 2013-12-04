/*
 * Cmput 415 - Team YACC
 * Unit tests for the Actions module
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>

#include "testActions.h"
#include "testSymbol.h"	/* for setUpTypeSymbol() */
#include "ActionsAll.h"
#include "SymbolAPI.h"
#include "tokens.h" /* for test token definitions */
#include "Type.h"

char *test_assertOpCompat() {
	Symbol *type1 = setUpTypeSymbol();
	Symbol *type2 = setUpTypeSymbol();

	mu_assert("Two integer types compatible with PLUS",
	    assertOpCompat(type1, PLUS, type2));	
	mu_assert("Two integer types are compatible with EQUAL",
	    assertOpCompat(type1, EQUAL, type2));

	type1->kindPtr.TypeKind->type = BOOLEAN_T;

	mu_assert("A boolean and an integer are not compatible with LESS",
	    !assertOpCompat(type1, LESS, type2));

	type1->kindPtr.TypeKind->type = ARRAY_T;
	type1->kindPtr.TypeKind->type = ARRAY_T;
	mu_assert("Two arrays types are not compatible with EQUAL",
	   !assertOpCompat(type1, EQUAL, type2));
	
	return NULL;
}

/* test constCal for constant expressions */
char *test_constCalc() {
	Symbol *x = NULL;
	Symbol *y = NULL;
	Symbol *res = NULL;

	Symbol *xType = NULL;
	Symbol *yType = NULL;
	Symbol *resType = NULL;

	xType = createTypeSymbol(NULL, 0);
	yType = createTypeSymbol(NULL, 0);
	resType = createTypeSymbol(NULL, 0);
	
	x = createConstSymbol(NULL);
	setInnerTypeSymbol(x,xType);
	
	y = createConstSymbol(NULL);
	setInnerTypeSymbol(y,yType);
	
	res = createConstSymbol(NULL);
	setInnerTypeSymbol(res,resType);

	/* end of prep stuff  */
	
	xType->kindPtr.TypeKind->type = INTEGER_T;
	yType->kindPtr.TypeKind->type = INTEGER_T;
	resType->kindPtr.TypeKind->type = BOOLEAN_T;
	
	getConstVal(x)->Integer.value = 10;
	getConstVal(y)->Integer.value = 22;

	constCalc(res, x, EQUAL, y);
	mu_assert("constKind EQUAL failing",
	    getConstVal(res)->Boolean.value == 0);

	yType->kindPtr.TypeKind->type = REAL_T;
	constCalc(res, x, EQUAL, y);
	mu_assert("constKind EQUAL failing",
	    getConstVal(res)->Boolean.value == 0);

	getConstVal(y)->Real.value = 10;
	constCalc(res, x, EQUAL, y);
	mu_assert("constKind EQUAL failing",
	    getConstVal(res)->Boolean.value == 1);


	xType->kindPtr.TypeKind->type = INTEGER_T;
	yType->kindPtr.TypeKind->type = INTEGER_T;
	resType->kindPtr.TypeKind->type = BOOLEAN_T;
	
	getConstVal(x)->Integer.value = 10;
	getConstVal(y)->Integer.value = 22;

	constCalc(res, x, DIV, y);
	mu_assert("constKind EQUAL failing",
	    getConstVal(res)->Integer.value == 0);

	return NULL;
}

char *test_all_Actions() {
	mu_run_test(test_assertOpCompat);
	mu_run_test(test_constCalc);
	return NULL;
}
