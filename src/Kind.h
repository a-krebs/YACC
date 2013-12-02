#ifndef KIND_H
#define KIND_H

#include "Definitions.h"

/*
 * Allocate space for ConstantKind
 * 
 * Parameter: none
 * 
 * Return: pointer to struct ConstantKind
 */
struct ConstantKind *allocateConstantKind();

/*
 * Allocates memory for the kindPtr of the symbol based on the kind of the
 * symbol passed.
 * WARNING: make sure you set s->kind BEFORE calling this function.
 * 
 * Parameter: pointer to symbol
 *
 * Return: void
 */
struct FunctionKind *allocateFunctionKind();

/*
 * Allocate space for ProcedureKind
 * 
 * Parameter: none
 * 
 * Return: pointer to struct ProcedureKind
 */
struct ProcedureKind *allocateProcedureKind();

/*
 * Allocate space for TypeKind
 * 
 * Parameter: none
 * 
 * Return: pointer to struct TypeKind
 */
struct TypeKind *allocateTypeKind();

/*
 * Allocate space for VariableKind
 * 
 * Parameter: none
 * 
 * Return: pointer to struct VariableKind
 */
struct VariableKind *allocateVariableKind();

/* not used */
void allocateKindPtr(Symbol *);

/* not used */
struct ParamKind * allocateParamKind();

/*
 * Check if the memory allocation successful or not
 * 
 * Parameter: pointer to struct
 * 
 * Return: void
 */
void allocationErrorCheck(void *);

/*
 * Acquire value of an anonymous constant
 * 
 * Parameter: pointer to symbol
 * 
 * Return: pointer to AnonConstVal
 */
AnonConstVal *getConstVal(Symbol *);

double getSimpleConstVal(Symbol *);

/*
 * Makes a copy of the given AnonConstVal based on type -- used when
 * creating a const symbol from a proxy symbol.
 * 
 * Parameter: pointer to new AnonConstVal, pointer to AnonConstVal, 
 * and type of AnonConstVal
 * 
 * Return: void
 */
void copyConstVal(AnonConstVal *, AnonConstVal *, type_t);
#endif
