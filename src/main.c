#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#include "ProgList.h"
#include "args.h"
#include "Hash.h"
#include "Emit.h"
#include "StmtLL.h"
/* must include for symbol typedef to work with parser. */
#include "SymbolAll.h"
#include "Init.h"

#if LEXTEST_DEBUG
	#include "tokenTestParser.tab.h"
#else
	#include "parser.tab.h"
#endif

#define FILE_MODE "r"
#define ASC_FEXE_NAME "asc"

extern FILE *yyin;
/* global program arguments struct */
extern struct args givenArgs;
extern StmtLL *stmts;

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
	int c = 0;	/* flag, set if we want to compile without running asc*/
	char *ascFile = NULL;
	char *file = NULL;
	char *listing = NULL;

	/* vars needed for parsing */
	int index;
	int option;

	/* reset opterr */
	opterr = 0;

	/* check options */
	while ((option = getopt(argc, argv, "Snaqc")) != -1) {
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
		case 'c':
			c = 1;
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

	ascFile = getAscFileName(file);
	if (!ascFile) return -1;

	/* set values in arg struct */
	argStruct->S = S;
	argStruct->n = n;
	argStruct->a = a;
	argStruct->q = q;
	argStruct->c = c;
	argStruct->inFile = file;
	argStruct->listingFile = listing;
	argStruct->ascFile = ascFile;

#if DEBUG
	printf("S: %d\n", S);
	printf("n: %d\n", n);
	printf("a: %d\n", a);
	printf("q: %d\n", q);
	printf("c: %d\n", c);
	printf("inFile: %s\n", file);
	printf("listingFile: %s\n", listing);
#endif

	return 0;
}


/* 
 * Fork and run ASC interpreter.
 */
static void forkAndRun(char *ascFileName)
{
	int status = 0;
	pid_t pid;
	pid = fork();
	if (pid == 0) {
		if (execlp(ASC_FEXE_NAME, ascFileName) == -1) {
			exit(EXIT_FAILURE);
		}
	} else {
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status)) {
			err(EXIT_FAILURE, "ASC interpreter returned with "
			    "error status.");
		}
	}
}


/*
 * Main entry point for the Team YACC PAL compiler.
 */
int main( int argc, char *argv[] )
{
	int fileGenerated = -1;
	int argsParsedSuccess = 0;
	FILE *fp = NULL;

	/* initialize global args struct */
	memset(&givenArgs, 0, sizeof(struct args));

	/* parse the given arguments */
	parseInputs(argc, argv, &givenArgs);

	/* check that parsing was success */
	if (argsParsedSuccess != 0) {
		fprintf(stderr, "Argument parsing failed.\n");
		return EXIT_FAILURE;
	}

	fp = fopen(givenArgs.inFile, FILE_MODE);
	if (fp == NULL) {
		fprintf(stderr, "Invalid input file.\n");
		return EXIT_FAILURE;
	}
	yyin = fp;

	/* initizie symbol table and pre-defitions */
	initialize();
	
	/* parse file */
	yyparse();

#ifdef DEBUG
	dumpStmtLL(stmts);
#endif
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

	/* Generate .asc file */
	fileGenerated = emitToFile(givenArgs.ascFile);
	if (fileGenerated != 0) {
		/* 
		 * Print to standard output, as this is not an error in our
		 * compiler.
		 */
		fprintf(stdout, "Did not generate .asc file, as the "
		    "given .pal file contains errors.");
	}

	/* close file input file*/
	if (fclose(fp) != 0) {
		err(EXIT_FAILURE, "File IO error.");
	}

	/* if emitting went OK, call the ASC interpreter */
	if (fileGenerated == 0) {
		forkAndRun(givenArgs.ascFile);
	}

	/*
	 * Remove the generated asc file.
	 * If the flag is not set, we remove the file.
	 */
	if ((givenArgs.S == 0) && (fileGenerated == 0)) {
		if (remove(givenArgs.ascFile) != 0) {
			err(EXIT_FAILURE, "Failed to remove generated .asc "
			    "file.");
		}
	}
	
	/* clean up */
	free(givenArgs.listingFile);
	free(givenArgs.ascFile);
	deInitialize();

	return EXIT_SUCCESS;
}
