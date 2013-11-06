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
#include "Definitions.h"


/*TODO:
	- dump table with something in it.
	- test bound conditions on hash functions
*/ 


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

	mu_assert("Expected initial lex level of 0",
		symbolTable->lexLevel == 0);

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

	mu_assert("Expected initial lex level of 0",
		symbolTable->lexLevel == 0);	

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
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	mu_assert("Collision on empty symbol table.", 
 		isKeyCollison(symbolTable, "blue") == 0);

	createHashElement(symbolTable, "blue", symbol);
	mu_assert("Could not find key collision where one should exist.", 
 		isKeyCollison(symbolTable, "blue") == 1);

	mu_assert("Found key collision where one should not exist.", 
 		isKeyCollison(symbolTable, "green") == 0); 			

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

	return NULL;
}


char *test_createHashElement() {
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	symbol->lvl = 14;
//simple hash function
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	mu_assert("Could not created element in empty table.", 
 		createHashElement(symbolTable, "blue", symbol) == 0);

	mu_assert("Could not create element where bucket collison happened.", 
 		createHashElement(symbolTable, "boo", symbol) == 0);

	mu_assert("Level of symbol not same as current lex level.", 
 		createHashElement(symbolTable, "blue", symbol) == 1);	

	setLexLevel(symbolTable, 14);
	mu_assert("Head of symbol linked list hash same lex level as appending symbol.", 
 		createHashElement(symbolTable, "blue", symbol) == 3);

	struct Symbol *symbol2 =  malloc(sizeof(struct Symbol));
	symbol2->lvl = 1;
	setLexLevel(symbolTable, 1);
	mu_assert("Appending symbol is at a lower lex level then list head.", 
 		createHashElement(symbolTable, "blue", symbol2) == 4);

	symbol2->lvl = 15;
	setLexLevel(symbolTable, 15);
	mu_assert("Could not append symbol where expected.", 
 		createHashElement(symbolTable, "blue", symbol2) == 0);

	// createHashElement(symbolTable, "green", symbol) ;
	// createHashElement(symbolTable, "red", symbol) ;
	// dumpHash(symbolTable);

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

//normal hash function
	symbolTable = createHash(&getHashedKeyNormal);
	mu_assert("Call to createHash does not seg fault.", 1);	

	mu_assert("Could not created element in empty table.", 
 		createHashElement(symbolTable, "blue", symbol) == 0);

	mu_assert("Could not create element where bucket collison happened.", 
 		createHashElement(symbolTable, "boo", symbol) == 0);

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);

	return NULL;
}


char *test_allocHashElement() {
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	struct hashElement *element = allocHashElement("blue", symbol);

	mu_assert("Unable to create hash element, expected NULL.", 
 		element != NULL);

	mu_assert("Incorrect key in hash element.", 
 		strcmp(element->key, "blue") == 0);

	mu_assert("Incorrect value in hash element.", 

 		element->symbol == symbol);

	mu_assert("Hash element not assigned but prev pointing at not NULL.", 
 		element->prev == NULL);

	mu_assert("Hash element not assigned but next pointing at not NULL.", 
 		element->next == NULL);	

	return NULL;
}


char *test_appendToHashBucket() {
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	struct hashElement *element1 = allocHashElement("blue", symbol);
	struct hashElement *element2 = allocHashElement("green", symbol);

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
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	struct hashElement *element = allocHashElement("blue", symbol);

	mu_assert("Keys idenitcal but evaluating to different.", 
 		isKeysIdentical(element, "blue") == 1);

	mu_assert("Keys differnt but evaluating to same.", 
 		isKeysIdentical(element, "green") == 0);	

	return NULL;
}

char *test_findHashElementByKey() {
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));

//simple hash function
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(symbolTable, "blue", symbol);

	mu_assert("Could not find element that should be table.", 
 		findHashElementByKey(symbolTable, "blue") != NULL);

	mu_assert("Found element that should not be table.", 
 		findHashElementByKey(symbolTable, "green") == NULL);

	destroyHash(symbolTable);
	mu_assert("Call to destroyHash does not seg fault.", 1);	

