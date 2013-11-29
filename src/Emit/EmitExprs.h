/*
 * Module implementing functionality to generate asc code for operations
 * common to all types of expressions.
 */
#ifndef EMITEXPRS_H
#define EMITEXPRS_H
#include "EmitUtils.h"

void emitArrayElementLocation(Symbol *, Symbol *);
void emitAssignmentOp(Symbol *, Symbol *);
void emitPushVarAddress(Symbol *);
void emitPushVarValue(Symbol *);
void emitPushConstValue(Symbol *);
void emitPushSymbolValue(Symbol *);
void emitPushArrayLocationValue(Symbol *);

#endif
