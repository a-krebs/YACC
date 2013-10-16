%{
/*******************************************************************************
			Lexical Entites for YACC-PAL			
********************************************************************************/

#include <stdlib.h>


#include "Error.h"
#include "ErrorLL.h"

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

int colno = 1;
extern void yyerror(char *);
%}

%option yylineno

%x INSIDE_BLOCK_COMMENT
%x INSIDE_STRING_WITH_NEWLINE

%%

%{

	colno += yyleng;
#if DEBUG
	printf("yylineno = %d, colno = %d\n", yylineno, colno);
	printf("Current Token: %s\n", yytext);
	printf("\n");

#endif

%}

[ \t]				{ colno += strlen(yytext); }
"//"[^\n]*			{ colno = 1; }

"}"				{
				  recordError("Closing comment brace '}' \
				      found without matching '{'", yylineno, colno);
#if DEBUG
				  printf("'}' FOUND WITHOUT MATCHING '{'\n");
#endif

				}

<INITIAL>"{"			{ 
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
<INSIDE_BLOCK_COMMENT><<EOF>>	{ 
				  BEGIN(INITIAL);
				  recordError("EOF encountered inside block comment.", yylineno, colno);
				  return; 
				}

[0-9]+			{
				  yylval.integer = atoi(yytext);
#if DEBUG
				  colno += strlen(yytext);
#endif
				  return(INT_CONST);
				}

^("+"|"-")?([0-9]*)(".")?[0-9]+(E("-"|"+")?[0-9]+)? { 
#ifndef LEXTEST_DEBUG
				  yylval.real = atof(yytext); 
#endif
				  colno += strlen(yytext);
				  return(REAL_CONST);
				}


<INITIAL>"'"((([^'\\])|(\\.))*(\n)+(([^'\\])|(\\.))*)+"'" {
#if DEBUG
				printf("STRING LITERAL WITH NEWLINE FOUND\n");
#endif
				recordError("Newline characters cannot appear \
				    in strings.", yylineno, colno);
				/* 
				 * We know it's an invalid string, but we'll
				 * continue compilation
				 * as though it was valid.
				 */
				return(STRING_CONST);
				}

"'"(([^'\\])|(\\.))*"'"		{
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
"while"				{ return(WHILE); }
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
"integer"			{ return(INT); }
"char"				{ return(CHAR); }
"bool"				{ return(BOOL); }
"real"				{ return(REAL); }
[a-zA-Z][a-zA-Z0-9]*		{ yylval.id = strdup(yytext);
				  return(ID); 
				}
\n 				{ 
				  colno = 1; 
				}
.				{ 
				 
				  yyerror("Unrecognized token(s)");
	                     	  return(UNREC); 
				}

%{


%}
