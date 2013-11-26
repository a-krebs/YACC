/*
 * Module implementing ASC code generating functionality.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Emit.h"

char *getAscFileName(char *palFileName)
{
	int len = 0;
	char *ascFileName = NULL;

	len = strlen(palFileName) + 1;
	if (len < 5) return NULL;	/* len < 5 => no .pal exten on file */

	ascFileName = calloc(len, sizeof(char));

	strncpy(ascFileName, palFileName, len);
	strncpy(ascFileName + len - 5, ".asc", 4);

	return ascFileName;
}



/*
 * Emits the var code necessary to 
 */
