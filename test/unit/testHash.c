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
	- change tests once real hash functions is created
	- test bound conditions on hash functions
*/ 



// // char *test_() {
// // /*test 1: .*/
// // 	mu_assert(".", 
// //  		);

// // 	return NULL;
// // }



char *test_getHashedKeySimple() {
	//with table size of 1000
	mu_assert("Hash function calulated '0' incorrectly.",
		getHashedKeySimple("0") == 48);

	mu_assert("Hash function calulated 'h' incorrectly.",
		getHashedKeySimple("h") == 104);

	mu_assert("Hash function calulated 'J' incorrectly.",
		getHashedKeySimple("J") == 74);

	mu_assert("Hash function calulated 'K' incorrectly.",
		getHashedKeySimple("K") != 2);

        return NULL;
}

char *test_getHashedKeyNormal() {       
	//with table size of 1000
	mu_assert("Hash function calulated 'b' incorrectly.",
		getHashedKeyNormal("b") == 671);

	mu_assert("Hash function calulated 'Joe' incorrectly.",
		getHashedKeyNormal("Joe") == 347);

        return NULL;
}

char *test_destroyHash() {
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	for (int i = 0; i < TABLE_SIZE; ++i) {
		mu_assert("destroyed bucket does not equal NULL.", 
			symbolTable->elements[i] == NULL);
	}	

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);		

	return NULL;
}

char *test_createHash() {
//simple hash function
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	int index = (*(symbolTable->hashFunction))("b");
	mu_assert("Hash function does not caluculate expected value for key 'b'.",
		index == 98);
	
	index = (*(symbolTable->hashFunction))("a");
	mu_assert("Hash function does not caluculate expected value for key 'a'.",
		index == 97);	

	for (int i = 0; i < TABLE_SIZE; ++i) {
		mu_assert("Empty table bucket does not equal NULL.", 
			symbolTable->elements[i] == NULL);
	}

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);		

//normal hash function	
	symbolTable = createHash(&getHashedKeyNormal);
	mu_assert("Call to createHash does not seg fault.", 1);	

	index = (*(symbolTable->hashFunction))("A");
	mu_assert("Hash function does not caluculate expected value for key 'A'.",
		index == 638);
	
	index = (*(symbolTable->hashFunction))("aaa");
	mu_assert("Hash function does not caluculate expected value for key 'a'.",
		index == 928);	

	for (int i = 0; i < TABLE_SIZE; ++i) {
		mu_assert("Empty table bucket does not equal NULL.", 
			symbolTable->elements[i] == NULL);
	}

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	
	return NULL;
}

char *test_getHashIndex() {
//simple hash function	
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	int index = getHashIndex(symbolTable, "b");
	mu_assert("getHashIndex does not return expected value on key 'b'", 
		index == 98);

	index = getHashIndex(symbolTable, "W");
	mu_assert("getHashIndex does not return expected value on key 'b'", 
		index == 87);

	index = getHashIndex(symbolTable, "=");
	mu_assert("getHashIndex does not return expected value on key 'b'", 
		index == 61);			

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

//normal hash function	
	symbolTable = createHash(&getHashedKeyNormal);
	mu_assert("Call to createHash does not seg fault.", 1);	

	index = getHashIndex(symbolTable, "b");
	mu_assert("getHashIndex does not return expected value on key 'b'", 
		index == 671);

	index = getHashIndex(symbolTable, "W");
	mu_assert("getHashIndex does not return expected value on key 'b'", 
		index == 660);			

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

	return NULL;
}


//not testing on normal hash to hard to find collisons
char *test_isKeyCollison() {
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	mu_assert("Collision on empty symbol table.", 
 		isKeyCollison(symbolTable, "blue") == 0);

	createHashElement(symbolTable, "blue", 456666);
	mu_assert("Could not find key collision where one should exist.", 
 		isKeyCollison(symbolTable, "blue") == 1);

	mu_assert("Found key collision where one should not exist.", 
 		isKeyCollison(symbolTable, "green") == 0); 			

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

	return NULL;
}


