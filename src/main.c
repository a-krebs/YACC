#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.tab.h"

extern FILE *yyin;

char commandOptions[4] = "Sna"; /* TODO: put in header file */


FILE * openFile(char *path, char *mode) {
	FILE *file;

	if (path == NULL) {
		/*TODO: create error*/
		printf("error, incorrect path\n");
	}
	
	file = fopen(path, mode);
	if (file == NULL) {
		/*TODO: create error*/
		printf("error, could not open file to read\n");
	}	

	return file;
}


void parseCommandOptions( char *options ) {
	int i, j;
	int flag = 0;

	/* start at 1 b/c 0 is the flag symbol */
	for ( i = 1; i < strlen(options); i++) {
				
		for ( j = 0; j < strlen(commandOptions); j++) {
			
			if ( options[i] == commandOptions[j] ) {
				/*TODO: something needs to happen here to respond to flag*/
				flag = 1;
				break;
			}
		}

		if ( flag != 0 ) {
			/*TODO: create error*/
			printf("error, option '%c' not supported\n", options[i]);
		}
	}
}


void parseInputs( int argc, char *argv[] ) {
	int i, j;
	char *arg;
	int fileFlag = 0;

	if ( argc == 1 ) {
		/*TODO: create error*/
		printf("error: no arguments to compilier\n"); 
	}

	/* start at 1 b/c first element is program */
	for ( i = 1; i < argc; i++ ) { 

		if ( strncmp(argv[i], "-", 1) == 0 ) {
			//found a option and must process
			parseCommandOptions(argv[i]);
			continue;
		}

		//doesn't identify as an option:
		if ( fileFlag == 0) {
			yyin = openFile(argv[i], "r");
			fileFlag = 1;
			continue;
		} else {
			/*TODO: create error*/
			printf("incorrect input options. ");
			printf("Either more than one input file ");
			printf("was specified or input options ");
			printf("inputted.\n");

		}
	}
}


/*
 * Main entry point for the Team YACC PAL compiler.
 */
int main( int argc, char *argv[] )
{
	parseInputs(argc, argv);

	/* test yyparse() for correct call */
	yyparse();
	fclose(yyin);

	return EXIT_SUCCESS;
}
