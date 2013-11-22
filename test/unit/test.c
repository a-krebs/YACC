#include <stdio.h>
#include "minunit.h"
#include "testError.h"
#include "testErrorLL.h"
#include "testElementArray.h"
#include "testProgList.h"
#include "testKind.h"
#include "testSymbol.h"
#include "testType.h"
#include "testHash.h"
#include "testActions.h"
#include "testUtils.h"
#include "testPreDef.h"

/* Include ASC tests */
#include "testPreDefAsc.h"

/* Include globals */
#include "Globals.h"
#include "Init.h"

int tests_run = 0;

extern struct hash *symbolTable;
extern struct preDefTypeSymbols *preDefTypeSymbols;

int testAsc();

int main(int argc, char *argv[]) {

	initialize();

	/* 
	 * If any argument is passed to the cmd line, we run tests on the
	 * ASC code for the predefined functions 
	 * TODO: change this functionality before the repo goes public
	 * and you bring shame to everyone you love.
	 */
	if (argc > 1) testAsc();

	char *result = test_all();
	if (result != NULL) {
		printf("%s\n", result);
	} else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);

	return result != NULL;
}

/*
 * Call all test functions here.
 */
char *test_all() {
	mu_run_suite(test_all_Error);
	mu_run_suite(test_all_ErrorLL);
	mu_run_suite(test_all_ElementArray);
	mu_run_suite(test_all_ProgList);
	errors = NULL;
	mu_run_suite(test_all_Symbol);
	mu_run_suite(test_all_Kind);
	mu_run_suite(test_all_Type);
	mu_run_suite(test_all_Hash);
	mu_run_suite(test_all_Actions);
	mu_run_suite(test_all_Utils);
	mu_run_suite(test_all_PreDef);
	return NULL;
}

int
testAsc()
{
	setUpAscTests();
	testArctan();
	testAbs();
	testChr();
	testCos();
	testExp();
	testLn();
	testPred();
	testRound();
	testSin();
	testSucc();
	testSqrt();
	testTrunc();
	testWrite();
	testWriteln();
	tearDownAscTests();
	return 0;
}
