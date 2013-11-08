#ifndef TESTELEMENTARRAY_H
#define TESTELEMENTARRAY_H

#include "minunit.h"
#include "../../src/ElementArray.h"
#include "testSymbol.h"

char *test_newElementArray();
char *test_growElementArray();
char *test_appendElement();
char *test_getElementAt();
char *test_appendElementArray();
char *test_freeElementArray();
char *test_all_ElementArray();
char *test_hasDuplicateElement();

#endif
