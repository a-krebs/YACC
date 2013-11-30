/*
 * Module implementing functions generating asc code for 
 * procedures and functions.
 */

#include "EmitProcs.h"
 #include "../ElementArray.h"



void emitProcDecl(Symbol *symbol, struct ElementArray *ea) {
 	CHECK_CAN_EMIT(symbol);

 	emitComment("Procedure declaration: %s", symbol->name);
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