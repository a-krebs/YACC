#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "Hash.h"


//Simple hash function for now. Will replace later
unsigned int getHashedKey(char *string) {
        return (string[0] % TABLE_SIZE);   
}

// int isSameKey(char *key) {
//     int index = simpleHashFunc(key);
    
//     if ( hash[index] != NULL ) {
//         if ( strcmp(hash[index]->key, key) == 0 ) {        
//             return 1;
//         }
//     }   
    
//     return 0;
// }










int isKeyInBucket(char *key) {
        if ( findHashElementByKey(key) != NULL ){
                return 1;
        }

        return 0;
}

struct hashElement *findHashElementByKey(char *key) {
        struct hashElement *element = symbolTable[getHashedKey(key)];

        if ( element == NULL) {
                return NULL;
        }

        if ( isKeysIdentical(element, key) ) {
                return element;
        }

        for (; element->next != NULL; element = element->next) {
                if ( isKeysIdentical(element, key) ) {
                    return element;
                }     
        }   

        if (HASH_DEBUG) {
                printf("Could not find hash element.\n");
        }

        return NULL;
}


/*
 Prints the symbol table to stdout.
*/
void dumpSymbolTable() {
        struct hashElement *element;

        printf("\n\nDUMPING HASH:\n");

        for ( int i = 0; i < TABLE_SIZE; ++i) {
                if ( symbolTable[i] != NULL ) {
                        element = symbolTable[i];

                        printf("Element: %d:\n", i);
                    
                        for (; element != NULL; element = element->next) {
                                printf("\tKey: %s\n", element->key);
                                printf("\tValue: %d\n", element->value);
                                printf("\tElement Pointer: %p\n", element);
                                printf("\tPrev pointer: %p\n", element->prev);
                                printf("\tNext pointer: %p\n\n",element->next);
                        }
                }
        }

        printf("DUMP COMPLETE.\n\n");
}

struct hashElement *createNewElement(char *key, int value) {
        struct hashElement *element = malloc(sizeof(struct hashElement));

        if (element == NULL ) {
                err(1, "Error: Could not create hash element. alloc returned NULL.");
                exit(EXIT_FAILURE);
        }

        // element->key = strdup(key);
        element->key = malloc(strlen(key) + 1);
        strcpy(element->key, key);

        element->value = value;
        element->prev = NULL;
        element->next = NULL;

        return element;
}

void appendToHashBucket(struct hashElement *bucketHead, struct hashElement *newElement) {
    struct hashElement *current = bucketHead;

    for (; current->next != NULL; current = current->next);
    
    current->next = newElement;
    newElement->prev = current;
}

int isKeysIdentical(struct hashElement *element, char *key) {
        if ( element != NULL ) {
                if ( strcmp(element->key, key) == 0 ) {        
                        return 1;
                }
        }   
            
        return 0;
}

int isKeyCollison(char *key) {

        if ( symbolTable[getHashedKey(key)] != NULL) {
                return 1;
        }

        return 0;
}


int createHashElement(char *key, int value) {
        struct hashElement *element;
        int index = getHashedKey(key);

        element = createNewElement(key, value);  

        if ( isKeyCollison(key) ) {

                if ( isKeyInBucket(key) ) {
                        if (HASH_DEBUG) {
                                printf("Error: Hash key already used! Will not reset. Skipping...\n");  
                        }

                        return 1;
                }

                if (HASH_DEBUG) {
                        printf("We have a hash collision. Creating bucket list element...\n"); 
                }

                appendToHashBucket(symbolTable[index], element);          
        }
        else {
                symbolTable[index] = element;     
        }    

        if (HASH_DEBUG) {
                printf("Created hash element with data:\n\tkey: %s\n\tvalue: %d\n", element->key, element->value);  
        }

        return 0;
}