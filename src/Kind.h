#ifndef KIND_H
#define KIND_H

#include "ParamArray.h"
/*
 * The kind values an entry in the symbol table can take.
 */
typedef enum {
	CONST_KIND,	/* constant value */
	FUNC_KIND,	/* function declaration */
	PROC_KIND,	/* procedure declaration */
	TYPE_KIND,	/* type declaration */
	VAR_KIND	/* variable declaration */
} kind_t;


struct Procedure {
	struct ParamArray params;

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
	struct symbol *return_t;
	/* flag for checking if anything is returned? */	

};


struct Const {
	type_t type;		/* the type of the const */
	void *typePtr;		/* pointer to the strcut of const type */
};




/* Do we need a variable struct?  Keep this here just in case */
struct Variable {
	
};

#endif