char *test_createHashElement() {
//simple hash function
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	mu_assert("Could not created element in empty table.", 
 		createHashElement(symbolTable, "blue", 123) == 0);

	mu_assert("Could not create element where bucket collison happened.", 
 		createHashElement(symbolTable, "boo", 123) == 0);

	mu_assert("Over written hash value.", 
 		createHashElement(symbolTable, "blue", 456) == 1);	

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

//normal hash function
	symbolTable = createHash(&getHashedKeyNormal);
	mu_assert("Call to createHash does not seg fault.", 1);	

	mu_assert("Could not created element in empty table.", 
 		createHashElement(symbolTable, "blue", 123) == 0);

	mu_assert("Could not create element where bucket collison happened.", 
 		createHashElement(symbolTable, "boo", 123) == 0);

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);

	return NULL;
}


char *test_allocHashElement() {
	struct hashElement *element = allocHashElement("blue", 123);

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


char *test_appendToHashBucket() {
	struct hashElement *element1 = allocHashElement("blue", 123);
	struct hashElement *element2 = allocHashElement("green", 456);

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

char *test_isKeysIdentical() {
	struct hashElement *element = allocHashElement("blue", 123);

	mu_assert("Keys idenitcal but evaluating to different.", 
 		isKeysIdentical(element, "blue") == 1);

	mu_assert("Keys differnt but evaluating to same.", 
 		isKeysIdentical(element, "green") == 0);	

	return NULL;
}

char *test_findHashElementByKey() {
//simple hash function
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(symbolTable, "blue", 123);

	mu_assert("Could not find element that should be table.", 
 		findHashElementByKey(symbolTable, "blue") != NULL);

	mu_assert("Found element that should not be table.", 
 		findHashElementByKey(symbolTable, "green") == NULL);

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

//normal hash function
	symbolTable = createHash(&getHashedKeyNormal);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(symbolTable, "teekkekkke", 123);

	mu_assert("Could not find element that should be table.", 
 		findHashElementByKey(symbolTable, "teekkekkke") != NULL);

	mu_assert("Found element that should not be table.", 
 		findHashElementByKey(symbolTable, "green") == NULL);

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);

	return NULL;
}


//can't test on normal hash function. can't find collisons
char *test_isKeyInBucket() {
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(symbolTable, "blue", 123);
	createHashElement(symbolTable, "boo", 23456);
	createHashElement(symbolTable, "bobby", 123);

	mu_assert("Could not find expected key 'blue' in bucket.", 
		isKeyInBucket(symbolTable, "blue") == 1 );		

	mu_assert("Could not find expected key 'blue' in bucket.", 
		isKeyInBucket(symbolTable, "bobby") == 1 );			

	mu_assert("Could not find expected key 'blue' in bucket.", 
		isKeyInBucket(symbolTable, "gree") == 0 );		

	mu_assert("Could not find expected key 'blue' in bucket.", 
		isKeyInBucket(symbolTable, "boo") == 1 );		
	
	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

	return NULL;
}

//can't test on normal hash function. can't find collisons
char *test_getHashBucketHead() {
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(symbolTable, "blue", 123);
	createHashElement(symbolTable, "boo", 23456);
	createHashElement(symbolTable, "bobby", 123);

	mu_assert("Returned pointer when NULL was expected in getHashBucketHead.", 
		getHashBucketHead(symbolTable, "gree") == NULL );

	mu_assert("Returned bucket head is incorrect.", 
		getHashBucketHead(symbolTable, "b") == findHashElementByKey(symbolTable, "blue") );

	mu_assert("Returned bucket head is incorrect.", 
		getHashBucketHead(symbolTable, "bobby") != findHashElementByKey(symbolTable, "bobby") );
	
	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

	return NULL;
}

char *test_dumpHash() {
	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	dumpHash(hash);
	mu_assert("Hash dump seg faults.", 1);

/*test 2: Copy stdout to to buffer and compare out of empty symbol table.*/
	char buffer[100] = {0};
	int out_pipe[2];
	int saved_stdout = dup(STDOUT_FILENO); /* save stdout for display later */

	pipe(out_pipe);						/* make a pipe */
	dup2(out_pipe[1], STDOUT_FILENO);   /* redirect stdout to the pipe */
	close(out_pipe[1]);

 	dumpHash(hash);		/* anything sent to printf should now go down the pipe */
 	fflush(stdout);

 	read(out_pipe[0], buffer, 100);  /*read from pipe into buffer */
 	dup2(saved_stdout, STDOUT_FILENO);  /* reconnect stdout for testing */

 	char expectedOutput[33] = "\n\nDUMPING HASH:\nDUMP COMPLETE.\n\n";

	mu_assert("Hash dumper gives unexpected output on empty hash.", 
 		strcmp(expectedOutput, buffer) == 0);	
	
	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

	hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	// createHashElement(hash, "blue", 123);
	// createHashElement(hash, "boo", 23456);
	// createHashElement(hash, "bobby", 123);

	// dumpHash(hash);

	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);

	return NULL;
}

