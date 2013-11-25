#include <stdlib.h>

#include "Definitions.h"

Symbol *createTestSymbol(int lexLevel, char *key);
Symbol *createTestSymbolTypeKind(int lexLevel, char *key, type_t type);


/*
 * Initialize a clean environment for each test.
 */
void initTestEnv();


/*
 * Tear down the testing environment after each test.
 */
void tearDownTestEnv();
