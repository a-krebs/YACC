%{
/*******************************************************************************
			Lexical Entites for YACC-PAL			
********************************************************************************/

#include <stdlib.h>


#include "Error.h"
#include "ErrorLL.h"
#include "Symbol.h"
#include "Globals.h"

#ifndef LEXTEST_DEBUG
#include "parser.tab.h"
#endif

#if LEXTEST_DEBUG
#include "tokenTestParser.tab.h"
#endif

/* re-set max token size */
#undef YYLMAX
#define YYLMAX 10240

extern YYABORT;
extern int nErrors;
int colno = 1;
extern void yyerror(char *);
extern unsigned long long whileLoopDepth;

/* 
 * Flag to set if we're in constant declaration.
 * 
 * This will enable/disable parts of the grammar. Specifically, when inDecl == 1
 * the var production will not reduce to a function invokation.
 */
int inDecl = 0;
%}

%option yylineno
%pointer yytext

%x INSIDE_BLOCK_COMMENT
%x INSIDE_STRING_WITH_NEWLINE

%%

%{
	if (nErrors >= MAXERRORS) {
		fprintf(stderr, "Maximum number of errors recorded. Parsing "
		    "will stop.\n");
		return 0;

	}
	colno += yyleng;
#if DEBUG
	printf("yylineno = %d, colno = %d\n", yylineno, colno);
	printf("Current Token: %s\n", yytext);
	printf("\n");

#endif

%}

[ \t]                   { colno += strlen(yytext); }
"//"[^\n]*              { colno = (1);
                        /* () around 1 to make vim
                         * syntax highlighting happy
                         */
                        }

"}"             { colno++;
                  struct Error *e = recordError("Closing comment brace '}' "
                  "found without matching '{'", yylineno, colno, SYNTAX);
                  printError(e);
#if DEBUG
                  printf("'}' FOUND WITHOUT MATCHING '{'\n");
#endif
                }

<INITIAL>"{"                    {
				  BEGIN(INSIDE_BLOCK_COMMENT);
				  colno++;
#if DEBUG
				  printf("BEGIN BLOCK COMMENT\n");
#endif
				}

<INSIDE_BLOCK_COMMENT>"}"	{ 
				  BEGIN(INITIAL);
				  colno++;
#if DEBUG
				  printf("END BLOCK COMMENT\n");
#endif
				}

<INSIDE_BLOCK_COMMENT>[^}]+	{ 
				  colno += strlen(yytext);
#if DEBUG
				  printf("INSIDE BLOCK COMMENT\n");
#endif
				}

<INSIDE_BLOCK_COMMENT><<EOF>>   {
                                  BEGIN(INITIAL);
                                  yyerror("EOF encountered inside block \
comment.");
				  return 0; 
				}


[0-9]+((\.[0-9]+([E][+-]?[0-9]+)?)|([E][+-]?[0-9]+)) { 
#ifndef LEXTEST_DEBUG
				  yylval.real = atof(yytext); 
#endif
				  colno += strlen(yytext);
				  return(REAL_CONST);
				}

[0-9]+                          {
				  yylval.integer = atoi(yytext);
#if DEBUG
				  colno += strlen(yytext);
#endif
				  return(INT_CONST);
				}

<INITIAL>"'"((([^'\\])|(\\['tn\\]))*(\n)+(([^'\\])|(\\['tn\\]))*)+"'" {
#if DEBUG
				printf("STRING LITERAL WITH NEWLINE FOUND\n");
#endif
				yytext = NULL;
				yyerror("Multiline string literal detected.");
				/* 
				 * We know it's an invalid string, but we'll
				 * continue compilation
				 * as though it was valid.
				 */
				return(STRING_CONST);
				}

"'"(([^'\\])|(\\['tn\\]))*"'"		{
#if DEBUG
				  printf("STRING FOUND\n");
#endif	
				  yylval.string = strdup(yytext);
				  return(STRING_CONST);
				}

":="				{ return(ASSIGN); }
"and"				{ return(AND); }
"continue"			{ return(CONTINUE); }
"end"				{ return(END); }
"mod"				{ return(MOD); }
"procedure"			{ return(PROCEDURE); }
"type"				{ return(TYPE); }
"array"				{ return(ARRAY); }
"div"				{ return(DIV); }
"exit"				{ return(EXIT); }
"not"				{ return(NOT); }
"program"			{ return(PROGRAM); }
"var"				{ return(VAR); }
"begin"				{ return(_BEGIN); }
"do"				{ return(DO);}
"function"			{ return(FUNCTION); }
"of"				{ return(OF); }
"record"			{ return(RECORD); }
"while"				{ whileLoopDepth++;
				  return(WHILE); }
"const"				{ return(CONST); }
"else"				{ return(ELSE); }
"if"				{ return(IF); }
"or"				{ return(OR); }
"then"				{ return(THEN); }
"="				{ return(EQUAL); }
"<>"				{ return(NOT_EQUAL); }
"<"				{ return(LESS); }
"<="				{ return(LESS_OR_EQUAL); }
">="				{ return(GREATER_OR_EQUAL); }
">"				{ return(GREATER); }
"+"				{ return(PLUS); }
"-"				{ return(MINUS); }
"*"				{ return(MULTIPLY); }
"/"				{ return(DIVIDE); }
"("				{ return(L_PAREN); } 
")"				{ return(R_PAREN); }
".."				{ return(RANGE); }
"."				{ return(PERIOD); }
";"				{ return(SEMICOLON); }
":"				{ return(COLON); }
"["				{ return(LS_BRACKET); }
"]"				{ return(RS_BRACKET); }
","				{ return(COMMA); }
[a-zA-Z][a-zA-Z0-9]*		{ yylval.id = strdup(yytext);
				  if (inDecl == 0) {
				  	return(ID);
				  } else {
					return(DECL_ID);
				  }
				}
\n 				{ 
				  colno = 1;
				}

.                               {
#ifndef LEXTEST_DEBUG
                                  yyerror("Unrecognized token(s)");
#endif
                                  return(UNREC);
}

%{


%}
