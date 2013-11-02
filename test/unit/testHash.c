/*
 * Cmput 415 - Team YACC
 * Unit tests for the Hash module.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <unistd.h>

#include "testHash.h"
#include "../../src/Hash.h"


/*TODO:
	- dump table with something in it.
	- create tests for test_getHashedKey once
		using real hash function
*/ 


// char *test_getErrorTypeString() {
// 	char *syntax = "Syntax";
// 	char *semantic = "Semantic";


// 	mu_assert("getErrorTypeString returned wrong string.",
// 	    strcmp(dump(SYNTAX), syntax) == 0);
// 	return NULL;
// }




char *test_dumpEmptySymbolTable() {
/*test 1: Empty symbol table seg fault teset.*/
	dumpSymbolTable();
	mu_assert("Call to dumper does not seg fault.", 1);

/*test 2: Copy stdout to to buffer and compare out of empty symbol table.*/
	char buffer[100] = {0};
	int out_pipe[2];
	int saved_stdout = dup(STDOUT_FILENO); /* save stdout for display later */

	pipe(out_pipe);						/* make a pipe */
	dup2(out_pipe[1], STDOUT_FILENO);   /* redirect stdout to the pipe */
	close(out_pipe[1]);

 	dumpSymbolTable();		/* anything sent to printf should now go down the pipe */
 	fflush(stdout);

 	read(out_pipe[0], buffer, 100); /* read from pipe into buffer */
 	dup2(saved_stdout, STDOUT_FILENO);  /* reconnect stdout for testing */

 	char expectedOutput[33] = "\n\nDUMPING HASH:\nDUMP COMPLETE.\n\n";

	mu_assert("Hash dumper gives unexpected output on empty hash.", 
 		strcmp(expectedOutput, buffer) == 0);


	return NULL;
}


char *test_getHashedKey() {
/*test 1: Hash function in bounds.*/
	// mu_assert("Hash function returing values out of bounds.", 
 // 		(getHashedKey("e") < TABLE_SIZE));

	return NULL;
}

// char *test_() {
// /*test 1: .*/
// 	mu_assert(".", 
//  		);

// 	return NULL;
// }

char *test_isKeyCollison() {
/*test 1: .*/
	mu_assert("Collision on empty symbol table.", 
 		isKeyCollison("blue") == 0);

	return NULL;
}


char *test_createNewElement() {
	struct hashElement *element = createNewElement("blue", 123);

	mu_assert("Unable to create hash element.", 
 		element != NULL);

	mu_assert("Incorrect key in hash element.", 
 		strcmp(element->key, "blue") == 0);

	mu_assert("Incorrect value in hash element.", 
 		element->value == 123);

	mu_assert("Hash element not assigned but prev pointing at not NULL.", 
 		element->prev == NULL);

	mu_assert("Hash element not assigned but next pointing at not NULL.", 
 		element->next == NULL);	

	return NULL;
}




char * test_all_Hash() {
	mu_run_test(test_dumpEmptySymbolTable);
	mu_run_test(test_getHashedKey);
	mu_run_test(test_isKeyCollison);
	mu_run_test(test_createNewElement);

	return NULL;
}
