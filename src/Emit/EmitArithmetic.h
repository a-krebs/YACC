/*
 * Module implementing functions generating asc code for performing 
 * arithmetic operations.
 */
#ifndef EMITARITHMETIC_H
#define EMITARITHMETIC_H

#include <err.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../Error.h"
#include "../Definitions.h"
#include "../Kind.h"
#include "../StmtLL.h"
#include "../SymbolAPI.h"
#include "../Type.h"

#include "EmitExprs.h"
#include "EmitUtils.h"

#ifdef TESTBUILD
	#include "tokens.h"
#else
	#ifdef LEXTEST_DEBUG
		#include "tokenTestParser.tab.h"
	#else
		#include "parser.tab.h"	/* token definitions used in operator compat checks */
	#endif
#endif


#define ARITHMETIC_RESULT_INTEGER 0
#define ARITHMETIC_RESULT_REAL 1

extern int doNotEmit;

//void emitArithmeticPrep(Symbol *, Symbol *, int *);
void emitAddition(Symbol *, Symbol *);
void emitSubtraction(Symbol *, Symbol *);
void emitMultiplication(Symbol *, Symbol *);
void emitDivision(Symbol *, Symbol *, int);
void emitMod(Symbol *, Symbol *);
void emitITOR(Symbol *);
void emitRTOI(Symbol *);
void genericArithConstruct(Symbol *, Symbol *, char *, 
	char *, char *, int);
void emitArithmCheckAndComment(Symbol *, Symbol *, char *);


#endif
