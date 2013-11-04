#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "Kind.h"

/*
 * Allocates memory for the kindPtr of the symbol based on the kind of the
 * symbol passed.
 * WARNING: make sure you set s->kind BEFORE calling this function.
 */
void
allocateKindPtr(Symbol *s)
{
	if (!s) return;
	switch (s->kind) {
	case CONST_KIND: 
		s->kindPtr.ConstKind = allocateConstantKind();
		break;
	case FUNC_KIND:
		s->kindPtr.FuncKind = allocateFunctionKind();
		break;
	case PROC_KIND:
		s->kindPtr.ProcKind = allocateProcedureKind();
		break;
	case TYPE_KIND:
		s->kindPtr.TypeKind = allocateTypeKind();
		break;
	case VAR_KIND:
		s->kindPtr.VarKind = allocateVariableKind();
		break;	
	default:
		/* NOT REACHED */
		break;
	}	
}

struct ConstantKind *
allocateConstantKind()
{
	struct ConstantKind *ck = calloc(1, sizeof(struct ConstantKind));
	allocationErrorCheck(ck);
	return ck;
}

struct FunctionKind *
allocateFunctionKind()
{
	struct FunctionKind *fk = calloc(1, sizeof(struct FunctionKind));
	allocationErrorCheck(fk);
	return fk;
}

struct ProcedureKind *
allocateProcedureKind()
{
	struct ProcedureKind *pk = calloc(1, sizeof(struct ProcedureKind));
	allocationErrorCheck(pk);
	return pk;
}

struct TypeKind *
allocateTypeKind()
{
	struct TypeKind *tk = calloc(1, sizeof(struct TypeKind));
	allocationErrorCheck(tk);
	return tk;
}

struct VariableKind *
allocateVariableKind() 
{
	struct VariableKind *vk = calloc(1, sizeof(struct VariableKind));
	allocationErrorCheck(vk);
	return vk;
}


void
allocationErrorCheck(void *p)
{
	if (!p) {
		err(1, "Failed to allocate memory for kind ptr!");
		exit(1);
	}
}
