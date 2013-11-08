#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <time.h> 
#include <sys/time.h>

#include "Hash.h"
#include "Definitions.h"



/*
 TODO:
        - need to free what was malloced in createHash
        - test for bounds of hash array 0 and table_size
        - test for keys of incorrect values i.e. =  (is this even allowed in the grammer)
        - need to free symbol member when deleting
        - for createNameForAnonType need to figure out the proper error
        
*/



/*
 *
 * Parameters:
 *
 * Return:
 *
 */





/* FOR TESTING USE ONLY. DO NOT USE!!!!!!!!
 * Sets the current lexical level of the hash. This is 
 * saved in the symbol table hash struct.
 *
 * Parameters:
 *              hash: hash struct with levLevel member
 *              lexLevel: number to update the lex level with
 *
 * Return: void
 */
void setLexLevel(struct hash *hash, int lexLevel) {
        hash->lexLevel = lexLevel;
}


/* 
 * Increments the current lexical level of the hash. This is 
 * saved in the symbol table hash struct.
 *
 * Parameters:
 *              hash: hash struct with levLevel member
 *
 * Return: 0 successs
 *         1 failure
 */
int incrementLexLevel(struct hash *hash) {
        if (hash == NULL) {
                return 1;
        }

        hash->lexLevel = hash->lexLevel + 1;
        return 0;        
}


/*
 * Decrements the current lexical level of the hash. This is 
 * saved in the symbol table hash struct.
 *
 * Parameters:
 *              hash: hash struct with levLevel member
 *
 * Return: 0 successs
 *         1 failure
 */
int decrementLexLevel(struct hash *hash) {
        if (hash == NULL) {
                return 1;
        }

        if (hash->lexLevel == 0) {
                return 1;
        }

        hash->lexLevel = hash->lexLevel - 1;
        return 0;
}


/* Gets the lexical level of the passed symbol.
 *
 * Parameters:
 *              symbol: symbol to be searched
 *
 * Return: symbol's lexical level
 */
int getSymbolLexLevel(struct Symbol *symbol) {
        return symbol->lvl;
}

/* Gets the current lexical level of the hash. This is 
 * saved in the symbol table hash struct.
 *
 * Parameters:
 *              hash: hash struct with levLevel member
 *
 * Return: Current lexical level of hash.
 */
int getCurrentLexLevel(struct hash *hash) {
        return hash->lexLevel;
}


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
		if ( i >= TABLE_SIZE ) {
			break;
		}

                c = string[i];
                x = ((x << 5) + x) + c; //x * 33 + c
        }

        return (x % TABLE_SIZE);   
}


/* Gets length of the symbol linked list pointed to by element
 *
 * Parameters: 
 *              element: struct hashElement holding pointer to
 *                      head of list
 *
 * Return: -1 on passed element NULL
 *         0 when passed element pointers to NULL
 *         everything else is count of list length
 */
int getLengthOfSymbolList(struct hashElement *element) {
        struct Symbol *symbol;
        int count = 0;

        if (element == NULL) {
                return -1;
        }

        symbol = element->symbol;

        for (; symbol != NULL; symbol = symbol->next) {
                count++;
        }

        return count;
}


/* Checks to see if the supplied symbol is the only one in the 
 * linked list of symbols and that element is pointing to it.
 *
 * Parameters: 
 *              element: struct hashElement holding pointer to
 *                      head of list
 *              symbol: symbol to search against
 *
 * Return: -1 on passed element NULL
 *         0 when passed element pointers to NULL
 *         everything else is count of list length
 */
int isOnlySymbolInList(struct hashElement *element, struct Symbol *symbol) {
        if ( (getLengthOfSymbolList(element) == 1) 
                && (element->symbol == symbol) ) {
                return 1;
        }

        return 0;
}


/* Determined the number of hash elements in the bucket. i.e. lenghth
 * of linked list.
 *
 * Parameters: 
 *              hash: hash where bucket resides
 *              key: hash key
 *
 * Return: Count of elements in hash bucket
 */
