#include "PreDef.h"
#include "Type.h"
#include "Kind.h"
#include "SymbolAll.h"
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

	symbol = createNewBoolConst("true", 1);
	addToSymbolTable(symbolTable, symbol);

	symbol = createNewBoolConst("false", 0);
	addToSymbolTable(symbolTable, symbol);

	// TODO set max in value
	symbol = createNewIntConst("maxint", 0);
	addToSymbolTable(symbolTable, symbol);

	return 0;
}

Symbol *createNewBoolConst(char *name, int val) {
	Symbol *symbol = NULL;

	symbol = calloc(1, sizeof(Symbol));
	if (!symbol) {
		err(1, "Failed to allocate memory for new const symbol!");
		exit(EXIT_FAILURE);
	}
	setSymbolName(symbol, name);
	symbol->kind = CONST_KIND;
	allocateKindPtr(symbol);

	setInnerTypeSymbol(symbol, getPreDefBool(preDefTypeSymbols));

	symbol->kindPtr.ConstKind->value.Boolean.value = val;
	symbol->lvl = getCurrentLexLevel(symbolTable);

	return symbol;
}

Symbol *createNewIntConst(char *name, int val) {
	Symbol *symbol = NULL;

	symbol = calloc(1, sizeof(Symbol));
	if (!symbol) {
		err(1, "Failed to allocate memory for new const symbol!");
		exit(EXIT_FAILURE);
	}
	setSymbolName(symbol, name);
	symbol->kind = CONST_KIND;
	allocateKindPtr(symbol);

	setInnerTypeSymbol(symbol, getPreDefInt(preDefTypeSymbols));

	symbol->kindPtr.ConstKind->value.Integer.value = val;
	symbol->lvl = getCurrentLexLevel(symbolTable);

	return symbol;
}


