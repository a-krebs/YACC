#include "Init.h"
#include "EmitUtils.h"

int initialize() {
	/* symbol table */
	symbolTable = createHash(&getHashedKeyNormal);
	if (symbolTable == NULL)  {
		err(1, "Could not create symbolTable.");
		exit(EXIT_FAILURE);
	}

	/* pre-defined types, procedures and functions */
	preDefTypeSymbols = initializePreDefTypes();
	if (preDefTypeSymbols == NULL) {
		err(1, "Could not create pre-defined types.");
		exit(EXIT_FAILURE);
	}

	initializePreDefProc();
	initializePreDefFunc();
	initializePreDefConstants();

	/* error stuff */
	errors = NULL;
	
	/* control statement stuff */
	whileLoopDepth = 0;
	labelStack = newLabelStack();

	/* user defined procedures and functions stuff */
	procOrFuncStack = newLabelStack();

	return 0;
}


int deInitialize() {
	/* symbol table */
	destroyHash(&symbolTable);

	/* control statement stuff */
	destroyLabelStack(&labelStack);

	/* user defined procedures and functions stuff */
	destroyLabelStack(&procOrFuncStack);	

	return 0;
}