int getSizeOfBucket(struct hash *hash, char *key) {
        struct hashElement *element = getHashBucketHead(hash, key);
        int count = 0;

        for (; element != NULL; element = element->next) {
                count++;
        }

        return count;
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
 *              symbolPtr: pointer to symbol struct holding
 *                      symbol info
 *
 * Return: pointer to a newly create struct hashElement.
 *
 */
struct hashElement *allocHashElement(char *key, struct Symbol *symbolPtr) {    
        struct hashElement *element = malloc(sizeof(struct hashElement));

        if (element == NULL ) {
                err(1, "Error: Could not create hash element. alloc returned NULL.");
                exit(EXIT_FAILURE);
        }

        element->key = malloc(strlen(key) + 1);
        strcpy(element->key, key);

        element->symbol = symbolPtr;
        element->prev = NULL;
        element->next = NULL;

        return element;
}


/* Appends onto the symbol linked list of an element in the hash.
 *      
 * Parameters: 
 *              hash: hash for element to be created in
 *              element: pointer to hashElement
 *              symbol: pointer to symbol struct to saved in 
 *                  hash element.
 *
 * Return: 0 on success
 *         1 current lex level and symbol's lex level differ
 *         2 element on hash table has symbol set to NULL
 *         3 element's symbol list head lex level same as symbol's
 *         4 symbol's lex level lower than element's symbol list head
*/
int appendToSymbolList(struct hash *hash, struct hashElement *element, struct Symbol *symbol) {
        int symbolLexLevel = getSymbolLexLevel(symbol);

        if (symbolLexLevel != getCurrentLexLevel(hash) ) {
                if (HASH_DEBUG) { printf("The current lex level is not the same as the passed symbol.\n"); }
                return 1;
        }

        struct Symbol *elementSymbolListHead = element->symbol;
        int listHeadLexLevel = getSymbolLexLevel(elementSymbolListHead);

        if (elementSymbolListHead == NULL) {
                if (HASH_DEBUG) { printf("Element's symbol pointer points to NULL.\n"); }
                return 2;
        }

        if ( symbolLexLevel == listHeadLexLevel ) {
                if (HASH_DEBUG) { printf("Element's symbol list head equal to passed symbol lex level.\n"); }
                return 3;
        }

        if ( symbolLexLevel < listHeadLexLevel ) {
                if (HASH_DEBUG) { printf("Element's symbol list head higner than passed symbol lex level.\n"); }
                return 4;
        }

        symbol->next = elementSymbolListHead;
        element->symbol = symbol;

        return 0;
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


char *createNameForAnonType(struct Symbol *symbol) {
        char *name = NULL;
        struct timeval tv;
        double tim;
        int size;

        if (symbol->kind != TYPE_KIND) {
                err(1, "Symbol is not TYPE_KIND. Cannot generate name.");
                exit(EXIT_FAILURE);
        }

        if ( symbol->kindPtr.TypeKind->type != ARRAY_T
                && symbol->kindPtr.TypeKind->type != SUBRANGE_T
                && symbol->kindPtr.TypeKind->type != RECORD_T
                && symbol->kindPtr.TypeKind->type != SCALAR_T ) {
                        err(1, "Symbol is not ARRAY_T, SUBRANGE_T, RECORD_T, OR SCALAR_T. Cannot generate name.");
                        exit(EXIT_FAILURE);
        }

        gettimeofday(&tv, NULL);
        tim = tv.tv_sec + ( tv.tv_usec / 1000000.0 );

        size = snprintf(NULL, 0, "%f", tim);
        name = malloc(size + 1);
        sprintf(name, "%f", tim);

        symbol->name = name;

        return name;
}


/* Creates an entry in the symbol table for the key supplied.
 *      
 * Parameters: 
 *              hash: hash for element to be created in
 *              key: hash key
 *              symbol: pointer to symbol struct to saved in 
 *                  hash element.
 *
 * Returns: 0 on success 
 *         1 current lex level and symbol's lex level differ
 *         2 element on hash table has symbol set to NULL
 *         3 element's symbol list head lex level same as symbol's
 *         4 symbol's lex level lower than element's symbol list head    
 *         5 could not create a name for null key
*/
int createHashElement(struct hash *hash, char *key, struct Symbol *symbol) {
        struct hashElement *element;
        int index;
        int retval;   

        if ( key == NULL ) {
                key = createNameForAnonType(symbol);
                if (key == NULL) {
                        return 5;
                }
                //printf("Hashed value %d\n", getHashIndex(hash, key));
        }

        index = getHashIndex(hash, key);      
        
        //check to see if a element in the table already exists with same key name
        if ( isKeyInBucket(hash, key) ) {
                element = findHashElementByKey(hash, key);

                retval = appendToSymbolList(hash, element, symbol);
                return retval;
        }

        element = allocHashElement(key, symbol); 

        //check to see if the key will create a hash collison
        if ( isKeyCollison(hash, key) ) {
                if ( HASH_DEBUG ) { printf("Key %s causes collision. Appending to bucket.\n", key); } 

                appendToHashBucket(hash->elements[index], element);
        }
        else {
               hash->elements[index] = element;  
        }

        if (HASH_DEBUG) {
                printf("Created hash element with data:\n\tkey: %s\n\tsymbol pointer: %p\n", element->key, element->symbol);  
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
        hash->lexLevel = 0;             //default value

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
 */
void dumpHash(struct hash *hash) {
        struct hashElement *element;
        struct Symbol *symbol;

        printf("\n\nDUMPING HASH:\n");

        for ( int i = 0; i < TABLE_SIZE; ++i) {
                if ( hash->elements[i] != NULL ) {
                        element = hash->elements[i];

                        printf("Element: %d:\n", i);
                    
                        for (; element != NULL; element = element->next) {
                                printf("\tSelf Pointer: %p\n", element);
                                printf("\tKey: %s\n", element->key);
                                printf("\tSymbol pointer: %p\n", element->symbol);
                                printf("\tPrev pointer: %p\n", element->prev);
                                printf("\tNext pointer: %p\n",element->next); 

                                printf("\t\tSymbol INFO:\n"); 
                                symbol = element->symbol;

                                for (; symbol != NULL; symbol = symbol->next) {
                                        printf("\t\t\tName: %s\n", symbol->name);
                                        printf("\t\t\tLex Level: %d\n", symbol->lvl);
                                        printf("\t\t\tTypeOriginator: %d\n\n", symbol->typeOriginator);
                                }

                                printf("\n");
                        }                        
                }
        }

        printf("DUMP COMPLETE.\n\n");
}


/* Gets pointer to symbol requested.
 *
 * Parameters: 
 *              hash: hash to be looked in
 *              key: hash key
 *              lexLevel: requested level in symbol
 *
 * Return: Pointer to struct symbol
 */
struct Symbol *findSymbolByLexLevel(struct hash *hash, char *key, int lexLevel) {
        struct Symbol *symbol;
        struct hashElement *element = findHashElementByKey(hash, key);

        if ( element == NULL ) {
                if (HASH_DEBUG) { printf("Could not find element.\n"); }
                return NULL;
        }

        symbol = element->symbol;

        if ( symbol == NULL ) {
                if (HASH_DEBUG) { printf("Pointer to symbol in element is null.\n"); }
                return NULL;
        }        

        for (; symbol != NULL; symbol = symbol->next) {
                if ( getSymbolLexLevel(symbol) == lexLevel ) {
                        return symbol;
                }
        }

        return NULL;
}


/* Gets pointer to request symbol at the local lexical level.
 *
 * Parameters: 
 *              hash: hash to be looked in
 *              key: hash key
 *
 * Return: Pointer to struct symbol
 */
struct Symbol *getLocalSymbol(struct hash *hash, char *key) {
        int lexLevel = getCurrentLexLevel(hash);

        return findSymbolByLexLevel(hash, key, lexLevel);
}


/* Gets pointer to request symbol at the global lexical level.
 *
 * Parameters: 
 *              hash: hash to be looked in
 *              key: hash key
 *
 * Return: Pointer to struct symbol
 */
struct Symbol *getGlobalSymbol(struct hash *hash, char *key) {
        int lexLevel = getCurrentLexLevel(hash);
        struct Symbol *symbol;

        for (; lexLevel >= 0; lexLevel--) {
                symbol = findSymbolByLexLevel(hash, key, lexLevel);

                if ( symbol != NULL ) {
                        return symbol;
                }
        }

        return NULL;
}


/* Finds the requested symbol and deletes it struct at the requested
 * lexical level. If symbol is is alone in hashElemet, will delete
 * whole hash element.
 *
 * Parameters: 
 *              hash: hash to be looked in
 *              key: hash key
 *              lexLevel: lexical level of symbol to  be deleted
 *
 * Return: 0 on success
 *         1 on could not find element to delete
 *         2 attempted to delete value not at head of list
*/
int deleteSymbolAtLexLevel(struct hash *hash, char *key, int lexLevel) {
        struct Symbol *symbol = findSymbolByLexLevel(hash, key, lexLevel);
        struct hashElement *element = findHashElementByKey(hash, key);
        int retval;

        //check if symobol valid
        if ( symbol == NULL ) {        
                if (HASH_DEBUG) { printf("Could not delete symbol.\n"); }
                return 1;
        }

        //only item in list
        if ( isOnlySymbolInList(element, symbol) ) {
                retval = deleteHashElement(hash, key);
                return retval;
        }

        //at head of list
        if ( element->symbol == symbol ) {
                element->symbol = symbol->next;
                //NEED TO FREE SYMBOL;
                return 0;
        }

        if (HASH_DEBUG) {
                printf("Symbol request to be delete not at head of symbol list.\n");
        }

        return 2;
}


/* Pops all the symbols in the symbol table with the current lexical
 * level. Then decrements the lexical level by one.
 *
 * Parameters: 
 *              hash: hash to pop symbols from
 *
 * Return: 0 on success
 *         1 on could not find element to delete
*/
 int popLexLevel(struct hash *hash) {
        struct hashElement *element;
        struct Symbol *symbol;
        int lexLevel = getCurrentLexLevel(hash);

        if (lexLevel == 0) {
                if (HASH_DEBUG) { printf("Cannot pop lexical levels when already at level 0.\n");}
                return 1;
        }

        for (int i = 0; i < TABLE_SIZE; ++i) {
                element = hash->elements[i];

                for(; element != NULL; element = element->next) {
                        symbol = findSymbolByLexLevel(hash, element->key, lexLevel);

                        if (symbol != NULL) {
                                if (deleteSymbolAtLexLevel(hash, element->key, lexLevel) != 0) {
                                        return 1;
                                }
                        }
                }
        }

        decrementLexLevel(hash);

        return 0;
}
