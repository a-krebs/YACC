#include <stdlib.h>
#include <stdio.h>
#include "dummy_shared.h"

#include "parser.tab.h"

extern FILE *yyin;

/*
 * Mian entry point for the Team YACC PAL compiler.
 */
int 
main(int argc, char *argv[]) 
{
	FILE *in;
	int tmp;
	
	/* unit test example code */
	tmp = 0;
	tmp = dummySharedFunc(0);
	printf("0+1=%d\n", tmp);

	/* for now just pull input file as argv[1] blindly,
	 * this obviously needs to be corrected before checkpoint 1 */
	in = fopen(argv[1], "r");
	if (!in) {
		fprintf(stderr, "Invalid input file specified.\n");
		return -1;
	}

	yyin = in;
	/* test yyparse() for correct call */
	yyparse();
	fclose(in);
	return EXIT_SUCCESS;
}
