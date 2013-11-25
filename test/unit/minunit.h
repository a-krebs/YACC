/* 
 * minunit.h
 *
 * Testing Framework.
 *
 * See http://www.jera.com/techinfo/jtns/jtn002.html
 *
 */

#include "testingUtils.h"

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { initTestEnv();\
				char *message = test();\
				tests_run++; \
				tearDownTestEnv();\
				if (message) return message; } while (0)

#define mu_run_suite(suite) do { char *message = suite(); \
				if (message) return message; } while (0)

extern int tests_run;

char *test_all();
