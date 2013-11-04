#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ProgList.h"
#include "args.h"
#include "Hash.h"
/* must include for symbol typedef to work with parser. */
#include "Symbol.h"

#if LEXTEST_DEBUG
	#include "tokenTestParser.tab.h"
#else
	#include "parser.tab.h"
#endif

#define FILE_MODE "r"

extern FILE *yyin;
/* global program arguments struct */
extern struct args givenArgs;
extern struct hashElement *symbolTable[TABLE_SIZE];

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
	int q = 0;
	char *file = NULL;
	char *listing = NULL;

	/* vars needed for parsing */
	int index;
	int option;

	/* reset opterr */
	opterr = 0;

	/* check options */
	while ((option = getopt(argc, argv, "Snaq")) != -1) {
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
		case 'q':
			q = 1;
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
	argStruct->q = q;
	argStruct->inFile = file;
	argStruct->listingFile = listing;

#if DEBUG
	printf("S: %d\n", S);
	printf("n: %d\n", n);
	printf("a: %d\n", a);
	printf("q: %d\n", q);
	printf("inFile: %s\n", file);
	printf("listingFile: %s\n", listing);
#endif

	return 0;
}


void testHash() {
	// createHashElement("blue", 14);
 //    	createHashElement("GREEN", 7);
	// createHashElement("bee", 6);
	// createHashElement("bbbb", 888);
	// createHashElement("e", 4);
	// createHashElement("blue", 15);
	// dumpSymbolTable();
}


/*
 * Main entry point for the Team YACC PAL compiler.
 */
int main( int argc, char *argv[] )
{
	// //testHash();

	int argsParsedSuccess = 0;
	FILE *fp = NULL;

	/* initialize global args struct */
	memset(&givenArgs, 0, sizeof(struct args));

	/* parse the given arguments */
	parseInputs(argc, argv, &givenArgs);

	/* check that parsing was success */
	if (argsParsedSuccess != 0) {
		printf("Argument parsing failed.\n");
		return EXIT_FAILURE;
	}

	fp = fopen(givenArgs.inFile, FILE_MODE);
	if (fp == NULL) {
		printf("Invalid input file.\n");
		return EXIT_FAILURE;
	}
	yyin = fp;

	/* parse file */
	yyparse();

	/* 
	 * print program listing.
	 * 0 means the flag is NOT SET, so produce file
	 */
	if (givenArgs.n == 0) {
		/*
		 * First set fp to point to beginning of file before passing
		 * it to printProgramListing.
		 */
		fseek(fp, 0L, SEEK_SET);
		printProgramListing(fp, givenArgs.listingFile);
	}

	/* close file, clean up, and exit */
	if (fclose(fp) != 0) {
		return EXIT_FAILURE;
	}
	
	free(givenArgs.listingFile);

	
	destroySymbolTable();
	
	return EXIT_SUCCESS;
}
