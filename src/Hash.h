#ifndef hash_H
#define hash_H


/* Macros and const string variable declarations. */
#define TABLE_SIZE 100
#define HASH_DEBUG 1


/* Global variables. */
struct hashElement {
    char *key;
    int value;
    struct hashElement *prev;
    struct hashElement *next;
};

struct hashElement *symbolTable[TABLE_SIZE];


/* Non-C99 compliant function prototypes. */


/* Function declarations. */
int isKeyCollison(char *key);
int isSameKey(char *key);

#endif