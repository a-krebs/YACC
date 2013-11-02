
#include <stdio.h>
#include <stdlib.h>

#ifndef TYPE_H
#define TYPE_H

/*
 * Defines the pre-defined types used by the compiler.
 */

/*
 * Notes/thoughts:
 *	-PARAM =?= Vvar with flag that tells us if it was
 *	 passed by reference or not???  Do we actually need to know the params
 *	 for a function ? ..... yes: for semantic checking at invocation
 *
 *
 *	-Does this class pass divine judgment upon the souls of the living
 * 	 and the dead? (smellin like a god class brah)
 */

/*
 * The types of a values which can be associated with various kinds.
 */
typedef enum {
	ARRAY_T,
	BOOLEAN_T,
	CHAR_T,
	INTEGER_T,
	REAL_T,
	RECORD_T,	
	SCALAR_T,
	SUBRANGE_T,
} type_t;

typedef union type_union {
	struct Array * Array;
	struct Boolean * Boolean;
	struct Char * Char;
	struct Integer * Integer;
	struct Real * Real;
	struct Record * Record;
	struct Scalar * Scalar;
	struct Subrange * Subrange;
} Type;

struct Param {
	char *name;
	type_t type;
	Type typePtr;
};

/* Param Array defined here to avoid incestuous circular .h includes :( */
struct ParamArray {
	struct Param **data;
	unsigned int len;
	unsigned int nElements;
};


struct Array {
	type_t baseType;	/* type of elements of array (e.g., array of 
				 * char => baseType = CHAR_T */
	void *baseTypePtr;	/* pointer to struct of base type */
	type_t indexType;	/* type which indexes the array */
	void *indexTypePtr;	/* pointer to struct of index type */
};

struct Boolean {
	int value;		/* value only needed when being pointed to
				 * by an object of kind CONST_KIND */
};

struct Char {
	char value;		/* value only needed when being pointed to
				 * by an object of kind CONST_KIND */
};

/*
 * TODO: need to check if function actually returns something (i.e., does it
 *	 reference its own id as l-val in an assignment operation?) ; we won't
 *	 have time to implement checking if there is a execution path
 * 	 which results in no return type being set (and thus setting warning/
 *	 error)
 */
struct Function {
	struct ParamArray params;
	Type *returnType;

};

struct Integer {
	int value;		/* value only needed when being pointed to
				 * by an object of kind CONST_KIND */
};

struct Procedure {
	struct ParamArray params;
};


struct Real {
	double value;		/* value only needed when being pointed to
				 * by an object of kind CONST_KIND */
};

struct Subrange {
	int high;
	int low;
	type_t baseType;  /* type of subrange indices */
	Type baseTypePtr; /* pointer to struct of type of subrange indices */
};

struct Scalar {
	/* 
	 * Array of pointers to ids of consts in scalar list 
	 */	
};



struct Record {
	/* each record implemented as its own symbol table */
};


/* Function declarations */
int isOrdinal(type_t);
#endif
