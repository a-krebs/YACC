%{
/*******************************************************************************
			Lexical Entites for YACC-PAL			
********************************************************************************/

#include <stdlib.h>

#include "parser.tab.h"
#undef YYLMAX
#define YYLMAX 10240
%}

%option yylineno

%x INSIDE_BLOCK_COMMENT
%x INSIDE_STRING

%%

%{
#if DEBUG
	printf("yylineno = %d\n", yylineno);
	printf("Current Token: %s\n", yytext);
#endif
%}

[ \t]				{ ; }
"//"[^\n]*			{ ; }

<INITIAL>"{"			{ BEGIN(INSIDE_BLOCK_COMMENT); }
<INSIDE_BLOCK_COMMENT>"}"	{ BEGIN(INITIAL); }
<INSIDE_BLOCK_COMMENT>[^}\n]+	{ ; }
<INSIDE_BLOCK_COMMENT><<EOF>>	{ return; }

^("+"|"-")?([0-9]*)(".")?[0-9]+(E("-"|"+")?[0-9]+)? { 
				yylval.real = atof(yytext); 
				return(REAL); }

<INITIAL>"'"			{ BEGIN(INSIDE_STRING);
				  printf("STRING FOUND\n");
				}

<INSIDE_STRING>([^'\\]*(?:\\.[^'\\]*)*)	{ 
				yylval.string = strdup(yytext);
				  return(STRING); 
				}

<INSIDE_STRING>\n		{
				printf("NEWLINE APPEARS INSIDE STRING");
				}

<INSIDE_STRING>"'"		{BEGIN(INITIAL);}

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
[a-zA-Z][a-zA-Z0-9]*		{ yylval.id = strdup(yytext);
				  return(ID); }
\n 				{ ; }
