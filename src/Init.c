#include "Init.h"

int initialize() { 
	symbolTable = createHash(&getHashedKeyNormal);
	if (symbolTable == NULL)  {
		err(1, "Could not create symbolTable.");
		exit(EXIT_FAILURE);
	}

	preDefTypeSymbols = initializePreDefTypes();
	if (preDefTypeSymbols == NULL) {
		err(1, "Could not create pre-defined types.");
		exit(EXIT_FAILURE);
	}

	initializePreDefProc();
	initializePreDefFunc();
	initializePreDefConstants();

	errors = NULL;
	
	whileLoopDepth = 0;

	return 0;
}

int deInitialize() {
	destroyHash(&symbolTable);

	return 0;
}
