#ifndef TESTSYMBOL_H
#define TESTSYMBOL_H
#include "minunit.h"
#include "../../src/Symbol.h"

Symbol * setUpTypeSymbol();
Symbol * setUpConstSymbol();
Symbol * setUpIntConst();

char * test_newAnonArraySym();
char * test_newConstProxySym();
char * test_newConstSymFromProxy();
char * test_newParamSym();
char * test_newTypeSymFromSym();
char * test_newVariableSym();
char * test_newSubrangeSym();
char * test_newParameter;
char * test_all_Symbol();
char * test_isValidArrayAccess();
char * test_newAnonScalarSym();
char * test_isConstInScalar();
#endif
