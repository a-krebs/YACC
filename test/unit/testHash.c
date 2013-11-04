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
#include "Hash.h"


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

char *test_deleteHashElement_begining() {
   	createHashElement("GREEN", 7);
	createHashElement("bb", 6);
	createHashElement("bbb", 888);
	createHashElement("bbbb", 753);

	struct hashElement *element = findHashElementByKey("bb");
	struct hashElement *newHead = element->next;

	mu_assert("unexpected element at head of bucket list.", 
 		symbolTable[getHashedKey("b")] == element);

	mu_assert("Delete function did not remove begining element.", 
 		deleteHashElement("bb") == 0);

	mu_assert("Begining element not deleted.", 
 		symbolTable[getHashedKey("b")] == newHead);

	mu_assert("Did not delete front of list propertly.", 
 		newHead->prev == NULL);

	mu_assert("Resulting bucket should have more than one element.", 
 		newHead->next != NULL);	

	destroySymbolTable();

	return NULL;
}

char *test_deleteHashElement_end() {
   	createHashElement("GREEN", 7);
	createHashElement("bb", 6);
	createHashElement("bbb", 888);
	createHashElement("bbbb", 753);

	struct hashElement *element = findHashElementByKey("bbbb");
	struct hashElement *newTail = element->prev;

	mu_assert("unexpected element at end of list.", 
 		element->next == NULL);

	mu_assert("Delete function did not remove end element.", 
 		deleteHashElement("bbbb") == 0);

	mu_assert("End element not deleted.", 
 		newTail->next == NULL);

	mu_assert("Did not delete end of list propertly.", 
 		newTail->prev != NULL);

	destroySymbolTable();

	return NULL;
}


char *test_deleteHashElement_middle() {
   	createHashElement("GREEN", 7);
	createHashElement("bb", 6);
	createHashElement("bbb", 888);
	createHashElement("bbbb", 753);

	struct hashElement *element = findHashElementByKey("bbb");
	struct hashElement *head = findHashElementByKey("bb");
	struct hashElement *tail = findHashElementByKey("bbbb");

	mu_assert("unexpected element after head.", 
 		head->next == element);

	mu_assert("unexpected element before tail.", 
 		tail->prev == element);

	mu_assert("Delete function did not remove middle element.", 
 		deleteHashElement("bbb") == 0);

	mu_assert("Did not reset next in list propertly.", 
 		head->next == tail);

	mu_assert("Did not reset prev in list propertly", 
 		tail->prev == head);

	destroySymbolTable();

	return NULL;
}

char *test_deleteHashElement_single() {
   	createHashElement("GREEN", 7);
	createHashElement("bb", 6);
	createHashElement("bbb", 888);
	createHashElement("bbbb", 753);

	struct hashElement *element = findHashElementByKey("GREEN");

	mu_assert("unexpected element at in single bucket list.", 
 		symbolTable[getHashedKey("G")] == element);

	mu_assert("Delete function did not remove single bucket element.", 
 		deleteHashElement("GREEN") == 0);

	mu_assert("Single element not deleted.", 
 		symbolTable[getHashedKey("G")] == NULL);

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
	mu_run_test(test_deleteHashElement_begining);
	mu_run_test(test_deleteHashElement_end);
	mu_run_test(test_deleteHashElement_middle);
	mu_run_test(test_deleteHashElement_single);

	return NULL;
}
