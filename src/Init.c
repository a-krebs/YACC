#include "Init.h"

extern StmtLL *stmts;

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

	/* at start, we're in the main program declarations section */
	inMainDecls = 1;

	/* prep global StmtLL */
	stmts = NULL;
	/* emit some comments and stuff */
	emitInit();

	initializePreDefProc();
	initializePreDefFunc();
	initializePreDefConstants();

	/* error stuff */
	errors = NULL;
	
	/* control statement stuff */
	whileLoopDepth = 0;
	labelStack = newLabelStack();
	loopLabelStack = newLabelStack();

	/* user defined procedures and functions stuff */
	procOrFuncStack = newLabelStack();
	/* labels for main proc and func bodies */
	mainLabelStack = newLabelStack();


	return 0;
}


int deInitialize() {
	/* symbol table */
	destroyHash(&symbolTable);

	/* control statement stuff */
	destroyLabelStack(&labelStack);
	destroyLabelStack(&loopLabelStack);

	/* user defined procedures and functions stuff */
	destroyLabelStack(&procOrFuncStack);	
	
	/* Linked List of emitted code */
	freeStmtLL(stmts);

	return 0;
}
