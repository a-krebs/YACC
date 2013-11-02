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

int isKeyCollison(char *key) {

        if ( symbolTable[getHashedKey(key)] != NULL) {
                return 1;
        }

        return 0;
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


// int createHashElement(char *key, int value) {
//     struct hashElement *element;
//     int index = simpleHashFunc(key);

//     if ( isSameKey(key) ) {
        
//         if (HASH_DEBUG) {
//             printf("Error: Hash key already used! Will not reset. Skipping...\n");  
//         }

//         return 1;
//     }

//     element = createNewElement(key, value);  

//     if ( isKeyCollison(key) ) {

//         if (HASH_DEBUG) {
//             printf("We have a hash collision. Creating list element...\n"); 
//         }

//         appendToHashBucket(hash[index], element);          
//     }
//     else {
//         hash[index] = element;     
//     }    

//     if (HASH_DEBUG) {
//         printf("Created hash element with data:\n\tkey: %s\n\tvalue: %d\n", element->key, element->value);  
//     }

//     return 0;
// }