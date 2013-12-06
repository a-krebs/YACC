/*
 * Module implementing functions for generating asc code to call pre-defined
 * functions.
 */

#include "EmitPreDef.h"

/* Predefined functions */
static void emitOrd(Symbol *, struct treeNode *);
static void emitChr(Symbol *, struct treeNode *);
static void emitTrunc(Symbol *, struct treeNode *);
static void emitRound(Symbol *, struct treeNode *);
static void emitSucc(Symbol *, struct treeNode *);
static void emitPred(Symbol *, struct treeNode *);

static void emitOdd(Symbol *, struct treeNode *);
static void emitAbs(Symbol *, struct treeNode *);
static void emitSqrt(Symbol *, struct treeNode *);
static void emitSin(Symbol *, struct treeNode *);
static void emitExp(Symbol *, struct treeNode *);
static void emitLn(Symbol *, struct treeNode *);

static void pushPreDefFuncValues(Symbol *, struct treeNode *);


/* IO Procedures */
static void emitIOCall(char *, Symbol *);
static void emitRead(Symbol *, struct ElementArray *);
static void emitReadln(Symbol *, struct ElementArray *);
static void emitWrite(Symbol *, struct ElementArray *);
static void emitWriteln(Symbol *, struct ElementArray *);

void emitPreDefFunc(Symbol *s, struct ElementArray *args)
{
	struct treeNode *node;
	CHECK_CAN_EMIT(s);
	if (!args) return;

	/* All predefined functions only take one argument */
	node = getElementAt(args, 0);

	if (strcmp(s->name, "ord") == 0) {

		emitOrd(s, node);

	} else if (strcmp(s->name, "odd") == 0) {

		emitOdd(s, node);

	} else if (strcmp(s->name, "abs") == 0) {

		emitAbs(s, node);

	} else if (strcmp(s->name, "sqrt") == 0) {

		emitSqrt(s, node);

	} else if (strcmp(s->name, "sin") == 0) {

		emitSin(s, node);

	} else if (strcmp(s->name, "exp") == 0) {
	
		emitExp(s, node);

	} else if (strcmp(s->name, "ln") == 0) {

		emitLn(s, node);
	
	} else if (strcmp(s->name, "chr") == 0) {

		emitChr(s, node);

	} else if (strcmp(s->name, "trunc") == 0) {

		emitTrunc(s, node);

	} else if (strcmp(s->name, "round") == 0) {

		emitRound(s, node);

	} else if (strcmp(s->name, "succ") == 0) {

		emitSucc(s, node);

	} else if (strcmp(s->name, "pred") == 0) {

		emitPred(s, node);

	} else if (strcmp(s->name, "chr") == 0) {

		
	}
}

static void pushPreDefFuncValues(Symbol *s, struct treeNode *node)
{
	emitComment("Make room for return value");
	emitStmt(STMT_LEN, "CONSTI 0");	
	postOrderWalk(node);
	emitPushParamValue(node->symbol, 0);
}

static void emitOrd(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	/* We don't care what type it is, we just return the value anyway */
	emitStmt(STMT_LEN, "CALL 0, __ord");
	emitStmt(STMT_LEN, "ADJUST -1");
}

static void emitChr(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	emitStmt(STMT_LEN, "CALL 0, __chr");
	emitStmt(STMT_LEN, "ADJUST -1");
}

static void emitTrunc(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	if (getType(node->symbol) == INTEGER_T) {
		emitStmt(STMT_LEN, "ITOR");
	}
	emitStmt(STMT_LEN, "CALL 0, __trunc");
	emitStmt(STMT_LEN, "ADJUST -1");
}

static void emitRound(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	if (getType(node->symbol) == INTEGER_T) {
		emitStmt(STMT_LEN, "ITOR");
	}
	emitStmt(STMT_LEN, "CALL 0, __round");
	emitStmt(STMT_LEN, "ADJUST -1");
}

static void emitSucc(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	switch (getType(node->symbol)) {
	case BOOLEAN_T:
		emitStmt(STMT_LEN, "CALL 0, __succ_bool");
		break;
	case CHAR_T:
		emitStmt(STMT_LEN, "CALL 0, __succ_char");
		break;
	case INTEGER_T:
		emitStmt(STMT_LEN, "CALL 0, __succ_int");
		break;
	case SCALAR_T:
		emitStmt(STMT_LEN, "CALL 0, __succ_scalar");
		break;
	default:
		/* Not reached */
		break; 
	}
	emitStmt(STMT_LEN, "ADJUST -1");
}

static void emitPred(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	switch (getType(node->symbol)) {
	case BOOLEAN_T:
		emitStmt(STMT_LEN, "CALL 0, __pred_bool");
		break;
	case CHAR_T:
		emitStmt(STMT_LEN, "CALL 0, __pred_char");
		break;
	case INTEGER_T:
		emitStmt(STMT_LEN, "CALL 0, __pred_int");
		break;
	case SCALAR_T:
		emitStmt(STMT_LEN, "CALL 0, __pred_scalar");
		break;
	default:
		/* Not reached */
		break; 
	}
}

