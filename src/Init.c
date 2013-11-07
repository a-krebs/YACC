#include "Init.h"


int initialize() { 
	symbolTable = createHash(&getHashedKeyNormal);
	if (symbolTable == NULL)  {
		err(1, "Could not create symbolTable.");
		// exit(EXIT_FAILURE);
	}


	preDefTypesSymbols = initializePredDefs();

}

