#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "Hash.h"


/*
 TODO:
        - //make function getSizeOfBucket
        - getSizeOfBucket in delete tests
        - need to free what was malloced in createHash
        - test for bounds of hash array 0 and table_size
        - test for keys of incorrect values i.e. =  (is this even allowed in the grammer)
*/



/*
 *
 * Parameters:
 *
 * Return:
 *
 */



/* Determined the hashed value of a key. This is a simpilifed
 * hashing function and should not be used in production. Testing
 * only.
 *
 * Parameters: 
 *              string: string key to be hash
 *
 * Return: Unsigned long of hashed key value.
 */
unsigned int getHashedKeySimple(char *string) {
        return (string[0] % TABLE_SIZE);   
}


/* Determined the hashed value of a key. This is the production
 * function that should be used. 
 *
 * Parameters: 
 *              string: string key to be hash
 *
 * Return: Unsigned long of hashed key value.
 */
unsigned int getHashedKeyNormal(char *string) {
        unsigned long x = 5381;
        int c;

        for ( int i = 0; i < strlen(string); i++ ) {
                c = string[i];
                x = ((x << 5) + x) + c; //x * 33 + c
        }

        return (x % TABLE_SIZE);   
}


/* Gets the index for the hash array for a provided key. This is
 * done by hashing the key and using that as the array index.
 *
 * Parameters:
 *              hash: hash to search in
 *              key: hash key
 *
 * Return: Returns hashed index value
 */
int getHashIndex(struct hash *hash, char *key) {
        return (*(hash->hashFunction))(key);
}


/* Gets the bucket head element for each hash array. 
 *
 * Parameters:
 *              hash: hash to search in
 *              key: hash key
 *
 * Return: Pointer to element at the head of the bucket list in
 *              the hash array. If only one element is in the bucket
 *              returns that one. If no element is in the bucket, returns
 *              null.
 */
struct hashElement *getHashBucketHead(struct hash *hash, char *key) {
        int index = getHashIndex(hash, key);

        return hash->elements[index];
}


/* Determines if key is in the hash bucket.
 *
 * Parameters: 
 *              hash: hash to be looked in
 *              key: hash key
 *
 * Return: Boolean: 1 on in bucket and 0 for not in bucket.
 */
int isKeyInBucket(struct hash *hash, char *key) {
        if ( findHashElementByKey(hash, key) != NULL ){
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


/* Determines if provided key in will cause hash collision
 *
 * Parameters: 
 *              hash: hash to be looked
 *              key: hash key
 *
 * Return: Boolean: 1 on collision and 0 for no collision.
 */
int isKeyCollison(struct hash *hash, char *key) {
        int index = getHashIndex(hash, key);

        if ( hash->elements[index] != NULL) {
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
void destroyHash(struct hash *hash) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
                if ( hash->elements[i] != NULL ) {     
                        deleteHashBucket(hash->elements[i]);
                        hash->elements[i] = NULL;     
                }
        }
}


/* Deletes element in symbole table indicated by the key.
 *
 * Parameters: 
 *              hash: hash that will be deleted from
 *              key: hash key
 *
 * Return: 0 on success
 *         1 on element didn't exist in symbol table
 * 
 * TODO: errors on delete?
 */
int deleteHashElement(struct hash *hash, char *key) {
        struct hashElement *element = findHashElementByKey(hash, key);
        struct hashElement *temp;
        int index = getHashIndex(hash, key);

        if ( element == NULL ) {
                return 1;
        }

        //only element in bucket
        if ( element->prev == NULL && element->next == NULL ) {
                hash->elements[index] = NULL;
                freeHashElement(element);
                return 0;
        }

        //at head of bucket list
        if (element->prev == NULL) {
                temp = element->next;
                hash->elements[index] = temp;
                temp->prev = NULL;

                freeHashElement(element);
                return 0;
        }

        //at the end of bucket list
        if (element->next == NULL) {
                temp = element->prev;
                temp->next = NULL;

                freeHashElement(element);
                return 0;
        }

        //in middle of list
        temp = element->prev;
        temp->next = element->next;
        (temp->next)->prev = temp;

        freeHashElement(element);

        return 0;
}


/* Gets pointer to hash element requested.
 *
 * Parameters: 
 *              hash: hash to be looked in
 *              key: hash key
 *
 * Return: Pointer to struct hashElement
 */
struct hashElement *findHashElementByKey(struct hash *hash, char *key) {
        struct hashElement *element  = getHashBucketHead(hash, key);

        if ( element == NULL) {
                return NULL;
        }

        if ( isKeysIdentical(element, key) ) {
                return element;
        }

        for (; element != NULL; element = element->next) {
                if ( isKeysIdentical(element, key) ) {
                        return element;
                }     
        }   

        if (HASH_DEBUG) {
                printf("Could not find hash element.\n");
        }

        return NULL;
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
// struct hashElement *createNewElement(char *key, int value) {
struct hashElement *allocHashElement(char *key, int value) {    
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
 *              hash: hash for element to be created in
 *              key: hash key
 *              value: int value for testing (WILL BE REMOVED!
 *                      and replaced with real symbol info)
 *
 * Returns: Boolean: 1 on success and 0 and failure.
 * 
 * TODO: add real parameters for when adding symbols to table      
*/
int createHashElement(struct hash *hash, char *key, int value) {
        struct hashElement *element;
        int index = getHashIndex(hash, key);

        element = allocHashElement(key, value);  

        if ( isKeyCollison(hash, key) ) {

                if ( isKeyInBucket(hash, key) ) {
                        if (HASH_DEBUG) {
                                printf("Error: Hash key already used! Will not reset. Skipping...\n");  
                        }

                        return 1;
                }

                if (HASH_DEBUG) {
                        printf("We have a hash collision. Creating bucket list element...\n"); 
                }

                appendToHashBucket(hash->elements[index], element);          
        }
        else {
                hash->elements[index] = element;     
        }    

        if (HASH_DEBUG) {
                printf("Created hash element with data:\n\tkey: %s\n\tvalue: %d\n", element->key, element->value);  
        }

        return 0;
}


/* Creates an hash data structure.
 *
 * Parameters:
 *              hashFunction: pointer to function, this points
 *                      to hashing function
 *
 * Return: createHash: created hash struct
 */
struct hash *createHash(unsigned int (*hashFunction)(char *)) {
        struct hash *hash = malloc(sizeof(struct hash));
        hash->hashFunction = hashFunction;

        for (int i = 0; i < TABLE_SIZE; ++i) {
                hash->elements[i] = NULL;
        }

        return hash;
}


/* Prints the hash to stdout. 
 *
 * Parameters: void
 *
 * Return: void
 *
 * TODO: Add values for the symbol info 
 *              and remove value attribute.
 */
void dumpHash(struct hash *hash) {
        struct hashElement *element;

        printf("\n\nDUMPING HASH:\n");

        for ( int i = 0; i < TABLE_SIZE; ++i) {
                if ( hash->elements[i] != NULL ) {
                        element = hash->elements[i];

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


