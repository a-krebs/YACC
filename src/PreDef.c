#include "PreDef.h"
#include "Type.h"
#include "Kind.h"
#include "SymbolAll.h"
#include "Hash.h"
#include "Emit.h"

/*
 * This module implements creation functions and accessor functions for
 * pre-defined PAL constants, functions, procedures, and types.
 *
 * It is safe to emit code in this module by calling the various emit*()
 * functions.
 */

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


struct Symbol *createPreDefType(char *name, type_t type) {
	struct Symbol *symbol = NULL;

	if (! ( (strcmp(name, "boolean") == 0 )  ||
		( strcmp(name, "char") == 0 )    ||
		( strcmp(name, "integer") == 0 ) ||
		( strcmp(name, "real") == 0 )    ||
		( strcmp(name, "string") == 0 ) ))
	{
		err(2, "createPreDefType does not support the given type.");
		exit(EXIT_FAILURE);
	}

	symbol = createTypeSymbol(name, TYPEORIGINATOR_YES);
	symbol->kindPtr.TypeKind->type = type;

	addToSymbolTable(symbolTable, symbol);
	
	return symbol;
}


struct preDefTypeSymbols *initializePreDefTypes() {
	struct preDefTypeSymbols *preDefs = calloc(
	    1, sizeof(struct preDefTypeSymbols));	
	preDefs->boolean = createPreDefType(BOOLEAN_KEY, BOOLEAN_T);
	preDefs->chars = createPreDefType(CHAR_KEY, CHAR_T);
	preDefs->integer = createPreDefType(INTEGER_KEY, INTEGER_T);
	preDefs->real = createPreDefType(REAL_KEY, REAL_T);

	return preDefs;
}

struct Symbol *createPreDefProc(char *name) {
	struct Symbol *symbol;

	symbol = calloc(1, sizeof(struct Symbol));
	if (symbol == NULL) {
		err(1, "Failed to allocate memory for symbol name!");
		exit(EXIT_FAILURE);
	}

	setSymbolName(symbol, name);
	symbol->kind = PROC_KIND;

	allocateKindPtr(symbol);
	symbol->kindPtr.ProcKind->params = NULL;

	symbol->lvl = getCurrentLexLevel(symbolTable);
	symbol->typeOriginator = 0;
	symbol->next = NULL;

	return symbol;
}

struct Symbol *createPreDefFunc(char *name) {
	struct Symbol *symbol = createFuncSymbol(name);

	symbol->kindPtr.FuncKind->params = NULL;
	setInnerTypeSymbol(symbol, NULL); 

	return symbol;
}


int initializePreDefProc() {
	struct Symbol *symbol;

	/* IO functions */
	symbol = createPreDefProc(WRITE);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefProc(WRITELN);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefProc(READ);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefProc(READLN);
	addToSymbolTable(symbolTable, symbol);

	return 0;
}


int initializePreDefFunc() {
	struct Symbol *symbol;

	/* IO functions */
	symbol = createPreDefFunc(ODD);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(ABS);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(SQR);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(SQRT);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(SIN);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(EXP);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(LN);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(TRUNC);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(ROUND);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(ORD);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(CHR);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(SUCC);
	addToSymbolTable(symbolTable, symbol);

	symbol = createPreDefFunc(PRED);
	addToSymbolTable(symbolTable, symbol);

	return 0;
}

int initializePreDefConstants() {
	Symbol *symbol = NULL;

	emitBlankLine();
	emitSepLine();
	emitBlankLine();
	emitComment("Pre-defined constants to follow");
	emitBlankLine();
	emitSepLine();
	emitBlankLine();
	
	symbol = createNewBoolConst(TRUE_KEY, 1);
	addToSymbolTable(symbolTable, symbol);
	setSymbolOffset(symbol, symbolTable);
	emitConstDecl(symbol);

	symbol = createNewBoolConst(FALSE_KEY, 0);
	addToSymbolTable(symbolTable, symbol);
	setSymbolOffset(symbol, symbolTable);
	emitConstDecl(symbol);
	
	symbol = createNewIntConst(MAXINT_KEY, ASC_MAX_INT);
	addToSymbolTable(symbolTable, symbol);
	setSymbolOffset(symbol, symbolTable);
	emitConstDecl(symbol);

	return 0;
}

Symbol *createNewBoolConst(char *name, int val) {
	Symbol *symbol = NULL;

	symbol = createConstSymbol(name);
	setInnerTypeSymbol(symbol, getPreDefBool(preDefTypeSymbols));
	symbol->kindPtr.ConstKind->value.Boolean.value = val;

	return symbol;
}

Symbol *createNewIntConst(char *name, int val) {
	Symbol *symbol = NULL;

	symbol = createConstSymbol(name);
	setInnerTypeSymbol(symbol, getPreDefInt(preDefTypeSymbols));
	symbol->kindPtr.ConstKind->value.Integer.value = val;

	return symbol;
}


