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
	- change tests once real hash functions is created
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
	mu_assert("Collision on empty symbol table.", 
 		isKeyCollison("blue") == 0);


	createHashElement("blue", 456666);
	mu_assert("Could not find key collision where one should exist.", 
 		isKeyCollison("blue") == 1);

	mu_assert("Found key collision where one should not exist.", 
 		isKeyCollison("green") == 0); 			

	destroySymbolTable();

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

char *test_isKeysIdentical() {
	struct hashElement *element = createNewElement("blue", 123);

	mu_assert("Keys idenitcal but evaluating to different.", 
 		isKeysIdentical(element, "blue") == 1);

	mu_assert("Keys differnt but evaluating to same.", 
 		isKeysIdentical(element, "green") == 0);	

	return NULL;
}


//THIS IS BROKEN!!!!!!!!!!!!!!!!
// char *test_findHashElementByKey() {
// 	struct hashElement *element = createNewElement("blue", 123);

// 	mu_assert("Could not find element that should be table.", 
//  		findHashElementByKey("blue") != NULL);

// 	mu_assert("Found element that should not be table.", 
//  		findHashElementByKey("green") == NULL);


// 	return NULL;
// }

char *test_appendToHashBucket() {
	struct hashElement *element1 = createNewElement("blue", 123);
	struct hashElement *element2 = createNewElement("green", 456);

	appendToHashBucket(element1, element2);
	mu_assert("Call to appendToHashBucket does not seg fault.", 1);

	mu_assert("Head element of bucket not set propertly.", 
 		element1->prev == NULL);

	mu_assert("Append element did not work.", 
 		element1->next != NULL);

	mu_assert("Cannot access prev element in bucket list.", 
 		element2->prev != NULL);	

	mu_assert("End of list not propertly set.", 
 		element2->next == NULL);

	mu_assert("Bucket list not assigning next propertly.", 
 		element1->next == element2);	

	mu_assert("Bucket list not assigning prev propertly.", 
 		element2->prev == element1);		

	return NULL;
}

char *test_createHashElement() {
	
	destroySymbolTable();
	mu_assert("Could not created element in empty table.", 
 		createHashElement("blue", 123) == 0);

	mu_assert("Over written hash value.", 
 		createHashElement("blue", 456) == 1);	

	mu_assert("Could not create element where hash collison happened.", 
 		createHashElement("b", 456666) == 0);	

	destroySymbolTable();

	return NULL;
}




char * test_all_Hash() {
	mu_run_test(test_dumpEmptySymbolTable);
	mu_run_test(test_getHashedKey);
	mu_run_test(test_isKeyCollison);
	mu_run_test(test_createNewElement);
	mu_run_test(test_isKeysIdentical);
	// mu_run_test(test_findHashElementByKey);
	mu_run_test(test_appendToHashBucket);
	mu_run_test(test_createHashElement);

	return NULL;
}
