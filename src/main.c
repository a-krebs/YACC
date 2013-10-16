#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#if LEXTEST_DEBUG
	#include "tokenTestParser.tab.h"
#else
	#include "parser.tab.h"
#endif

extern FILE *yyin;

/*char commandOptions[4] = "Sna";  TODO: put in header file */

int programlist = 1;

int boundscheck = 1;

char inputfile[100];
char outputfile[100];


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

void parseInputs( int argc, char *argv[] ) {

	if ( argc == 1 ) {
		/*TODO: create error*/
		printf("error: no arguments to compilier\n");
        exit(1);
	}
    
    int c;
    int digit_optind = 0;
    int aopt = 0, bopt = 0;
    char cmd[100];
    sprintf(cmd, "nroff -man ./man/pal.man");
    memset(inputfile, 0, 100);
    memset(outputfile, 0, 100);
	
    while ( (c = getopt(argc, argv, "Snachi:o:")) != -1) {
        switch (c) {
			printf("%d\n", c);
        case 'S':
            printf("PH leave ASC file intact\n");
            break;
        case 'c':
            printf("PH generate ASC file without invoking ASC\n");
            break;
        case 'n':
            programlist = 0;
//          printf("do not produce program listing");
            break;
        case 'a':
            boundscheck = 0;
            printf("PH do not perform runtime run-time array");
            printf("subscript bounds checking\n");
            break;
        case 'h':
    		system(cmd);
//          printf("show man page");
            exit(0);
            break;
        case 'i':
            printf ("option i with value '%s'\n", optarg);
            strcpy(inputfile, optarg);
            yyin = openFile(inputfile, "r");
            break;
//        case 'o':
//            printf ("option o with value '%s'\n", optarg);
//            strcpy(outputfile, optarg);
//            yyout = openFile(outputfile, "w");
//            break;
        default:
//            system(cmd);
//            exit(1);
            break;
        }
    }

    if (optind < argc) {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");
    }

    int i;

    int inputflag = 0;
    for (i = 0; i < argc; i++)
    {
        if (strncmp(argv[i], "-i", 2) == 0)
        {   
            if (strncmp(argv[i+1], "-", 1) == 0)
                {}
            else
                 inputflag = 1;
        }
    }
    if (inputflag == 0)
    {
        printf("no input file specified\n");
        exit(1);
    }

//    int outputflag = 0;
//    for (i = 0; i < argc; i++)
//    {
//        if (strncmp(argv[i], "-o", 2) == 0)
//       {
//            if ((strncmp(argv[i+1], "-", 1) == 0))
//                {}
//           else
//                outputflag = 1;
//        }
//    }
//    if (outputflag == 0)
//    {
//        printf("no output file specified\n");
//        exit(1);
//    }






}




/*
 * Main entry point for the Team YACC PAL compiler.
 */
int main( int argc, char *argv[] )
{
	parseInputs(argc, argv);

	/* test yyparse() for correct call */
	yyparse();

//    if (programlist != 0)
//    {
//        printProgramListing(yyin);
//    }

	fclose(yyin);

	return EXIT_SUCCESS;
}
