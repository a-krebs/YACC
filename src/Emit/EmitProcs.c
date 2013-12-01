/*
 * Module implementing functions generating asc code for 
 * procedures and functions.
 */

#include "EmitProcs.h"


/*
 * Emit code to push procedure/function call onto the the stack.
 *
 * Parameters: 	param: parameter symbol
 *				paramNum: the parameter's position number in the 
 *					parameter list.
 * 	
 * Returns: void
 */
void emitProcOrFuncDecl(Symbol *symbol, struct ElementArray *ea) {
 	CHECK_CAN_EMIT(symbol);
 	emitStmt(STMT_LEN, "");
 	emitStmt(STMT_LEN, "");

 	char *label = createProcOrFunctionLabel(symbol);
 	
 	if (symbol->kind == PROC_KIND) {	
 		symbol->kindPtr.ProcKind->label = label;
		emitComment("Procedure start: %s", label);
	}
	else if (symbol->kind == FUNC_KIND)  {
		symbol->kindPtr.FuncKind->label = label;
	 	emitComment("Function start: %s", label);
	}

 	/* Emit procedure label */
 	emitStmt(STMT_LEN, label); 
}


/*
 * Emit code to end a procedure.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitEndProc() {
	emitProcOrFuncEndCommon("Procedure end.");
}


/*
 * Emit code to end a functions. 
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitEndFunc() {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(1);

	/* Default return space on stack */
	int offset = (getReturnOffset() + 2) * -1;

	/* Get the lexical so we can idenity the display register */
	int lexLevel = getCurrentLexLevel(symbolTable);

	/* Return result */
	emitStmt(STMT_LEN, "POP %d[%d]", offset, lexLevel);

	emitProcOrFuncEndCommon("Function end.");
} 


/*
 * Emit code to end a procedure/function. Adjusts for any local variables
 * and returns.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitProcOrFuncEndCommon(char *msg) {
	CHECK_CAN_EMIT(1);		

	/* Determine how many levels on the stack we need to adjust by */
	int adjustCount = getAdjustCounter() * -1;	

	/* Get the lexical so we can idenity the display register */
	int lexLevel = getCurrentLexLevel(symbolTable);	

	/* Adjust and return */
	emitStmt(STMT_LEN, "ADJUST %d", adjustCount);
	emitStmt(STMT_LEN, "RET %d", lexLevel);

	emitComment(msg);
	emitStmt(STMT_LEN, "");
	emitStmt(STMT_LEN, "");	
}


/*
 * Creates a label for procedure/function. Label would have form
 * symbolName_currentStackNumber.
 *
 * I fully realize this function was coded as stupid...
 *
 * Parameters: symbol: procedure/function symbol to create label for.
 * 	
 * Returns: generated label
 */
char *createProcOrFunctionLabel(Symbol *symbol) {
	char *tempName = NULL;
	char *name = NULL;
	int labelCount;
	int size;

	reserveLabels(procOrFuncStack, 1);
	labelCount = peekLabelStackTop(procOrFuncStack);

	size = snprintf(NULL, 0, "%i", labelCount);
        tempName = calloc(1, size + 1);
        sprintf(tempName, "%i", labelCount);

        name = calloc(1, (strlen(symbol->name) + 2 + strlen(tempName) ));
        strcat(name, symbol->name);
        strcat(name, "_");
        strcat(name, tempName);

        free(tempName);

        return name;
}


/*
 * Emit code to invoce procedure
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitProcInvok(Symbol *symbol, struct ElementArray *params) {
	CHECK_CAN_EMIT(symbol);
	Symbol *tempSym;

 	emitStmt(STMT_LEN, "");
 	emitComment("Start procedure invocation:");
 	
	char * label = symbol->kindPtr.ProcKind->label;

	//  Foreach parameter, push onto stack 
        for (int i = params->nElements ; i > 0 ; i--) {
                emitPushSymbolValue(getElementAt(params, i - 1));
        }
 
	emitStmt(STMT_LEN, "GOTO %s", label);
}
