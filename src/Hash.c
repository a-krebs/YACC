#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "Hash.h"


/*
 *
 * Parameters:
 *
 * Return:
 *
 */


//Simple hash function for now. Will replace later
// unsigned int getHashedKey(char *string) {
//         return (string[0] % TABLE_SIZE);   
// }

unsigned int getHashedKey(char *string) {
        unsigned long x = 5381;
        int c;

        for ( int i = 0; i < strlen(string); i++ ) {
                c = string[i];
                x = ((x << 5) + x) + c; //x * 33 + c
        }

        return (x % TABLE_SIZE - 1);   
}



/* Determines if key is in the hash bucket.
 *
 * Parameters: 
 *              key: hash key
 *
 * Return: Boolean: 1 on in bucket and 0 for not in bucket.
 */
int isKeyInBucket(char *key) {
        if ( findHashElementByKey(key) != NULL ){
                return 1;
        }

        return 0;
}


/* Determines if provided hash element has same key as parameter.
 *
 * Parameters: 
 *              element: hash element to compare against
 *              key: hash key to compare against
 *
 * Return: Boolean: 1 on keys same and 0 for differnt keys.
 */
int isKeysIdentical(struct hashElement *element, char *key) {
        if ( element != NULL ) {
                if ( strcmp(element->key, key) == 0 ) {        
                        return 1;
                }
        }   
            
        return 0;
}


/* Determines if provided in will cause hash collision
 *
 * Parameters: 
 *              key: hash key
 *
 * Return: Boolean: 1 on collision and 0 for no collision.
 */
int isKeyCollison(char *key) {
        if ( symbolTable[getHashedKey(key)] != NULL) {
                return 1;
        }

        return 0;
}


/* Frees memory to members of hashElement struct
 *
 * Parameters: 
 *              element: struct to be freed
 *
 * Return: void
 *
 * TODO: Add free calls for any symbol additions
 */
void freeHashElement(struct hashElement *element) {
        free(element->key);
        free(element);
}


/* Recursive function to free memory in a linked list.
 *
 * Parameters: 
 *              current: current memember in linked list recursing through
 *
 * Return: void
 */
void deleteHashBucket(struct hashElement *current) {
        if ( current->next != NULL ) {
                deleteHashBucket(current->next);
        }

        freeHashElement(current);
}


/* Destroys the symbol table for program end. Frees and alloced memory.
 *
 * Parameters: void
 *
 * Return: void
 */
void destroySymbolTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
                if ( symbolTable[i] != NULL ) {     
                        deleteHashBucket(symbolTable[i]);
                        symbolTable[i] = NULL;     
                }
        }
}


/* Gets pointer to hash element requested
 *
 * Parameters: 
 *              key: hash key
 *
 * Return: Pointer to struct hashElement
 */
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


/* Prints the symbol table to stdout. 
 *
 * Parameters: void
 *
 * Return: void
 *
 * TODO: Add values for the symbol info 
 *              and remove value attribute.
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


/* Creates and allocs memory for a struct hashElement.
 *
 * Parameters: 
 *              key: hash key
 *              value: int value for testing (WILL BE REMOVED!
 *                      and replaced with real symbol info)
 *
 * Return: pointer to a newly create struct hashElement.
 *
 * TODO: add real parameters for when adding symbols to table   
 *              - add symbol null pointer
 */
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


/* Appends the hashElement pointed to by newElement to the 
 * end of the linked list pointed to by bucketHead
 *
 * Parameters:
 *              bucketHead: head of the hash bucket linked list
 *              newElement: new elment to append
 *
 * Return: void
 *
 */
void appendToHashBucket(struct hashElement *bucketHead, struct hashElement *newElement) {
    struct hashElement *current = bucketHead;

    for (; current->next != NULL; current = current->next);
    
    current->next = newElement;
    newElement->prev = current;
}


/* Creates an entry in the symbol table for the key supplied.
 *      
 * Parameters: 
 *              key: hash key
 *              value: int value for testing (WILL BE REMOVED!
 *                      and replaced with real symbol info)
 *
 * Returns: Boolean: 1 on success and 0 and failure.
 * 
 * TODO: add real parameters for when adding symbols to table      
*/
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