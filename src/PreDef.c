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


Symbol *getPreDefString(struct preDefTypeSymbols *preDefTypeSymbols) {
	return preDefTypeSymbols->string;
}


struct Symbol *createPreDefType(char *name, type_t type) {
	struct Symbol *symbol = malloc(sizeof(struct Symbol));

	setSymbolName(symbol, name);
	symbol->kind = TYPE_KIND;

	allocateKindPtr(symbol);
	symbol->kindPtr.TypeKind->type = type;

	if ( strcmp(name, "boolean") == 0 ) {
		getTypePtr(symbol)->Boolean = calloc(1, sizeof(struct Boolean));
	}
	else if ( strcmp(name, "char") == 0 ) {
		getTypePtr(symbol)->Char = calloc(1, sizeof(struct Char));
	}
	else if ( strcmp(name, "integer") == 0 ) {
		getTypePtr(symbol)->Integer = calloc(1, sizeof(struct Integer));
	}
	else if ( strcmp(name, "real") == 0 ) {
		getTypePtr(symbol)->Real = calloc(1, sizeof(struct Real));
	}
	else if ( strcmp(name, "string") == 0 ) {
		getTypePtr(symbol)->String = malloc(sizeof(struct String));
	}	
	else {
		err(2, "Could not determine type asked in pre-def.");
		exit(EXIT_FAILURE);
	}

	symbol->lvl = getCurrentLexLevel(symbolTable);
	symbol->typeOriginator = 1;
	symbol->next = NULL;

	return symbol;
}


struct preDefTypeSymbols *initializePreDefTypes() {
	struct preDefTypeSymbols *preDefs = malloc(sizeof(struct preDefTypeSymbols));	
	preDefs->boolean = createPreDefType(BOOLEAN_KEY, BOOLEAN_T);
	preDefs->chars = createPreDefType(CHAR_KEY, CHAR_T);
	preDefs->integer = createPreDefType(INTEGER_KEY, INTEGER_T);
	preDefs->real = createPreDefType(REAL_KEY, REAL_T);
	preDefs->string = createPreDefType(STRING_KEY, STRING_T);

	createHashElement(symbolTable, BOOLEAN_KEY, preDefs->boolean);
	createHashElement(symbolTable, CHAR_KEY, preDefs->chars);
	createHashElement(symbolTable, INTEGER_KEY, preDefs->integer);
	createHashElement(symbolTable, REAL_KEY, preDefs->real);
	createHashElement(symbolTable, STRING_KEY, preDefs->string);

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
	struct Symbol *symbol;

	symbol = calloc(1, sizeof(struct Symbol));
	
	if (symbol == NULL) {
		err(1, "Failed to allocate memory for symbol name!");
		exit(EXIT_FAILURE);
	}

	setSymbolName(symbol, name);
	symbol->kind = FUNC_KIND;

	allocateKindPtr(symbol);
	symbol->kindPtr.FuncKind->params = NULL;
	symbol->kindPtr.FuncKind->typeSym = NULL;


	symbol->lvl = getCurrentLexLevel(symbolTable);
	symbol->typeOriginator = 0;
	symbol->next = NULL;

	return symbol;
}


int initializePreDefProc() {
	struct Symbol *symbol;

	/* IO functions */
	symbol = createPreDefProc(WRITE);
	createHashElement(symbolTable, WRITE, symbol);

	symbol = createPreDefProc(WRITELN);
	createHashElement(symbolTable, WRITELN, symbol);

	symbol = createPreDefProc(READ);
	createHashElement(symbolTable, READ, symbol);

	symbol = createPreDefProc(READLN);
	createHashElement(symbolTable, READLN, symbol);

	return 0;
}


int initializePreDefFunc() {
	struct Symbol *symbol;

	/* IO functions */
	symbol = createPreDefFunc(ODD);
	createHashElement(symbolTable, ODD, symbol);

	symbol = createPreDefFunc(ABS);
	createHashElement(symbolTable, ABS, symbol);

	symbol = createPreDefFunc(SQR);
	createHashElement(symbolTable, SQR, symbol);

	symbol = createPreDefFunc(SQRT);
	createHashElement(symbolTable, SQRT, symbol);

	symbol = createPreDefFunc(SIN);
	createHashElement(symbolTable, SIN, symbol);

	symbol = createPreDefFunc(COS);
	createHashElement(symbolTable, COS, symbol);

	symbol = createPreDefFunc(EXP);
	createHashElement(symbolTable, EXP, symbol);

	symbol = createPreDefFunc(LN);
	createHashElement(symbolTable, LN, symbol);

	symbol = createPreDefFunc(ARCTAN);
	createHashElement(symbolTable, ARCTAN, symbol);

	symbol = createPreDefFunc(TRUNC);
	createHashElement(symbolTable, TRUNC, symbol);

	symbol = createPreDefFunc(ROUND);
	createHashElement(symbolTable, ROUND, symbol);

	symbol = createPreDefFunc(ORD);
	createHashElement(symbolTable, ORD, symbol);

	symbol = createPreDefFunc(CHR);
	createHashElement(symbolTable, CHR, symbol);

	symbol = createPreDefFunc(SUCC);
	createHashElement(symbolTable, SUCC, symbol);

	symbol = createPreDefFunc(PRED);
	createHashElement(symbolTable, PRED, symbol);

	return 0;
}

int initializePreDefConstants() {
	Symbol *symbol = NULL;

	symbol = createNewBoolConst("true", 1);
	createHashElement(symbolTable, "true", symbol);

	symbol = createNewBoolConst("false", 0);
	createHashElement(symbolTable, "false", symbol);

	// TODO set max in value
	symbol = createNewIntConst("maxint", 0);
	createHashElement(symbolTable, "maxint", symbol);

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

	symbol->kindPtr.ConstKind->typeSym = getPreDefBool(preDefTypeSymbols);
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

	symbol->kindPtr.ConstKind->typeSym = getPreDefInt(preDefTypeSymbols);
	symbol->kindPtr.ConstKind->value.Integer.value = val;
	symbol->lvl = getCurrentLexLevel(symbolTable);

	return symbol;
}
