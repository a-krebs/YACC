#include <stdio.h>
#include "minunit.h"
#include "testError.h"
#include "testErrorLL.h"
#include "testProgList.h"


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
	mu_run_test(test_all_Error);
	mu_run_test(test_all_ErrorLL);
	mu_run_test(test_all_ProgList);

	return NULL;
}
