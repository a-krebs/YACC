/*
 * Module implementing functionality to generate asc code for operations
 * common to all types of expressions.
 */
#ifndef EMITEXPRS_H
#define EMITEXPRS_H
#include "EmitUtils.h"

#define NO_OP -1

void emitArrayElementLocation(Symbol *, Symbol *);
void emitAssignmentOp(Symbol *, Symbol *);
void emitPushVarAddress(Symbol *);
void emitPushVarValue(Symbol *);
void emitPushConstValue(Symbol *);
void emitPushSymbolValue(Symbol *);
void emitPushAddressValue(Symbol *);
void emitPushRecordFieldAddress(Symbol *, Symbol *);
void emitPushAnonConstValue(Symbol *);
void emitArrayAssignment(Symbol *, Symbol *);
void emitPushStringLiteralValue(Symbol *);
void emitPushStructuredVarValue(Symbol *);
#endif
