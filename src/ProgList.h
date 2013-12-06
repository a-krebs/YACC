/*
 * Cmput 415 = Team YACC
 * Module implementing functionality related to the production
 * of the program listing (with errors) at end of compilation.
 */

#ifndef PROGLIST_H
#define PROGLIST_H

#include "Error.h"
#include "ErrorLL.h"

#define ERRMSG_SIZE ERR_STRSIZE + 128

extern struct ErrorLL *errors;

/*
 * Produces the program listing for the given compilation.
 * Pre: in is points to the input file which was parsed/compiled
 *      fileName is a null terminated string which is the name
 *               of the file to which to write the program listing
 * 
 * Parameter: pointer to input file, string of file name
 * 
 * 
 * Return: void
 * 
 */
void printProgramListing(FILE *, char *);

/* not used */
int getNextErrLineno(struct ErrorLL **);

/*
 * Given an input file name, strip the '.pal' and return
 * a string with a '.lst' ending.
 *
 * Return a pointer to the new filename, be sure to
 * call free() on it later.
 * Return NULL if the file name cannot be generated.
 *
 * Parameter: string of input file name
 * 
 * 
 * Return: string of listing file name
 * 
 */
char *getListingFileName(char*);



#endif
