#include "PreDef.h"
#include "Type.h"
#include "Kind.h"
#include "Symbol.h"
#include "Hash.h"

Symbol *getPreDefBool(struct preDefTypeSymbols *preDefTypeSymbols) {
	return preDefTypeSymbols->boolean;
}


Symbol *getPreDefChar(struct preDefTypeSymbols *preDefTypeSymbols) {
	return preDefTypeSymbols->chars;
}


Symbol *getPreDefInt(struct preDefTypeSymbols *preDefTypeSymbols) {
	return preDefTypeSymbols->integer;
}


Symbol *getPreDefReal(struct preDefTypeSymbols *preDefTypeSymbols) {
	return preDefTypeSymbols->real;
}


struct Symbol *createPreDef(char *name, type_t type) {
	struct Symbol *symbol = malloc(sizeof(struct Symbol));

	setSymbolName(symbol, name);
	symbol->kind = TYPE_KIND;

	allocateKindPtr(symbol);
	symbol->kindPtr.TypeKind->type = type;

	if ( strcmp(name, "boolean") == 0 ) {
		getTypePtr(symbol)->Boolean = malloc(sizeof(struct Boolean));
	}
	else if ( strcmp(name, "char") == 0 ) {
		getTypePtr(symbol)->Char = malloc(sizeof(struct Char));
	}
	else if ( strcmp(name, "integer") == 0 ) {
		getTypePtr(symbol)->Integer = malloc(sizeof(struct Integer));
	}
	else if ( strcmp(name, "real") == 0 ) {
		getTypePtr(symbol)->Real = malloc(sizeof(struct Real));
	}
	else {
		err(2, "Could not determine type asked in pre-def.");
		exit(EXIT_FAILURE);
	}

	symbol->lvl = 0; ///fix this
	symbol->typeOriginator = 1;
	symbol->next = NULL;

	return symbol;
}


struct preDefTypeSymbols *initializePredDefs() {
	struct preDefTypeSymbols *preDefs = malloc(sizeof(struct preDefTypeSymbols));	
	preDefs->boolean = createPreDef(BOOLEAN_KEY, TYPE_KIND);
	preDefs->chars = createPreDef(CHAR_KEY, TYPE_KIND);
	preDefs->integer = createPreDef(INTEGER_KEY, TYPE_KIND);
	preDefs->real = createPreDef(REAL_KEY, TYPE_KIND);

	createHashElement(symbolTable, BOOLEAN_KEY, preDefs->boolean);
	createHashElement(symbolTable, CHAR_KEY, preDefs->chars);
	createHashElement(symbolTable, INTEGER_KEY, preDefs->integer);
	createHashElement(symbolTable, REAL_KEY, preDefs->real);

	return preDefs;
}