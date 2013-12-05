/*
 * Module implementing functions generating asc code for 
 * procedures and functions.
 */

#include "Tree.h"
#include "EmitProcs.h"
#include "EmitExprs.h"

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
// TODO: make this function work correctly
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
	//Symbol *param = NULL;

 	emitStmt(STMT_LEN, "");
 	emitComment("Start function invocation '%s':", symbol->name);	
	

 	//TODO remove this if not needed. If needed it needs fixin'
 	// for (int i = params->nElements; i > 0 ; i--) {
 	// 	param = getElementAt(params, i - 1);

 	// 	if ( param->kind == CONST_KIND ) {
 	// 		emitComment("NOT READY FOR CONST");	
 	// 		emitStmt(STMT_LEN, "ADJUST -1");
 	// 	}
 	// }

 	//make room for return value
	emitStmt(STMT_LEN, "CONSTI 0");

 	emitProcOrFuncInvokCommon(symbol, params, label);
}


/*
 * Emit code to emit structure type symbols: arrays, records
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitStructuredType(Symbol *arg, Symbol *param) {
	int offset = arg->offset;	

	if ( isByReference(param) ) {
 		emitStmt(STMT_LEN, "PUSH %d[%d]", param->offset, param->lvl); 
 		emitStmt(STMT_LEN, "PUSHI");	
 		return;		
	}

	//elese go throught each element in array and push onto stack
	for (int i = 0; i < arg->size; ++i){
		offset = arg->offset + i;
		emitStmt(STMT_LEN, "PUSH %d[%d]", offset, arg->lvl); 
	}
}


/*
 * Gets the ElementArray for the paramters for a fucntion or
 * procedure symbol
 *
 * Parameters: procOrFuncSymbol: symbol to func/proc
 * 	
 * Returns: ElementArray of paramters
 */
struct ElementArray *getProcOrFuncParams(Symbol *procOrFuncSymbol) {
	struct ElementArray *params = NULL;

	if (procOrFuncSymbol->kind == PROC_KIND) {	
 		params = procOrFuncSymbol->kindPtr.ProcKind->params;
	}
	else if (procOrFuncSymbol->kind == FUNC_KIND)  {
		params = procOrFuncSymbol->kindPtr.FuncKind->params;
	}

	return params;
}


/*
 * Common code to emit functions and procedures invocation
 *
 * Parameters: void.
 * 	
 * Returns: void
 */
void emitProcOrFuncInvokCommon(Symbol *symbol, 
	struct ElementArray *args, char *label) 
{
	struct ElementArray *params = getProcOrFuncParams(symbol);
	struct treeNode *argNode = NULL;
	Symbol *arg = NULL;
	Symbol *param = NULL;
	int i;

	for (i = args->nElements; i > 0 ; i--) {

		/* Get parameter symbol from the proc/func's kindPtr */
		param = getElementAt(params, i-1);

		/* Get the argument symbol from the parsed expression nodes */
		argNode = getElementAt(args, i-1);

		if (!argNode) return;
	
		arg = argNode->symbol;

		if (!(arg) || !(param)) return;

		/* Push the value of expression */
		postOrderWalk(argNode);	
		emitPushParamValue(arg, isByReference(param)); 
	}
	emitStmt(STMT_LEN, "CALL %d, %s", symbol->lvl, label);
}




/*
 * Given a Symbol which is to be placed onto the stack in preparation
 * for a call to a function, determines if that Symbol's value already
 * exists on the stack or if it needs to be pushed (in which case it does so).
 * Parameters
 *		s : the symbol being passed to a procedure/function whose
 *		    value needs to be placed on the stack.
 */

void emitPushParamValue(Symbol *s, int byRef)
{
	if (!byRef) {
		/* The variable is being passed by value, so its value needs
		 * to be placed on the stack. */

		/* s is a constant */ 
		if (s->kind == CONST_KIND) {
			if (!isConstResultSym(s)) {
				emitPushSymbolValue(s);
			} 
		/* Else, s is result of expression and value already
		 * on the stack */
			return;
		}

		/* s is a variable, so its value is not on the stack.
		 * This case is simply -- we simply push its value */
		if (s->kind == VAR_KIND) {
			if ( (getType(s) == ARRAY_T) || (getType(s) ==
			    RECORD_T) ) {
			emitPushStructuredVarValue(s);
			} else {
				emitPushSymbolValue(s);
			}
			return;
		}

		/* We got to here, meaning s must be a type_kind symbol */

		/* 
		 * If the symbol of type_kind and one of the following holds:
		 * (i) 		its address flag is set
		 * (ii)		it is an array type
		 * (iii) 	it a record type
		 * then necessarily we have that the value on top of the stack
		 * is an address.  We need to convert this address into a value
		 * (or array of values) as appropriate.
		 */
		if ( (s->isAddress) || getType(s) == ARRAY_T || getType(s) ==
		    (RECORD_T) ) {
			emitPushAddressValue(s);	
		}

		/* 
		 * Else, it is a type symbol which is resultant from an
 		 * expression that did not leave an address on the stack.
 		 * Thus, we have nothing to do
		 */
	} else {
		emitComment("got here");
		/* 
		 * Else, the variable is being passed by reference.  And we 
		 * only want to push the address of the variable onto the
		 * stack
		 */
		if (s->kind == CONST_KIND) {
			/* THIS SHOULD NOT HAPPEN : cannot pass const by ref  */
		}

		/* s is a variable, so its value is not on the stack.  In this
		 * case we simply push its address */
		if (s->kind == VAR_KIND) {
			emitPushVarAddress(s);
		}

		/* else s is a type_kind, in which case its resultant from some
		 * expression and its value is already on the stack */
	}
}
