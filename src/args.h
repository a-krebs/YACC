/*
 * Structures and global variables needed for program arguments.
 */

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
	/* Do not print error output to stdout. */
	int q;
	/* Do no execute compiled asc file */
	int c;
	/* Input file name */
	char *inFile;
	/* Listing file name */
	char *listingFile;
	/* Generated asc file name */
	char *ascFile;
};

struct args givenArgs;
