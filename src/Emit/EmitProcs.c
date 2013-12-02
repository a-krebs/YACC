/*
 * Module implementing functions generating asc code for 
 * procedures and functions.
 */

#include "EmitProcs.h"

// printf("SIZE OF PARAMS: %d\n", getSizeOfParams(symbol));


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
 	emitLabel(STMT_LEN, label); 
}


/*
 * Emit code to end a procedure.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitEndProc(Symbol *symbol) {
	emitProcOrFuncEndCommon(symbol, "Procedure end.");
}


/*
 * Emit code to end a functions. 
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitEndFunc(Symbol *symbol) {
	/* we don't have a symbol pointer, so just pass in non-null */
	CHECK_CAN_EMIT(1);

	/* Calucalate where to return to:
	   determined by size of parameters 
	   + 3 (PC, display reg, and return value)
	   * -1	
	*/
	int offset = (getSizeOfParams(symbol) + 3) * -1;

	/* Get the lexical so we can idenity the display register */
	int lexLevel = getCurrentLexLevel(symbolTable);

	/* Return result */
	emitStmt(STMT_LEN, "POP %d[%d]", offset, lexLevel);

	emitProcOrFuncEndCommon(symbol, "Function end.");
} 


/*
 * Determines the size of a parameter list
 *
 * Parameters: 	symbol: pointer to function or procedure symbol
 * 	
 * Returns: size of list
 */
int getSizeOfParams(Symbol *procOrFuncSymbol) {
	struct ElementArray *params = NULL;
	Symbol *param = NULL;
	int size = 0;
	type_t type;

	if (procOrFuncSymbol->kind == PROC_KIND) {	
 		params = procOrFuncSymbol->kindPtr.ProcKind->params;
	}
	else if (procOrFuncSymbol->kind == FUNC_KIND)  {
		params = procOrFuncSymbol->kindPtr.FuncKind->params;
	}

	for (int i = 0; i < params->nElements; ++i) {
		param = getElementAt(params, i);

		if ( isByReference(param) ) {
			size++;
			continue;
		}

		if ( param->kind == CONST_KIND ) {
			size++;
			continue;
		}

		param = getTypeSym(param);
		type = getType(param);

		if ( type == BOOLEAN_T 
			|| type == CHAR_T 
			|| type == INTEGER_T
			|| type == REAL_T
			|| type == SCALARINT_T
			//include array because only want base
			|| type == ARRAY_T ) 
		{
			size++;
			continue;	
		}

		if ( type == RECORD_T 
			|| type == SCALAR_T 
			|| type == STRING_T
			) {

			size = size + param->size;
		}
	}

	return size;
}


/*
 * Emit code to end a procedure/function. Adjusts for any local variables
 * and returns.
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitProcOrFuncEndCommon(Symbol *symbol, char *msg) {
	CHECK_CAN_EMIT(1);		

	/* Determine how many levels on the stack we need to adjust by */
	int adjustCount = getSizeOfParams(symbol) * -1;	

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
	char * label = symbol->kindPtr.ProcKind->label;	

 	emitStmt(STMT_LEN, "");
 	emitComment("Start procedure invocation '%s':", symbol->name);
 	
 	emitProcOrFuncInvokCommon(symbol, params, label);
}


/*
 * Emit code to invoce function
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitFuncInvok(Symbol *symbol, struct ElementArray *params) {
	CHECK_CAN_EMIT(symbol);
	char * label = symbol->kindPtr.FuncKind->label;	
	Symbol *param = NULL;

 	emitStmt(STMT_LEN, "");
 	emitComment("Start function invocation '%s':", symbol->name);	

 	//TODO fix this, this should be done for both proc and func
 	for (int i = params->nElements; i > 0 ; i--) {
 		param = getElementAt(params, i - 1);

 		if ( param->kind == CONST_KIND ) {
 			emitComment("NOT READY FOR CONST");	
 			emitStmt(STMT_LEN, "ADJUST -1");
 		}
 	}

 	//make room for return value
	emitStmt(STMT_LEN, "CONSTI 0");

 	emitProcOrFuncInvokCommon(symbol, params, label);
}



/*
 * Common code to emit functions and procedures invocation
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitProcOrFuncInvokCommon(Symbol *symbol, 
	struct ElementArray *params, char *label) 
{
	Symbol *param = NULL;

 	/* Need to do this backwardss so parameters are in expected place on stack.
 	   i.e. First parameter at -3, second at -4, ect */
	for (int i = params->nElements; i > 0 ; i--) {
        	param = getElementAt(params, i - 1);

		if ( param->kind == CONST_KIND ) {
			emitPushAnonConstValue(param);	
		}
		else {
			if (getType(param) == ARRAY_T) {
				emitPushVarAddress(param);
			}
			else {
				emitPushSymbolValue(param);		
			}			
		}                
        }
 
	emitStmt(STMT_LEN, "CALL %d, %s", symbol->lvl, label);
}

