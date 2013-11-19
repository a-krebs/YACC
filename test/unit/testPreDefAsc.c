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

/* file locations */
static char execAsc[] = "bin/asc";
static char funcCodeDir[] = "src/asc/";
static char testDir[] = "test/unit/asctests/";

/* 
 * Global strings used when running test -- globals used to make
 * setting up a test run more convenient
 */
static char code[LEN];
static char tests[LEN];
static char out[LEN];


static char *getText(char *);

static void execErr(char *, int *);
static void forkAndRun(char *);
static void fnfErr(char *);
static void printHeader(char *);
static void runTest(char *);
static void setUpTest(char *, char *, char *);

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
	setUpTest("__abs.asc", "__absTests.asc", "testAbs.asc");
	runTest("__abs");
	    
	return 0;	
}

int
testChr()
{
	setUpTest("__chr.asc", "__chrTests.asc", "testChr.asc"); 
	runTest("__chr");
	return 0;
}

int
testPred()
{
	setUpTest("__pred.asc", "__predTests.asc", "testPred.asc");
	runTest("__pred");
	return 0;

}

int
testSucc()
{
	setUpTest("__succ.asc", "__succTests.asc", "testSucc.asc");
	runTest("__succ");
	return 0;

}

int
testSqrt()
{
	setUpTest("__sqrt.asc", "__sqrtTests.asc", "testSqrt.asc"); 
	runTest("__sqrt");
	return 0;
}


static void
setUpTest(char *codeFile, char *testsFile, char *outFile)
{
	memset(code, '\0', LEN);
	memset(tests, '\0', LEN);
	memset(out, '\0', LEN);
	strcpy(code, funcCodeDir);
	strcpy(tests, testDir); 
	strcat(code, codeFile);
	strcat(tests, testsFile);
	strcat(out, outFile);

}

static void
runTest(char *funcName)
{
	char *buf = NULL;
	FILE *fp = fopen(out, "w");
	
	if (!fp) fnfErr(out);
	buf = getText(code);

	printf("# TESTING %s ####################################\n", funcName);
	fflush(stdout);	
	
	fprintf(fp, "\t\tGOTO test_start\n");

	/* Append ASC code for given function */	
	fprintf(fp, "%s\n", buf);
	free(buf);

	/* Append ASC code for tests for given function */
	buf = getText(tests);	
	fprintf(fp, "%s\n", buf);
	
	/* Print header to stdout to inform tester about expected output */
	printHeader(buf);
	free(buf);

	fclose(fp);
	
	forkAndRun(out);

	printf("\n# %s TEST COMPLETE #############################\n\n", 
	    funcName);
	fflush(stdout);	

}


/*
 * Prints to stdout the comment header for the test file which was read into
 * buf. 
 */
static void
printHeader(char *buf)
{
	while (1) {
		if (*buf != '#') break;
		while (*buf != '\n') printf("%c", *buf++);
		printf("%c", *buf++);
	}
	printf("\n");	/* one more newline to make things easer to read */
	fflush(stdout);
}

static void
forkAndRun(char *testFileName)
{
	int status = 0;
	pid_t pid;
	pid = fork();
	if (!pid) {
		if (execlp(execAsc, execAsc, testFileName) == -1) {
			execErr(testFileName, &status);
		}
	} else waitpid(pid, &status, 0);
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