//can't test on normal hash function. can't find collisons
char *test_deleteHashElement_begining() {
	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

   	createHashElement(hash, "GREEN", 7);
	createHashElement(hash, "bb", 6);
	createHashElement(hash, "bbb", 888);
	createHashElement(hash, "bbbb", 753);
	
	struct hashElement *element = findHashElementByKey(hash, "bb");
	struct hashElement *newHead = element->next;

	int index  = getHashIndex(hash, "b");
	mu_assert("unexpected element at head of bucket list.", 
 		hash->elements[index] == element);

	mu_assert("Delete function did not remove begining element.", 
 		deleteHashElement(hash, "bb") == 0);

	mu_assert("Begining element not deleted.", 
 		hash->elements[index] == newHead);

	mu_assert("Did not delete front of list propertly.", 
 		newHead->prev == NULL);

	mu_assert("Resulting bucket should have more than one element.", 
 		newHead->next != NULL);	

	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);

	return NULL;
}

//can't test on normal hash function. can't find collisons
char *test_deleteHashElement_end() {
	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

   	createHashElement(hash, "GREEN", 7);
	createHashElement(hash, "bb", 6);
	createHashElement(hash, "bbb", 888);
	createHashElement(hash, "bbbb", 753);

	struct hashElement *element = findHashElementByKey(hash, "bbbb");
	struct hashElement *newTail = element->prev;

	mu_assert("unexpected element at end of list.", 
 		element->next == NULL);

	mu_assert("Delete function did not remove end element.", 
 		deleteHashElement(hash, "bbbb") == 0);

	mu_assert("End element not deleted.", 
 		newTail->next == NULL);

	mu_assert("Did not delete end of list propertly.", 
 		newTail->prev != NULL);

	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);

	return NULL;
}

//can't test on normal hash function. can't find collisons
char *test_deleteHashElement_middle() {
	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

   	createHashElement(hash, "GREEN", 7);
	createHashElement(hash, "bb", 6);
	createHashElement(hash, "bbb", 888);
	createHashElement(hash, "bbbb", 753);

	struct hashElement *element = findHashElementByKey(hash, "bbb");
	struct hashElement *head = findHashElementByKey(hash, "bb");
	struct hashElement *tail = findHashElementByKey(hash, "bbbb");

	mu_assert("unexpected element after head.", 
 		head->next == element);

	mu_assert("unexpected element before tail.", 
 		tail->prev == element);

	mu_assert("Delete function did not remove middle element.", 
 		deleteHashElement(hash, "bbb") == 0);

	mu_assert("Did not reset next in list propertly.", 
 		head->next == tail);

	mu_assert("Did not reset prev in list propertly", 
 		tail->prev == head);

	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);

	return NULL;
}

