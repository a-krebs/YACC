/*
 * Module implementing writing generated ASC code to file.
 */
#include "EmitToFile.h"


/*
 * Write generated code to file.
 *
 * Parameters:
 * 	fileName: name of the .asc file to which to write.
 * Return:
 * 	0 on success,
 * 	non-zero otherwise
 */
int emitToFile(char *fileName) {
	FILE *ascfp = NULL;

	if (doNotEmit) {
		return 1;
	}

	/* open the file */
	ascfp = fopen(fileName, "w");

	/* write the emitted code to file */
	writeStmtLL(ascfp, stmts);

	/* close the file */
	if (fclose(ascfp) != 0) {
		err(EXIT_FAILURE, "File IO error.");
	}

	return 0;
}
