#ifndef hash_H
#define hash_H


/* Macros and const string variable declarations. */
#define TABLE_SIZE 100
#define HASH_DEBUG 0


/* Global variables. */
struct hashElement {
    char *key;
    int value;
    struct Symbol *symbol;
    struct hashElement *prev;
    struct hashElement *next;
};

// struct hashElement *symbolTable[TABLE_SIZE];

struct hash {
    struct hashElement *elements[TABLE_SIZE];
    unsigned int (*hashFunction)();
};


/* Non-C99 compliant function prototypes. */


/* Function declarations. */
unsigned int getHashedKeySimple(char *string);
struct hash *createHash(unsigned int (*hashFunction)(char *));
void destroyHash(struct hash *hash);
int getHashIndex(struct hash *hash, char *key);
struct hashElement *getHashBucketHead(struct hash *hash, char *key);
int isKeyCollison(struct hash *hash, char *key);
int createHashElement(struct hash *hash, char *key, int value);
struct hashElement *findHashElementByKey(struct hash *hash, char *key);
int isKeyInBucket(struct hash *hash, char *key);
struct hashElement *allocHashElement(char *key, int value);
void appendToHashBucket(struct hashElement *bucketHead, struct hashElement *newElement);
int isKeysIdentical(struct hashElement *element, char *key);
struct hashElement *getHashBucketHead(struct hash *hash, char *key);
void dumpHash(struct hash *hash);
int deleteHashElement(struct hash *hash, char *key);
unsigned int getHashedKeySimple(char *string);
unsigned int getHashedKeyNormal(char *string);


#endif