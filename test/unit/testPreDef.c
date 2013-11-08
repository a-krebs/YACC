/*
 * Cmput 415 - Team YACC
 * Unit tests for the PreDef module.
 */

/*TODO:

*/ 
#include "testPreDef.h"


// struct Symbol *createTestSymbol(int lexLevel, char *key) {
// 	struct Symbol *symbol = malloc(sizeof(struct Symbol));
// 	symbol->lvl = lexLevel;
// 	symbol->name = key;
// 	symbol->typeOriginator = 0;

// 	return symbol;
// }

struct preDefTypeSymbols *initSyms() {
	// levels are arbitrary
    	struct Symbol *boolean = createTestSymbol(12,"bool");
	struct Symbol *chars = createTestSymbol(13,"chars");
	struct Symbol *integer = createTestSymbol(14,"integer");
	struct Symbol *real = createTestSymbol(15,"real");
	struct preDefTypeSymbols *syms =
	    calloc(1, sizeof(struct preDefTypeSymbols));
	
	syms->boolean = boolean;
	syms->chars = chars;
	syms->integer = integer;
	syms->real = real;
	return syms;
}


char *test_getPreDefBool() {
	struct preDefTypeSymbols *syms;
	syms = initSyms();

	struct Symbol *symbol = getPreDefBool(syms);


	mu_assert(
	    "Symbol name mismatch.",
	    strcmp(symbol->name, "bool") == 0);
	mu_assert(
	    "Symbol level mismatch.",
	    symbol->lvl == 12);

	free(syms);

        return NULL;
}


char *test_getPreDefChar() {
	struct preDefTypeSymbols *syms;
	syms = initSyms();

	struct Symbol *symbol = getPreDefChar(syms);

	mu_assert(
	    "Symbol name mismatch.",
	    strcmp(symbol->name, "chars") == 0);
	mu_assert(
	    "Symbol level mismatch.",
	    symbol->lvl == 13);

	free(syms);

        return NULL;
}


char *test_getPreDefInt() {
	struct preDefTypeSymbols *syms;
	syms = initSyms();

	struct Symbol *symbol = getPreDefInt(syms);

	mu_assert(
	    "Symbol name mismatch.",
	    strcmp(symbol->name, "integer") == 0);
	mu_assert(
	    "Symbol level mismatch.",
	    symbol->lvl == 14);

        return NULL;
}


char *test_getPreDefReal() {
	struct preDefTypeSymbols *syms;
	syms = initSyms();

	struct Symbol *symbol = getPreDefReal(syms);

	mu_assert(
	    "Symbol name mismatch.",
	    strcmp(symbol->name, "real") == 0);
	mu_assert(
	    "Symbol level mismatch.",
	    symbol->lvl == 15);

        return NULL;
}

char * test_all_PreDef() {
	
	mu_run_test(test_getPreDefBool);
	mu_run_test(test_getPreDefChar);
	mu_run_test(test_getPreDefInt);
	mu_run_test(test_getPreDefReal);

	return NULL;
}
