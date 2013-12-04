/*
 * Module implementing functions generating asc code for performing 
 * const, variable, procedure and function declarations.
 */

#include "EmitDecls.h"

/*
 * Creates asc statement necessary to make room on the stack for the given
 * variable.
 * Parameters
 *		s: the symbol for whom we need to declare space on the stack
 */
void emitVarDecl(Symbol *s)
{
	CHECK_CAN_EMIT(s);

	emitComment("Make room on the stack for new var %s", s->name);	
	emitStmt(STMT_LEN, "ADJUST %d", s->size);

}

/*
 * Creates asc statement necessary to make room on the stack for the given
 * constant and stores the value of the given constant in the location
 * allocated.
 * Parameters:
 *		s: the constant symbol whose value we need to store
 */
void emitConstDecl(Symbol *s)
{
	CHECK_CAN_EMIT(s);

	emitComment("Make room on the stack for new const %s.", s->name);
	emitStmt(STMT_LEN, "ADJUST %d", s->size);

	switch (getType(s)) {
	case BOOLEAN_T:
		emitIntConstDecl(s, getConstVal(s)->Boolean.value);
		break;
	case CHAR_T:
		emitIntConstDecl(s, getConstVal(s)->Char.value);
		break;
	case INTEGER_T:
		emitIntConstDecl(s, getConstVal(s)->Integer.value);
		break;
	case REAL_T:
		emitRealConstDecl(s, getConstVal(s)->Real.value);
		break;
	case STRING_T:
		emitStringConstDecl(s);
		break;
	default:
		/* Should not be reached */
		break;
	}

}

/*
 * Creates asc statement necessary to make room on the stack for the given
 * integer constant and stores the value of the constant in the location
 * allocated.
 * Parameters:
 *		s : the integer constant symbol whose value is to be stored
 *		value : the integer value of the constant symbol s 
 *
 */
void emitIntConstDecl(Symbol *s, int value)
{
	emitComment("Push const val = %d on stack, pop it into place.", value);
	emitStmt(STMT_LEN, "CONSTI %d", value);
	emitStmt(STMT_LEN, "POP %d[%d]", s->offset, s->lvl);
}

/*
 * Creates asc statement necessary to make room on the stack for the given
 * real constant and stores the value of the constant in the location
 * allocated.
 * Parameters:
 *		s : the real constant symbol whose value is to be stored
 *		value : the real value of the constant symbol s 
 *
 */
void emitRealConstDecl(Symbol *s, float value)
{
	emitComment("Push const val = %f on stack, pop it into place.", value);
	emitStmt(STMT_LEN, "CONSTR %f", value);
	emitStmt(STMT_LEN, "POP %d[%d]", s->offset, s->lvl);	
}


void emitStringConstDecl(Symbol *s)
{
	emitComment("Creating named string const decl %s", s->name);
	emitPushAnonConstValue(s);
	emitStmt(STMT_LEN, "POP %d[%d]", s->offset, s->lvl);
}

