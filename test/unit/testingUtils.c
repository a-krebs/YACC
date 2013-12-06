#include "testingUtils.h"
#include "Definitions.h"
#include "Globals.h"
#include "Hash.h"

Symbol *createTestSymbol(int lexLevel, char *key) {
	struct Symbol *symbol = calloc(1, sizeof(struct Symbol));
	symbol->lvl = lexLevel;
	symbol->name = key;
	symbol->typeOriginator = 0;

	return symbol;
}


Symbol *createTestSymbolTypeKind(int lexLevel, char *key, type_t type) {
	struct Symbol *symbol = calloc(1, sizeof(struct Symbol));
	symbol->lvl = lexLevel;
	symbol->name = key;
	symbol->typeOriginator = 0;
	symbol->next = NULL;

	symbol->kind = TYPE_KIND;

	symbol->kindPtr.TypeKind = calloc(1, sizeof(struct TypeKind));
	symbol->kindPtr.TypeKind->type = type;

	return symbol;
}


/*
 * Initialize a clean environment for each test.
 */
void initTestEnv() {
	symbolTable = createHash(&getHashedKeyNormal);
}


/*
 * Tear down the testing environment after each test.
 */
void tearDownTestEnv() {
	destroyHash(&symbolTable);
}
