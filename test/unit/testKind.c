/*
 * Unit tests for the Kind module.
 */
#include <stdio.h>
#include <stdlib.h>

#include "Type.h"
#include "testKind.h"
#include "testSymbol.h"

extern double REAL_VAL;

char *
test_getConstVal()
{
	Symbol *constSym = setUpConstSymbol();
	AnonConstVal *ret = NULL;

	ret = getConstVal(constSym);
	mu_assert("getConstVal() should not return null when passed a valid"
	    "symbol from which to retrieve a value", ret);

	mu_assert("getConstVal() should return an anon const value with the"
	    "the expected real value", ret->Real.value = REAL_VAL);

	mu_assert("getConstVal() return value should point to the anon const"
	   "value struct of the symbol from which it retrieved the value",
	    ret == &(constSym->kindPtr.ConstKind->value));
	return NULL;
}

char *
test_copyConstVal()
{
	Symbol *constSym = setUpConstSymbol();
	AnonConstVal ret;

	copyConstVal(&ret, (getConstVal(constSym)),
	    getType(constSym));

	mu_assert("copyConstValue() should return a copy of the const val"
	    "union",
	    ret.Real.value == constSym->kindPtr.ConstKind->value.Real.value);
	return NULL;
}

char *
test_all_Kind()
{
	mu_run_test(test_copyConstVal);
	mu_run_test(test_getConstVal);
	return NULL;
}