//normal hash function
	symbolTable = createHash(&getHashedKeyNormal);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(symbolTable, "teekkekkke", symbol);

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
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(symbolTable, "blue", symbol);
	createHashElement(symbolTable, "boo", symbol);
	createHashElement(symbolTable, "bobby", symbol);

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
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	struct hash *symbolTable = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(symbolTable, "blue", symbol);
	createHashElement(symbolTable, "boo", symbol);
	createHashElement(symbolTable, "bobby", symbol);

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

 	read(out_pipe[0], buffer, 100);  //read from pipe into buffer 
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
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

   	createHashElement(hash, "GREEN", symbol);
	createHashElement(hash, "bb", symbol);
	createHashElement(hash, "bbb", symbol);
	createHashElement(hash, "bbbb", symbol);
	
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
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

   	createHashElement(hash, "GREEN", symbol);
	createHashElement(hash, "bb", symbol);
	createHashElement(hash, "bbb", symbol);
	createHashElement(hash, "bbbb", symbol);

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
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

   	createHashElement(hash, "GREEN", symbol);
	createHashElement(hash, "bb", symbol);
	createHashElement(hash, "bbb", symbol);
	createHashElement(hash, "bbbb", symbol);

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
// simple hash function	
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
   	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	createHashElement(hash, "GREEN", symbol);
	createHashElement(hash, "bb", symbol);
	createHashElement(hash, "bbb", symbol);
	createHashElement(hash, "bbbb", symbol);

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

	createHashElement(hash, "GREEN", symbol);
	createHashElement(hash, "bb", symbol);
	createHashElement(hash, "bbb", symbol);
	createHashElement(hash, "bbbb", symbol);

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
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
   	struct hash *hash = createHash(&getHashedKeySimple);
	mu_assert("Call to createHash does not seg fault.", 1);	

	mu_assert("Expected empty bucket.",
		getSizeOfBucket(hash, "blue") == 0);

	createHashElement(hash, "blue", symbol);

	mu_assert("Expected bucket size of 1.",
		getSizeOfBucket(hash, "blue") == 1);

	createHashElement(hash, "red", symbol);
	createHashElement(hash, "ruby", symbol);
	createHashElement(hash, "rouse", symbol);
	createHashElement(hash, "rose", symbol);

	mu_assert("Expected bucket size of 4.",
		getSizeOfBucket(hash, "r") == 4);

	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);

//normal hash	
	hash = createHash(&getHashedKeyNormal);
	mu_assert("Call to createHash does not seg fault.", 1);	

	mu_assert("Expected empty bucket.",
		getSizeOfBucket(hash, "blue") == 0);

	createHashElement(hash, "blue", symbol);

	mu_assert("Expected bucket size of 1.",
		getSizeOfBucket(hash, "blue") == 1);

	createHashElement(hash, "red", symbol);
	createHashElement(hash, "rose", symbol);

	mu_assert("Expected bucket size of 0.",
		getSizeOfBucket(hash, "r") == 0);

	mu_assert("Expected bucket size of 4.",
		getSizeOfBucket(hash, "red") == 1);

	destroyHash(hash);
	mu_assert("Call to destroyHash does not seg fault.", 1);
	return NULL;
}


char * test_getLexLevel() {
	struct hash *hash = createHash(&getHashedKeyNormal);
	hash->lexLevel = 5;

	mu_assert("Expected lexical level of 5",
		getCurrentLexLevel(hash) == 5);
	
	mu_assert("Expected lexical level of 5",
		getCurrentLexLevel(hash) != 1);

	return NULL;
}

char * test_setLexLevel() {
	struct hash *hash = createHash(&getHashedKeyNormal);

	setLexLevel(hash, 5);
	mu_assert("Call to setLexLevel seg faulted", 1);

	mu_assert("Expected value of getCurrentLexLevel is 5.",
		getCurrentLexLevel(hash) == 5);

	return NULL;
}


char * test_getSymbolLexLevel() {
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	symbol->lvl = 123;

	mu_assert("Unexpected value in symbol lex level.",
		getSymbolLexLevel(symbol) == 123);	

	return NULL;
}

char * test_getCurrentLexLevel() {
	struct hash *hash = createHash(&getHashedKeyNormal);
	hash->lexLevel = 23;

	mu_assert("Unexpected value in hash lex level.",
		getCurrentLexLevel(hash) == 23);	

	return NULL;
}

char * test_appendToSymbolList() {
	struct Symbol *symbol =  malloc(sizeof(struct Symbol));
	symbol->lvl = 0;
	struct hashElement *element = allocHashElement("weee", symbol);
	element->symbol = symbol;

	symbol = malloc(sizeof(struct Symbol));
	symbol->lvl = 1;

	struct hash *hash = createHash(&getHashedKeySimple);
	hash->lexLevel = 1;

	// printf("Retval: %d\n", appendToSymbolList(hash, element, symbol));
	mu_assert("Could not append symbol.",
		appendToSymbolList(hash, element, symbol) == 0);

	symbol = malloc(sizeof(struct Symbol));
	symbol->lvl = 1;
	hash->lexLevel = 2;

	mu_assert("Could not append, current lex level not same as symbol.",
		appendToSymbolList(hash, element, symbol) == 1);

	symbol = malloc(sizeof(struct Symbol));
	symbol->lvl = 2;
	hash->lexLevel = 2;

	mu_assert("Could not append symbol.",
		appendToSymbolList(hash, element, symbol) == 0);

	symbol = malloc(sizeof(struct Symbol));
	symbol->lvl = 2;

	mu_assert("Could not append, head of symbol list has same lex level as appending symbol.",
		appendToSymbolList(hash, element, symbol) == 3);	

	symbol = malloc(sizeof(struct Symbol));
	symbol->lvl = 1;
	hash->lexLevel = 1;

	mu_assert("Could not append, head of symbol has higher lex level then as appending symbol.",
		appendToSymbolList(hash, element, symbol) == 4);

	return NULL;
}

