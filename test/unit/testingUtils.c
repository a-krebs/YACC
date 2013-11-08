#include "testingUtils.h"
#include "Definitions.h"

Symbol *createTestSymbol(int lexLevel, char *key) {
	struct Symbol *symbol = malloc(sizeof(struct Symbol));
	symbol->lvl = lexLevel;
	symbol->name = key;
	symbol->typeOriginator = 0;

	return symbol;
}


Symbol *createTestSymbolTypeKind(int lexLevel, char *key, type_t type) {
	struct Symbol *symbol = malloc(sizeof(struct Symbol));
	symbol->lvl = lexLevel;
	symbol->name = key;
	symbol->typeOriginator = 0;
	symbol->next = NULL;

	symbol->kind = TYPE_KIND;

	symbol->kindPtr.TypeKind = calloc(1, sizeof(struct TypeKind));
	symbol->kindPtr.TypeKind->type = type;

	return symbol;
}