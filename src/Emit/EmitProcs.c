/*
 * Module implementing functions generating asc code for 
 * procedures and functions.
 */

#include "EmitProcs.h"
#include "../ElementArray.h"
 #include "../Hash.h"



void emitProcDecl(Symbol *symbol, struct ElementArray *ea) {
 	CHECK_CAN_EMIT(symbol);

 	emitComment("");
 	emitComment("Procedure start: %s", symbol->name);
 	emitStmt(STMT_LEN, symbol->name); 
 	
	for (int i = 0; i < ea->nElements; i++) {
		emitProcParam(getElementAt(ea, i), i);
	}

}


void emitProcParam(Symbol *param, int paramNum) {
	CHECK_CAN_EMIT(param);	

	/* Get real offset. i.e. Take the parameter number
	and account for the PC and display reg in offset.
	We use 3 because first parameter is at index 0. */
	int offset = (paramNum + 3) * -1;

	emitPushParmVarValue(param, offset, param->lvl);
}

void emitEndProc() {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(1);	

	int lexLevel = getCurrentLexLevel(symbolTable);
	int adjustCount = adjustCounter[lexLevel] * -1;
	emitStmt(STMT_LEN, "ADJUST %d", adjustCount);
	emitStmt(STMT_LEN, "RET %d", lexLevel);

	emitComment("Procedure/Function end.");
	emitComment("");
	emitComment("");
}