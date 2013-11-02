#ifndef hash_H
#define hash_H


/* Macros and const string variable declarations. */
#define TABLE_SIZE 100
#define HASH_DEBUG 1


/* Global variables. */
struct hashElement {
    char *key;
    int value;
    struct Symbol *symbol;
    struct hashElement *prev;
    struct hashElement *next;
};

struct hashElement *symbolTable[TABLE_SIZE];


/* Non-C99 compliant function prototypes. */


/* Function declarations. */

unsigned int getHashedKey(char *string);
int isKeyInBucket(char *key);
struct hashElement *findHashElementByKey(char *key);
void dumpSymbolTable();
struct hashElement *createNewElement(char *key, int value);
void appendToHashBucket(struct hashElement *bucketHead, struct hashElement *newElement);
int isKeysIdentical(struct hashElement *element, char *key);
int isKeyCollison(char *key);
int createHashElement(char *key, int value);

void destroySymbolTable();
void deleteHashBucket(struct hashElement *current);
void freeHashElement(struct hashElement *element);


#endif