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

