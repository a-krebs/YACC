#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ProgList.h"

#if LEXTEST_DEBUG
	#include "tokenTestParser.tab.h"
#else
	#include "parser.tab.h"
#endif

#define FILE_MODE "r"

extern FILE *yyin;

struct args {
	/* Leave Asc code in file .asc instead of removing it */
	int S;
	/* Do not produce a program listing. Default is to produce one. */
	int n;
	/* 
	 * Do not generate run-time script-bounds checking.
	 * Default is to do the checking.
	 */
	int a;
	/* Input file name */
	char *inFile;
	/* Listing file name */
	char *listingFile;
};

/*
 * Use getopt to parse and validate the given program arguments.
 *
 * Return non-zero on error.
 */
int parseInputs(int argc, char **argv, struct args* argStruct)
{
	/* expected arguments */
	int S = 0;
	int n = 0;
	int a = 0;
	char *file = NULL;
	char *listing = NULL;

	/* vars needed for parsing */
	int index;
	int option;

	/* reset opterr */
	opterr = 0;

	/* check options */
	while ((option = getopt(argc, argv, "Sna")) != -1) {
		switch (option) {
		case 'S':
			S = 1;
			break;
		case 'n':
			n = 1;
			break;
		case 'a':
			a = 1;
			break;
		case '?':
			if (isprint(optopt)) {
				fprintf(
				    stderr,
				    "Unknown option `-%c'.\n",
				    optopt);
			} else {
				fprintf(
				    stderr,
				    "Unknown option character `\\x%x'.\n",
				    optopt);
			}
			/* fall through to default */
		default:
			return -1;
		}
	}

	/* filename should be next argument */
	if (optind >= argc) {
		printf("Missing file name argument.\n");
		return -1;
	}
	file = argv[optind];
	optind++;

	/* complain if there are other arguments */
	for (index = optind; index < argc; index++) {
		printf("Non-option argument %s\n", argv[index]);
	}

	listing = getListingFileName(file);
	if (listing == NULL) {
		return -1;
	}

	/* set values in arg struct */
	argStruct->S = S;
	argStruct->n = n;
	argStruct->a = a;
	argStruct->inFile = file;
	argStruct->listingFile = listing;

#if DEBUG
	printf("S: %d\n", S);
	printf("n: %d\n", n);
	printf("a: %d\n", a);
	printf("inFile: %s\n", file);
	printf("listingFile: %s\n", listing);
#endif

	return 0;
}


/*
 * Main entry point for the Team YACC PAL compiler.
 */
int main( int argc, char *argv[] )
{
	struct args givenArgs;
	int argsParsedSuccess = 0;
	FILE *fp = NULL;

	memset(&givenArgs, 0, sizeof(struct args));

	/* parse the given arguments */
	parseInputs(argc, argv, &givenArgs);

	/* check that parsing was success */
	if (argsParsedSuccess != 0) {
		return EXIT_FAILURE;
	}

	/* TODO open file and pass pointer to bison/flex */
	fp = fopen(givenArgs.inFile, FILE_MODE);
	if (fp == NULL) {
		return EXIT_FAILURE;
	}
	yyin = fp;

	/* TODO test yyparse() for correct call */
	/* parse file */
	yyparse();

	/* 
	 * print program listing.
	 * 0 means the flag is NOT SET, so produce file
	 */
	if (givenArgs.n == 0) {
		printProgramListing(fp, givenArgs.listingFile);
	}

	/* close file, clean up, and exit */
	if (fclose(fp) != 0) {
		return EXIT_FAILURE;
	}
	
	free(givenArgs.listingFile);

	return EXIT_SUCCESS;
}
