
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "Hash.h"
/*
 * Mirrors design ideas in Piotr's nodes (CheckingAttributes.pdf)
 */

typedef enum {
	VOID_T,		/* special type for return type of procedures */
	ARRAY_T,
	BOOLEAN_T,
	CHAR_T,
	INTEGER_T,
	REAL_T,
	RECORD_T,	
	SCALAR_T,
	SCALARINT_T,
	STRING_T,
	SUBRANGE_T,
} type_t;

typedef union type_union {
	struct Array * Array;
	struct Boolean * Boolean;
	struct Char * Char;
	struct Integer * Integer;
	struct Function *Function;
	struct Procedure *Procedure;
	struct Real * Real;
	struct Record * Record;
	struct Scalar * Scalar;
	struct String * String;
	struct Subrange * Subrange;
} Type;


/*
 * The kind values an entry in the symbol table can take.
 */
typedef enum {
	CONST_KIND,	/* constant value */
	FUNC_KIND,	/* function declaration */
	PARAM_KIND,	/* parameter declaration */
	PROC_KIND,	/* procedure declaration */
	TYPE_KIND,	/* type declaration */
	VAR_KIND	/* variable declaration */
} kind_t;

/*
 * TODO: params need to be a kind
 * TODO: need function newVarFromParam..... NO! just use newVariableSym
 *	 and pass it param->name, typeSymPtr
 */
struct ParamKind {
	struct Symbol *typeSym;
	int byRef;	/* flaged indicated if the param was passed by ref */	
};

struct Param {
	char *name;
	type_t type;
	struct Symbol *typeSym;
	
};

struct ParamArray {
	struct Param **data;
	unsigned int len;
	unsigned int nElements;
};

struct ElementArray {
	void **data;
	unsigned int len;
	unsigned int nElements;
};


struct Array {
	struct Symbol *baseTypeSym;	/* pointer to struct of base type */
	struct Symbol *indexTypeSym;	/* pointer to struct of index type */
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
	struct ParamArray *params;
	struct Symbol  *returnTypeSym;

};

struct Integer {
	int value;		/* value only needed when being pointed to
				 * by an object of kind CONST_KIND */
};

struct Procedure {
	struct ParamArray *params;
};


struct Real {
	double value;		/* value only needed when being pointed to
				 * by an object of kind CONST_KIND */
};


struct String {
	char * str;
	unsigned int strlen;
};
struct Subrange {
	int high;
	int low;
	struct Symbol *baseTypeSym; /* pointer to struct of type of subrange indices */
};

struct Scalar {
	struct ElementArray *consts;
};



struct Record { 
	/* each record implemented as its own symbol table */
	struct hash *hash;
};

/*
 * To be used when were are making an anonymous constant type (which will
 * be used to make a symbol).  We could not simply reuse the Type union
 * that is a union of pointers and would have required that we allocate
 * memory inside actions in the grammar file which I felt was a bad idea.
 */
typedef union anonymous_constant_value {
	struct Boolean Boolean;
	struct Char Char;
	struct Integer Integer;
	struct Real Real;
	struct String String;
} AnonConstVal;

typedef union kind_union {
	struct ConstantKind * ConstKind;
	struct FunctionKind * FuncKind;
	struct ParamKind * ParamKind;
	struct ProcedureKind * ProcKind;
	struct TypeKind * TypeKind;
	struct VariableKind * VarKind;
} Kind;

struct ConstantKind {
	struct Symbol *typeSym;
	AnonConstVal value;		
};

struct FunctionKind {
	struct Symbol *typeSym;
	struct ElementArray *params;
};

struct ProcedureKind {
	struct ElementArray *params;
};

struct TypeKind {
	Type typePtr;
	type_t type;
};

struct VariableKind {
	struct Symbol *typeSym;
	int byRef;		/* flag indicated if the variable is a value
				 * or a reference to a value (e.g., an address)
				 */
};


/*
 * The object stored at a hash element in the symbol table.
 * Here we define the name of the entry, what kind it is (e.g., VAR, CONST,
 * PARAM, ... ), and a pointer to the particular type of kind it is. 
 */
struct Symbol {
	char *name;	/* the name associated with the entry */
	kind_t kind;	/* the kind associated with this entry */
	Kind kindPtr;	/* kind specific description of symbol */
	int lvl;	/* the lexical level at which the entry is defined */
	int typeOriginator; /* set if the symbol is the originator of its kindPtr*/
	int offset;	/* the offset (i.e., position in the stack offset from
			 * display register) at which the variable appears */
	int size;	/* the ASC memory units this symbol occupies in the
			 * stack */
	struct Symbol *next;	
};

/* typedef Symbol to make it easier to work with */
typedef struct Symbol Symbol;
typedef struct Param Param;
/* typedef a proxy type to hold the same information as symbol, but
 * to not be stored in the symbol table. It is used as an intermediate value
 * when traversing the parse tree. 
 */
typedef Symbol ProxySymbol;


#endif
