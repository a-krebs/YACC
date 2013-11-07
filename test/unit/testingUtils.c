#include "testingUtils.h"

Symbol *createTestSymbol(int lexLevel, char *key) {
	struct Symbol *symbol = malloc(sizeof(struct Symbol));
	symbol->lvl = lexLevel;
	symbol->name = key;
	symbol->typeOriginator = 0;

	return symbol;
}
