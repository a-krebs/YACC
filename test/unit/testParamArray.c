/*
 * Unit tests for the ParamArray adt.
 * Cmput 415 - Team Yet Another Cmput415 Compiler
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testParamArray.h"

#define DEFAULT_CHAR_VAL 39

struct Param *
setUpTestParam()
{
	struct Param *p = NULL;
	char testName[] = "testParam";
	size_t len;

	p = calloc(1, sizeof(struct Param));
	if (!p) {
		err(1, "Failed to allocate memory for test param struct!");
		exit(1);
	}
	
	len = strlen(testName);
	p->name = calloc(1, (sizeof(char))*len);
	if (!p->name) {
		err(1, "Failed to allocate memory for test param name!");
		exit(1);
	} 
	
	p->typeSymPtr = calloc(1, sizeof(struct Symbol));
	if (!p->typeSymPtr) {
		err(1, "Failed to allocate memory for test param type ptr!");
		exit(1);
	}

	p->typeSymPtr->kindPtr.TypeKind = calloc(1, sizeof(Type));
	p->typeSymPtr->kindPtr.TypeKind->typePtr.Char = calloc(1,sizeof(struct Char)); 
	p->typeSymPtr->kindPtr.TypeKind->typePtr.Char->value = DEFAULT_CHAR_VAL;
	return p;
}


char *
test_newParamArray()
{
	struct ParamArray *pa = newParamArray();

	mu_assert("newParamArray() should not return NULL", pa);
	mu_assert("newParamArray() should have lne == PA_DEFAULT_SZ",
		  pa->len = PA_DEFAULT_SZ);
	mu_assert("newParamArray() data pointer should not be NULL",
		  pa->data);
	mu_assert("newParamArray() should have 0 elements",
		  pa->nElements == 0);

	return NULL;
}


/*
 * Warning:
 * The results of test_growParamArray are dependent on the correct functioning
 * of newParamArray() -- if these tests fail, please insure the correct
 * functioning of newParamArray() before debugging this code.
 */
char *
test_growParamArray()
{
	struct ParamArray *pa = newParamArray();
	unsigned int len;

	growParamArray(pa);
	mu_assert("first call to growParamArray() should set len == \
		   2*(default size)", pa->len == 2 * PA_DEFAULT_SZ);
	mu_assert("growParamArray() should not change number of elements \
		   in the array", pa->nElements == 0);
	
	len = pa->len;
	growParamArray(pa);
	mu_assert("subsequent calls to growParamArray() should double \
		   previous len", pa->len == 2*len);
	return NULL;
}

/*
 * Warning:
 * The results of test_appendParam are dependent on the correct functioning
 * of newParamArray() and growParamArray()-- if the tests below  fail, please 
 * insure the correct functioning of these functions before debugging this code.
 * TODO: test structural integrity of added params under new setup (was 
 * confirmed under old, operation should be independent of what values param
 * struct has, but should be confirmed at some point)
 */
char *
test_appendParam()
{
	struct ParamArray *pa = newParamArray();
	struct Param *p1 = setUpTestParam();
	int i;

	appendParam(pa, p1);
	mu_assert("appendParam() should increment nElements appropriately",
		  pa->nElements == 1);
	mu_assert("appendParam() should not affect param array len when \
		  number of elements added is less than old len",
		  pa->len == PA_DEFAULT_SZ);
	mu_assert("first element in param array should not be null",
		  pa->data[0]);

	appendParam(pa, p1);
	mu_assert("appendParam() should increment nElements appropriately",
		  pa->nElements == 2);
	mu_assert("appendParam() should not affect param array len when \
		  number of elements added is less than old len",
		  pa->len == PA_DEFAULT_SZ);
	mu_assert("second element in param array should not be null",
		  pa->data[1]);
	for (i=0; i < 24; i++) {
		appendParam(pa, p1);
	}

	mu_assert("appendParam() should call growParamArray() to double size \
		  of array when nElements exceeds len",
		  pa->len == 2 * PA_DEFAULT_SZ);
	mu_assert("appendParam() should successfully append param past old \
		  len of the array", pa->data[25]); 

	return NULL;
}

/*
 * Warning:
 * The results of test_getParam are dependent on the correct functioning
 * of newParamArray(), growParamArray(), appendParam -- if the tests below
 *  fail, please insure the correct functioning of these functions before 
 * debugging this code.
 * TODO: test structural integrity of added params under new setup (was 
 * confirmed under old, operation should be independent of what values param
 * struct has, but should be confirmed at some point)
 */

char *
test_getParam()
{
	struct ParamArray *pa = newParamArray();
	struct Param *p1 = setUpTestParam();
	struct Param *p2 = setUpTestParam();
	struct Param *ret = NULL;
	appendParam(pa, p1);
	appendParam(pa, p2);

	ret = getParam(pa, 2);
	mu_assert("getParam() should return NULL when passed index of entry \
		   known to NOT be in the array", !ret);

	ret = getParam(pa, 0);
	mu_assert("getParam() should not return NULL when passed index of \
		  entry known to be in array", ret);

	ret = getParam(pa, 1);

	return NULL;
}

char *
test_freeParamArray()
{
	struct ParamArray *pa = newParamArray();
	struct Param *p1 = setUpTestParam();
	struct Param *p2 = setUpTestParam();
	appendParam(pa, p1);
	appendParam(pa, p2);

	freeParamArray(pa);

	mu_assert("freeParamArray() should free param array pointer witnout \
		  segfaulting", 1);

	return NULL;
}

char *
test_all_ParamArray()
{
	mu_run_test(test_newParamArray);
	mu_run_test(test_growParamArray);
	mu_run_test(test_appendParam);
	mu_run_test(test_getParam);
	mu_run_test(test_freeParamArray);
	return NULL;
}
