#ifndef TESTPARAMARRAY_H
#define TESTPARAMARRAY_H

#include "minunit.h"
#include "../../src/ParamArray.h"

char *test_newParamArray();
char *test_growParamArray();
char *test_appendParam();
char *test_getParam();
char *test_freeParamArray();
char *test_all_ParamArray();

struct Param * setUpTestParam();
#endif