struct Symbol *createTestSymbol(int lexLevel, char *key) {
	struct Symbol *symbol = malloc(sizeof(struct Symbol));
	symbol->lvl = lexLevel;
	symbol->name = key;
	symbol->typeOriginator = 0;

	return symbol;
}

char *test_findSymbolByHashElement() {
	struct hash *hash = createHash(&getHashedKeySimple);

	struct Symbol *symbol0 = createTestSymbol(0, "charley");
	createHashElement(hash, "charley", symbol0);

	struct Symbol *symbol1 = createTestSymbol(0, "cherry");
	createHashElement(hash, "cherry", symbol1);

	struct Symbol *symbol2 = createTestSymbol(1, "cherry");
	setLexLevel(hash, 1);
	createHashElement(hash, "cherry", symbol2);
	// printf("Retval: %d\n", retval);

	struct Symbol *symbol3 = createTestSymbol(2, "cherry");
	setLexLevel(hash, 2);
	createHashElement(hash, "cherry", symbol3);

	struct Symbol *retSymbol = findSymbolByHashElement(hash, "cherry", 1);
	mu_assert("Symbol found is not correct, test1.",
		retSymbol == symbol2);

	retSymbol = findSymbolByHashElement(hash, "charley", 0);
	mu_assert("Symbol found is not correct, test2.",
		retSymbol == symbol0);	

	retSymbol = findSymbolByHashElement(hash, "charley", 1);
	mu_assert("Symbol found is not correct, test3.",
		retSymbol == NULL);	

	retSymbol = findSymbolByHashElement(hash, "cherry", 0);
	mu_assert("Symbol found is not correct, test4.",
		retSymbol == symbol1);

	retSymbol = findSymbolByHashElement(hash, "cherry", 2);
	mu_assert("Symbol found is not correct, test5.",
		retSymbol == symbol3);

	// dumpHash(hash);

	return NULL;
}


char * test_getLocalSymbol() {
	struct hash *hash = createHash(&getHashedKeySimple);

	struct Symbol *symbol0 = createTestSymbol(0, "charley");
	createHashElement(hash, "charley", symbol0);

	struct Symbol *symbol1 = createTestSymbol(0, "cherry");
	createHashElement(hash, "cherry", symbol1);

	struct Symbol *symbol2 = createTestSymbol(1, "cherry");
	setLexLevel(hash, 1);
	createHashElement(hash, "cherry", symbol2);

	struct Symbol *symbol3 = createTestSymbol(2, "cherry");
	setLexLevel(hash, 2);
	createHashElement(hash, "cherry", symbol3);

	// setLexLevel(hash, 2);
	struct Symbol *retSymbol = getLocalSymbol(hash, "cherry");
	mu_assert("Local symbol found is not correct, test1.",
		retSymbol == symbol3);

	setLexLevel(hash, 1);
	retSymbol = getLocalSymbol(hash, "cherry");
	mu_assert("Local symbol found is not correct, test2.",
		retSymbol == symbol2);	

	setLexLevel(hash, 0);
	retSymbol = getLocalSymbol(hash, "charley");
	mu_assert("Local symbol found is not correct, test3.",
		retSymbol == symbol0);	

	setLexLevel(hash, 3);
	retSymbol = getLocalSymbol(hash, "charley");
	mu_assert("Local symbol found is not correct, test3.",
		retSymbol == NULL);

	// dumpHash(hash);

	return NULL;
}

char * test_getGlobalSymbol() {
	struct hash *hash = createHash(&getHashedKeySimple);

	struct Symbol *symbol0 = createTestSymbol(0, "charley");
	createHashElement(hash, "charley", symbol0);

	struct Symbol *symbol1 = createTestSymbol(0, "cherry");
	createHashElement(hash, "cherry", symbol1);

	struct Symbol *symbol2 = createTestSymbol(1, "cherry");
	setLexLevel(hash, 1);
	createHashElement(hash, "cherry", symbol2);

	struct Symbol *symbol3 = createTestSymbol(2, "cherry");
	setLexLevel(hash, 2);
	createHashElement(hash, "cherry", symbol3);

	dumpHash(hash);

	struct Symbol *retSymbol = getGlobalSymbol(hash, "cherry");
	mu_assert("Global symbol found is not correct, test1.",
		retSymbol == symbol3);

	retSymbol = getGlobalSymbol(hash, "charley");
	mu_assert("Global symbol found is not correct, test2.",
		retSymbol == symbol0);	

	struct Symbol *symbol4 = createTestSymbol(2, "ruby");
	createHashElement(hash, "ruby", symbol4);

	retSymbol = getGlobalSymbol(hash, "ruby");
	mu_assert("Global symbol found is not correct, test3.",
		retSymbol == symbol4);	

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
	mu_run_test(test_getLexLevel); 
	mu_run_test(test_setLexLevel);
	mu_run_test(test_getSymbolLexLevel);
	mu_run_test(test_getCurrentLexLevel);
	mu_run_test(test_appendToSymbolList);
	mu_run_test(test_findSymbolByHashElement);
	mu_run_test(test_getLocalSymbol);
	mu_run_test(test_getGlobalSymbol);

	return NULL;
}
