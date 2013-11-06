#ifndef TESTSYMBOL_H
#define TESTSYMBOL_H
#include "minunit.h"
#include "../../src/Symbol.h"

Symbol * setUpTypeSymbol();
Symbol * setUpConstSymbol();

char * test_newTypeSymFromSym();
char * test_newVariableSym();
char * test_newSubrangeSym();
char * test_newParameter;
char * test_all_Symbol();
#endif
