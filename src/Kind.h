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

typedef union kind_union {
	struct Function * Function;
	struct Procedure * Procedure;
} Kind;

#endif