static void emitOdd(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	emitStmt(STMT_LEN, "CALL 0, __odd");
	emitStmt(STMT_LEN, "ADJUST -1");
}

static void emitAbs(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	switch (getType(node->symbol)) {
	case INTEGER_T:
		emitStmt(STMT_LEN, "CALL 0, __abs_int");
		break;
	case REAL_T:
		emitStmt(STMT_LEN, "CALL 0, __abs_real");
		break;
	default:
		/* Not reached */
		break;
	}
	emitStmt(STMT_LEN, "ADJUST -1");
}

static void emitSqrt(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	switch (getType(node->symbol)) {
	case INTEGER_T:
		emitStmt(STMT_LEN, "CALL 0, __sqrt_int");
		break;
	case REAL_T:
		emitStmt(STMT_LEN, "CALL 0, __sqrt_real");
		break;
	default:
		/* Not reached */
		break;	
	}
	emitStmt(STMT_LEN, "ADJUST -1");
}
static void emitSin(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	switch (getType(node->symbol)) {
	case INTEGER_T:
		emitStmt(STMT_LEN, "CALL 0, __sqrt_int");
		break;
	case REAL_T:
		emitStmt(STMT_LEN, "CALL 0, __sqrt_real");
		break;
	default:
		/* Not reached */
		break;
	}
	emitStmt(STMT_LEN, "ADJUST -1");
}
static void emitExp(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	switch (getType(node->symbol)) {
	case INTEGER_T:
		emitStmt(STMT_LEN, "CALL 0, __exp_int");
		break;
	case REAL_T:
		emitStmt(STMT_LEN, "CALL 0, __exp_real");
		break;
	default:
		/* Not reached */
		break;
	}
	emitStmt(STMT_LEN, "ADJUST -1");
}
static void emitLn(Symbol *s, struct treeNode *node)
{
	pushPreDefFuncValues(s, node);
	switch (getType(node->symbol)) {
	case INTEGER_T:
		emitStmt(STMT_LEN, "CALL 0, __ln_int");
		break;
	case REAL_T:
		emitStmt(STMT_LEN, "CALL 0, __ln_real");
		break;
	default:
		/* Not reached */
		break;
	}
	emitStmt(STMT_LEN, "ADJUST -1");
}

/*
 * Emits the code necessary to called the pre-defined I/O procedure 
 * represented in s with the arguments args (an array of expression nodes).
 * 
 */
void emitPreDefIO(Symbol *s, struct ElementArray *args)
{
	CHECK_CAN_EMIT(s);
	if (!args) return;
	
	if (strcmp(s->name, "read") == 0 ) {

		emitRead(s, args);

	} else if (strcmp(s->name, "readln") == 0) {

		emitReadln(s, args);

	} else if (strcmp(s->name, "write") == 0) {

		emitWrite(s, args);

	} else if (strcmp(s->name, "writeln") == 0) {

		emitWriteln(s, args);
	}
}

static void emitRead(Symbol *s, struct ElementArray *args)
{
	Symbol *arg = NULL;
	int i;
	
	/* handle the special case of no arguments */
	if (args->nElements == 0) {
		emitStmt(STMT_LEN, "CALL 0, __read_no_args");
		return;
	}

	/* handle the general case of variable number of args */
	for (i = 0; i < args->nElements; i++) {
		arg = ((struct treeNode *)getElementAt(args, i))->symbol;
		
		if (!arg) return;

		if (arg->kind == VAR_KIND) {
			if (arg->isAddress) {
				postOrderWalk(getElementAt(args, i));
			} else { 
				emitPushVarAddress(arg);
			}
		}

		if (arg->kind == TYPE_KIND) {
			/* Walk the subtree of the expression node to pus
			 * the correct address on the stack */
			emitComment("Walking expression tree to generate "
			    "correct address.");
			postOrderWalk(getElementAt(args, i));
		}
	
		switch (getType(arg)) {
		case ARRAY_T:
		case CHAR_T:
			emitIOCall("__read_str", arg);
			break;
		case INTEGER_T:
			emitIOCall("__read_int", arg);
			break;
		case REAL_T:
			emitIOCall("__read_real", arg);
			break;
		default:
			break;
		}
	}
}

