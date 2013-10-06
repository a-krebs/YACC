#include <stdlib.h>
#include "../src/dummy_shared.h"
#include "minunit.h"

char *test_dummySharedFunc() {
	mu_assert("Addition is broken", dummySharedFunc(1) == 2);
	return NULL;
}

char* test_all_dummy_shared() {
	mu_run_test(test_dummySharedFunc);
	return NULL;
}
