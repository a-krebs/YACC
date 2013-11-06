#ifndef KIND_H
#define KIND_H

#include "Definitions.h"


struct ConstantKind *allocateConstantKind();
struct FunctionKind *allocateFunctionKind();
struct ProcedureKind *allocateProcedureKind();
struct TypeKind *allocateTypeKind();
struct VariableKind *allocateVariableKind();
void allocateKindPtr(Symbol *);
void allocationErrorCheck(void *);

AnonConstVal *getConstVal(Symbol *);
AnonConstVal *copyConstVal(AnonConstVal *, type_t);
#endif