static void emitReadln(Symbol *s, struct ElementArray *args)
{
	Symbol *arg = NULL;
	int i;
	
	/* handle the special case of no arguments */
	if (args->nElements == 0) {
		emitStmt(STMT_LEN, "CALL 0, __read_no_args");
		return;
	}

	/* handle the general case of variable number of args */
	for (i = 0; i < args->nElements; i++) {
		arg = ((struct treeNode *)getElementAt(args, i))->symbol;
		
		if (!arg) return;

		if (arg->kind == VAR_KIND) {
			if (arg->isAddress) {
				postOrderWalk(getElementAt(args, i));
			} else { 
				emitPushVarAddress(arg);
			}
		}

		if (arg->kind == TYPE_KIND) {
			/* Walk the subtree of the expression node to pus
			 * the correct address on the stack */
			emitComment("Walking expression tree to generate "
			    "correct address.");
			postOrderWalk(getElementAt(args, i));
		}
	
		switch (getType(arg)) {
		case ARRAY_T:
		case CHAR_T:
			emitIOCall("__readln_str", arg);
			break;
		case INTEGER_T:
			emitIOCall("__readln_int", arg);
			break;
		case REAL_T:
			emitIOCall("__readln_real", arg);
			break;
		default:
			break;
		}
	}
}
static void emitWrite(Symbol *s, struct ElementArray *args)
{
	struct treeNode *node;
	Symbol *arg;
	int i;

	/* No need to handle the no argument case here */

	for (i = 0; i < args->nElements; i++) {
		arg = ((struct treeNode *)getElementAt(args, i))->symbol;
	
		if (!arg) return;
		arg = ((struct treeNode *)getElementAt(args, i))->symbol;
		node = getElementAt(args, i);	
		if (!arg) return;

		postOrderWalk(node);
		if (arg->kind == VAR_KIND) {
			if (node->opToken == RECORD_ACCESS) {
				if (getType(arg) != ARRAY_T)
					emitStmt(STMT_LEN, "PUSHI"); 
			} else {
				emitPushVarValue(arg);
			}
	
		} else if ((arg->kind == CONST_KIND) && 
		    !isConstResultSym(arg)) {

			emitPushConstValue(arg);
		}
		switch (getType(arg)) {
		case ARRAY_T:
		case CHAR_T:
		case STRING_T:
			emitIOCall("__write_str", arg);
			break;
		case INTEGER_T:
			emitIOCall("__write_int", arg);
			break;
		case REAL_T:
			emitIOCall("__write_real", arg);
			break;
		default:
			/* Should not be reached */
			break;
		}
	}
}
static void emitWriteln(Symbol *s, struct ElementArray *args)
{
	struct treeNode *node;
	Symbol *arg;
	int i;
	if (args->nElements == 0) {
		// TODO: can I just call writeln and have it do the right
		// thing?
		return;
	} 

	for (i = 0; i < args->nElements; i++) {
		arg = ((struct treeNode *)getElementAt(args, i))->symbol;
		node = getElementAt(args, i);	
		if (!arg) return;

		postOrderWalk(node);
		if (arg->kind == VAR_KIND) {
			if (node->opToken == RECORD_ACCESS) {
				if (getType(arg) != ARRAY_T)
					emitStmt(STMT_LEN, "PUSHI"); 
			} else {
				emitPushVarValue(arg);
			}
	
		} else if ((arg->kind == CONST_KIND) && 
		    !isConstResultSym(arg)) {

			emitPushConstValue(arg);
		}
		switch (getType(arg)) {
		case ARRAY_T:
		case CHAR_T:
		case STRING_T:
			emitIOCall("__writeln_str", arg);
			break;
		case INTEGER_T:
			emitIOCall("__writeln_int", arg);
			break;
		case REAL_T:
			emitIOCall("__writeln_real", arg);
			break;
		default:
			/* Should not be reached */
			break;
		}
	}
}

static void emitIOCall(char *proc, Symbol *arg)
{
	switch (getType(arg)) {
	case ARRAY_T:
		emitComment("Push size of char array");
		emitStmt(STMT_LEN, "CONSTI %d", arg->size);
		emitStmt(STMT_LEN, "CALL 0, %s", proc);
		emitComment("Kick params off the stack.");
		emitStmt(STMT_LEN, "ADJUST -2");
		break;
	case CHAR_T:
		emitComment("Push size of char array");
		emitStmt(STMT_LEN, "CONSTI 1");
		emitStmt(STMT_LEN, "CALL 0, %s", proc);
		emitComment("Kick params off the stack.");
		emitStmt(STMT_LEN, "ADJUST -2");
		break;
	case INTEGER_T:
		emitStmt(STMT_LEN, "CALL 0, %s", proc);
		emitStmt(STMT_LEN, "ADJUST -1");
		break;
	case REAL_T:
		emitStmt(STMT_LEN, "CALL 0, %s", proc);
		emitStmt(STMT_LEN, "ADJUST -1");
		break;
	case STRING_T:
		emitComment("Push size of string");
		emitStmt(STMT_LEN, "CONSTI %d", 
		    getConstVal(arg)->String.strlen);
		emitStmt(STMT_LEN, "CALL 0, %s", proc);
		emitComment("Kick params off the stack.");
		emitStmt(STMT_LEN, "ADJUST -2");
	default:
		break;
	}
}
