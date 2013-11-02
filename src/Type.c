/*
 * Some nice comments about what this module is.
 *
 */

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Type.h"

/*
 * Determines if the given type_t is an ordinal type.
 */
int
isOrdinal(type_t type)
{
	if ((type == BOOLEAN_T) || (type == CHAR_T) || (type == INTEGER_T)) {
		return 1;
	}
	return 0;
}

/*
 * Set type pointer new to point to type old of type passed as arg.
 */
void
setTypePtr(Type *new, Type old, type_t type)
{
	switch (type) {

	case ARRAY_T:
		new->Array = old.Array;
		break;
	case BOOLEAN_T:
		new->Boolean->value = old.Boolean->value;
		new->Boolean = old.Boolean;
		break;
	case CHAR_T:
		new->Char->value = old.Char->value;
		new->Char = old.Char;
		break;
	case INTEGER_T:
		new->Integer->value = old.Integer->value;
		new->Integer = old.Integer;
		break;
	case FUNCTION_T:
		new->Function = old.Function;
		break;
	case PROCEDURE_T:
		new->Procedure = old.Procedure;
		break;	
	case REAL_T:
		new->Real->value = old.Real->value;
		new->Real = old.Real;
		break;
	case RECORD_T:
		new->Record = old.Record;
		break;
	case SCALAR_T:
		new->Scalar = old.Scalar;
		break;
	case SUBRANGE_T:
		new->Subrange = old.Subrange;
		break;
	default:
		/* Not reached */
		break;
	}
}

