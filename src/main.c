#include <stdlib.h>
#include <stdio.h>
#include "dummy_shared.h"

/*
 * Mian entry point for the Team YACC PAL compiler.
 */
int main(int argc, char *argv[]) {
	int tmp = 0;
	tmp = dummySharedFunc(0);
	printf("0+1=%d\n", tmp);
	return EXIT_SUCCESS;
}
