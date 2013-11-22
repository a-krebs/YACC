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

#define N_PREDEF_FUNCS 22

char *ascFiles[N_PREDEF_FUNCS] = {
	"__abs.asc",
	"__arctan.asc",
	"__chr.asc",
	"__cos.asc",
	"__factorial.asc",
	"__is_bad_real.asc",
	"__ln.asc",
	"__odd.asc",
	"__ord.asc",
	"__exp.asc",
	"__pow.asc",
	"__pred.asc",
	"__read.asc",
	"__readln.asc",
	"__trunc.asc",
	"__sin.asc",
	"__sqr.asc",
	"__sqrt.asc",
	"__succ.asc",
	"__round.asc",
	"__write.asc",
	"__writeln.asc"
};

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
static char masterFile[] = "__preDefAsc.asc";

static char *getText(char *);

static void execErr(char *, int *);
static void forkAndRun(char *);
static void fnfErr(char *);
static void makeMasterFile();
static void printHeader(char *);
static void runTest(char *);
static void setUpTest(char *, char *);

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

	makeMasterFile();
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
	setUpTest("__absTests.asc", "testAbs.asc");
	runTest("__abs");
	    
	return 0;	
}

int
testChr()
{
	setUpTest("__chrTests.asc", "testChr.asc"); 
	runTest("__chr");
	return 0;
}

int
testCos()
{
	setUpTest("__cosTests.asc", "testCos.asc");
	runTest("__cos");
	return 0;

}

int
testExp()
{
	setUpTest("__expTests.asc", "testExp.asc");
	runTest("__exp");
	return 0;
}

int
testLn()
{
	setUpTest("__lnTests.asc", "testLn.asc");
	runTest("__ln");
	return 0;
}

int
testPred()
{
	setUpTest("__predTests.asc", "testPred.asc");
	runTest("__pred");
	return 0;

}

int
testRound()
{
	setUpTest("__roundTests.asc", "testRound.asc");
	runTest("__round");
	return 0;
}

int
testSin()
{
	setUpTest("__sinTests.asc", "testSin.asc");
	runTest("__sin");
	return 0;
}


int
testSucc()
{
	setUpTest("__succTests.asc", "testSucc.asc");
	runTest("__succ");
	return 0;

}

int
testSqrt()
{
	setUpTest("__sqrtTests.asc", "testSqrt.asc"); 
	runTest("__sqrt");
	return 0;
}

int
testTrunc()
{
	setUpTest("__truncTests.asc", "testTrunc.asc");
	runTest("__trunc");
	return 0;
}

int
testWrite()
{
	setUpTest("__writeTests.asc", "testWrite.asc");
	runTest("__write");
	return 0;
}

int
testWriteln()
{
	setUpTest("__writelnTests.asc", "testWriteln.asc");
	runTest("__writeln");
	return 0;
}


static void
setUpTest(char *testsFile, char *outFile)
{
	memset(tests, '\0', LEN);
	memset(out, '\0', LEN);
	strcpy(tests, testDir); 
	strcpy(out, testDir);
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
	

	/* Append ASC code for tests for given function */
	buf = getText(tests);	
	fprintf(fp, "%s\n", buf);

	/* Print header to stdout to inform tester about expected output */
	printHeader(buf);
	free(buf);

	/* */
	buf = getText(masterFile);
	fprintf(fp, "%s\n", buf);

	fclose(fp);
	
	forkAndRun(out);

	printf("\n# %s TEST COMPLETE #############################\n\n", 
	    funcName);
	fflush(stdout);	

}

static void
makeMasterFile()
{
	char *buf = NULL;
	FILE *fp = NULL;
	int i;

	fp = fopen(masterFile, "w");

	if (!fp) fnfErr(masterFile);

	for (i = 0; i < N_PREDEF_FUNCS; i++) {
		memset(code, '\0', LEN);
		strcpy(code, funcCodeDir);
		strcat(code, ascFiles[i]); 
		buf = getText(code);
		fprintf(fp, "%s\n", buf);
		free(buf);
	}
	fclose(fp);
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
