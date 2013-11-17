/*
 * Unit tests for the pre-defined asc functions.
 */

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#include "testPreDefAsc.h"

/* env variables */
static char *oldPath;
static char newPath[1024];


static char execAsc[] = "bin/asc";

static char absTestFile[] = "./test/unit/asctests/testAbs.asc";
static char absAscFile[] = "./src/asc/__abs.asc";
static char absTests[] = "./test/unit/asctests/__absTests.asc";

static void execErr(char *, int *);
static void fnfErr(char *);
static char *getText(char *);


/*
 * Append the current working directory to the environment Path variable
 * such that exec() call will find the asc executable.
 */
void setUpAscTests() 
{
	char cwd[1024];

	/* get the current working directory */
	getcwd(cwd, sizeof(cwd) - 1);

	/* get the current environment path variable */
	oldPath = getenv("PATH");
	strcpy(newPath, oldPath);

	/* append cwd to path variable so asc executable can be found by exec */
	strcat(newPath, cwd);

	/* set path var */
	setenv("PATH", newPath, 1);
}

/*
 * Resets the path variable to its original value.
 */
void tearDownAscTests()
{
	unsetenv("PATH");
	setenv("PATH", oldPath, 1);
}

int
testAbs()
{
	char *buf = NULL;
	int status;	
	FILE *fp = fopen(absTestFile, "w");
	pid_t pid;
	
	if (!fp) fnfErr(absTestFile);
	buf = getText(absAscFile);

	printf("# TESTING __abs.asc #\n");
	fprintf(fp, "\t\tGOTO test_start\n");

	/* Append ASC code for abs() to file */	
	fprintf(fp, "%s\n", buf);
	free(buf);

	/* Append ASC code for abs tests to file */
	buf = getText(absTests);	
	fprintf(fp, "%s\n", buf);
	free(buf);

	fclose(fp);

	pid = fork();
	if (!pid) {
		if (execlp(execAsc, execAsc, absTestFile) == -1) {
			execErr(absTestFile, &status);
		}
	} else waitpid(pid, &status, 0);

	printf(" # __abs TEST COMPLETE # \n\n");
	fflush(stdout);	
	return status;	
}

static void
execErr(char *fname, int *status)
{
	warn("Failed to execute asc with %s", fname);
	*status = -1;
}

static void
fnfErr(char * fname)
{
	err(1, "Could not open file %s for testing.", fname);
	exit(1);
}

static char *
getText(char *fname)
{
	long flen = 0;
	char *buf = NULL;
	FILE *fp = fopen(fname, "r");
	size_t bytesRead;
	if (!fp) fnfErr(fname);
	
	/* Get length of file so we know how much memory to allocate for buf */
	fseek(fp, 0L, SEEK_END);
	flen = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	buf = calloc(flen, sizeof(char));
	while ((bytesRead = fread(buf, sizeof(char), flen, fp)) > 0) ;
	return buf;	
}
