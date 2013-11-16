/*
 * Unit tests for the pre-defined asc functions.
 */

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#include "testPreDefAsc.h"

static char execAsc[] = "./bin/asc";

static char absTestFile[] = "./test/unit/asctests/testAbs.asc";
static char absFile[] = "./src/asc/__abs.asc";

static void execErr(char *);
static void fnfErr(char *);
static char *getFuncCode(char *);

int
testAbs()
{
	//TODO: get this working
	/*
	char *absCode = NULL;
	pid_t pid;
	int status;
	
	FILE *fp = fopen(absTestFile, "w");
	if (!fp) fnfErr(absTestFile);
	absCode = getFuncCode(absFile);

	printf("TESTING __abs----------------------------------------------\n");
	fprintf(fp, "\t\tGOTO testStart\n");
	fprintf(fp, "%s\n", absCode);
	fclose(fp);

	pid = fork();
	if (!pid) {
		if (execlp(execAsc, absTestFile) == -1) {
			warn("Failed to execute %s in asc", absFile);
			status = -1;
		}  
	} else waitpid(pid, &status, 0);

	printf(" - __abs test complete ------------------------------------\n");	
	return status;	*/
	return 0;
}

static void
execErr(char *fname)
{
	err(1, "Failed to execute %s in asc", fname);
	exit(1);
}

static void
fnfErr(char * fname)
{
	err(1, "Could not open file %s for testing.", fname);
	exit(1);
}

static char *
getFuncCode(char *fname)
{
	long flen = 0;
	char *funcCode = NULL;
	FILE *fp = fopen(fname, "r");
	size_t bytesRead;
	if (!fp) fnfErr(fname);
	
	/* Get length of file so we know how much memory to allocate for buf */
	fseek(fp, 0L, SEEK_END);
	flen = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	funcCode = calloc(flen, sizeof(char));
	while ((bytesRead = fread(funcCode, sizeof(char), flen, fp)) > 0) ;
	return funcCode;	
}
