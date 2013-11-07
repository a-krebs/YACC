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

int tests_run = 0;

int main(int argc, char *argv[]) {
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
	mu_run_suite(test_all_Symbol);
	mu_run_suite(test_all_Kind);
	mu_run_suite(test_all_Type);
	mu_run_suite(test_all_Hash);
	mu_run_suite(test_all_Actions);
	mu_run_suite(test_all_Utils);
	mu_run_suite(test_all_PreDef);
	return NULL;
}
