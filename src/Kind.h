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
/*
 * Acquire the actual value of an anonymous constant symbol which is of a 
 * simple type.
 *
 * Parameter: pointer to symbol
 * 
 * Return: pointer to AnonConstVal
 */
double getSimpleConstVal(Symbol *);
/*
 * Assigning the actual value of an anonymous constant symbol which is of a 
 * simple type.
 *
 * Parameter: pointer to symbol
 * 
 * Return: pointer to AnonConstVal
 */
void setSimpleConstVal(Symbol *, double);

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

/*	Check whehter a function is invocked correctly by its name.
 *	
 *  Parameters: Symbol in function kind
 * 	Return: 1: invocation is correct
 *			0: invocation is wrong
 */
int isInvocInstance(Symbol *);

/* Ensure that the kind of the given sybmols are actually compatible with each other
 * before assigning one to the other one.
 * This function checks the following:
 *		Assigning to a TYPE_KIND Symbol 
 * areKindAssignCompat also be able to validate the correctness of function 
 * inovaction by calling isInvocInstance(). (May need to refactor this later)
 *
 *	Parameters: Symbol x on LHS
 *				Symbol y on RHS
 *
 *	Returns: 1 if two sym are compatible
 *			 0 if not
 */
int areKindAssignCompat(Symbol *, Symbol *);

#endif