char *test_deleteHashElement_single() {
//simple hash function	
   	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(hash, "GREEN", 7);
	createHashElement(hash, "bb", 6);
	createHashElement(hash, "bbb", 888);
	createHashElement(hash, "bbbb", 753);

	int index  = getHashIndex(hash, "G");
	struct hashElement *element = findHashElementByKey(hash, "GREEN");

	mu_assert("unexpected element at in single bucket list.", 
 		hash->elements[index] == element);

	mu_assert("Delete function did not remove single bucket element.", 
 		deleteHashElement(hash, "GREEN") == 0);

	mu_assert("Single element not deleted.", 
 		hash->elements[index] == NULL);

	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);

//normal hash function
	hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(hash, "GREEN", 7);
	createHashElement(hash, "bb", 6);
	createHashElement(hash, "bbb", 888);
	createHashElement(hash, "bbbb", 753);

	index  = getHashIndex(hash, "G");
	element = findHashElementByKey(hash, "GREEN");

	mu_assert("unexpected element at in single bucket list.", 
 		hash->elements[index] == element);

	mu_assert("Delete function did not remove single bucket element.", 
 		deleteHashElement(hash, "GREEN") == 0);

	mu_assert("Single element not deleted.", 
 		hash->elements[index] == NULL);

	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);

	return NULL;
}


char *test_getSizeOfBucket() {
//simple hash	
   	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	mu_assert("Expected empty bucket.",
		getSizeOfBucket(hash, "blue") == 0);

	createHashElement(hash, "blue", 58);

	mu_assert("Expected bucket size of 1.",
		getSizeOfBucket(hash, "blue") == 1);

	createHashElement(hash, "red", 58);
	createHashElement(hash, "ruby", 58);
	createHashElement(hash, "rouse", 58);
	createHashElement(hash, "rose", 58);

	mu_assert("Expected bucket size of 4.",
		getSizeOfBucket(hash, "r") == 4);

	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);

//normal hash	
	hash = createHash(&getHashedKeyNormal);
	mu_assert("Call to createHash does not seg fault.", 1);	

	mu_assert("Expected empty bucket.",
		getSizeOfBucket(hash, "blue") == 0);

	createHashElement(hash, "blue", 58);

	mu_assert("Expected bucket size of 1.",
		getSizeOfBucket(hash, "blue") == 1);

	createHashElement(hash, "red", 58);
	createHashElement(hash, "rose", 58);

	mu_assert("Expected bucket size of 0.",
		getSizeOfBucket(hash, "r") == 0);

	mu_assert("Expected bucket size of 4.",
		getSizeOfBucket(hash, "red") == 1);

	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);
	return NULL;
}


char * test_all_Hash() {
	// mu_run_test(test_getHashedKey);
	
	mu_run_test(test_createHash);
	mu_run_test(test_destroyHash);
	mu_run_test(test_getHashIndex);
	mu_run_test(test_isKeyCollison);
	mu_run_test(test_allocHashElement);
	mu_run_test(test_appendToHashBucket);
	mu_run_test(test_isKeysIdentical);
	mu_run_test(test_createHashElement);
	mu_run_test(test_findHashElementByKey);
	mu_run_test(test_isKeyInBucket);
	mu_run_test(test_getHashBucketHead);
	// mu_run_test(test_dumpHash);		
	mu_run_test(test_deleteHashElement_begining);
	mu_run_test(test_deleteHashElement_end);
	mu_run_test(test_deleteHashElement_middle);
	mu_run_test(test_deleteHashElement_single);
	mu_run_test(test_getHashedKeySimple);
	mu_run_test(test_getHashedKeyNormal);
	mu_run_test(test_getSizeOfBucket);

	return NULL;
}
