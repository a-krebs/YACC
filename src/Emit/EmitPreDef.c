/*
 * Module implementing functions for generating asc code to call pre-defined
 * functions.
 */

#include "EmitPreDef.h"

static void emitIOCall(char *, Symbol *);
static void emitRead(Symbol *, struct ElementArray *);
static void emitReadln(Symbol *, struct ElementArray *);
static void emitWrite(Symbol *, struct ElementArray *);
static void emitWriteln(Symbol *, struct ElementArray *);

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
			emitPushVarAddress(arg);
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
			emitPushVarAddress(arg);
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
	
}
static void emitWriteln(Symbol *s, struct ElementArray *args)
{
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
	default:
		break;
	}
}
