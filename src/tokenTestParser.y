%{

/*  Unit test rule for lexical entites */

#include <stdio.h>
#include <stdlib.h>

%}

/*For parsing the real number with 'E',
 *use char instead of double temporarily 
 */

%union{
	char character;
	char *string;
	char *id;
	char *real;
	int integer;
}

/* keywords */
%token AND CONTINUE PROCEDURE TYPE ARRAY _BEGIN END NOT
%token PROGRAM VAR DO FUNCTION OF RECORD WHILE CONST IF ELSE
%token OR THEN EXIT

/* 
 * Operators and relational operators 
 * (set type and associativity as needed)
 */
%token PLUS MINUS MULTIPLY MOD DIVIDE DIV 
%token EQUAL NOT_EQUAL LESS LESS_OR_EQUAL GREATER_OR_EQUAL GREATER

/* Types and identifiers. */
%token <character> CHAR
%token <id> ID
%token <real> REAL
%token <integer> INT
%token <string> STRING

/* etc */
%token ASSIGN COMMA L_PAREN R_PAREN LS_BRACKET RS_BRACKET PERIOD
%token SEMICOLON COLON RANGE

%%

program		:tokens_list 		
		;

tokens_list	:token
		|tokens_list token
		
token           :types_list 
		|operators_list
		|etc_list
		|keywords_list
		;

types_list	:CHAR
		|ID                     {printf("%s\n",$<id>1);}
		|INT                    {printf("%d\n",$<integer>1);}
		|REAL                   {printf("%s\n",$<real>1);}
		|STRING                 {printf("%s\n",$<string>1);}
		;

operators_list	:PLUS                   {printf("PLUS\n");}
		|MINUS                  {printf("MINUS\n");}
		|MULTIPLY               {printf("MULTIPLY\n");}
		|MOD                    {printf("MOD\n");}
		|DIVIDE                 {printf("DIVID\n");}        
		|DIV	                {printf("DIV\n");}
		|EQUAL                  {printf("EQUAL\n");}			
		|NOT_EQUAL		{printf("NOT_EQUAL\n");}
		|LESS			{printf("LESS\n");}
		|LESS_OR_EQUAL		{printf("LESS_OR_EQUAL\n");}
		|GREATER_OR_EQUAL	{printf("GREATER_OR_EQUAL\n");}
		|GREATER		{printf("GREATER\n");}
		;

etc_list	:ASSIGN		{printf("ASSIGN\n");}
		|COMMA		{printf("COMMA\n");}
		|L_PAREN	{printf("L_PAREN\n");}
		|R_PAREN	{printf("R_PAREN\n");}
		|LS_BRACKET	{printf("LS_BRACKET\n");}
		|RS_BRACKET	{printf("RS_BRACKET\n");}
		|PERIOD		{printf("PERIOD\n");}
		|SEMICOLON	{printf("SEMICOLON\n");}
		|COLON		{printf("COLON\n");}
		|RANGE		{printf("RANGE\n");}
		;

keywords_list	:AND		{printf("AND\n");}
		|CONTINUE	{printf("CONTINUE\n");}
		|PROCEDURE	{printf("PROCEDURE\n");}
		|TYPE		{printf("TYPE\n");}
		|ARRAY		{printf("ARRAY\n");}
		|_BEGIN		{printf("_BEGIN\n");}
		|END		{printf("END\n");}
		|NOT		{printf("NOT\n");}
		|PROGRAM	{printf("PROGRAM\n");}
		|VAR		{printf("VAR\n");}
		|DO		{printf("DO\n");}
		|FUNCTION	{printf("FUNCTION\n");}
		|OF		{printf("OF\n");}
		|RECORD		{printf("RECORD\n");}
		|WHILE		{printf("WHILE\n");}
		|CONST		{printf("CONST\n");}
		|IF		{printf("IF\n");}
		|ELSE		{printf("ELSE\n");}
		|OR		{printf("OR\n");}
		|THEN		{printf("THEN\n");}
		|EXIT		{printf("EXIT\n");}
		;
%%
yyerror(s) char *s;{
}
		
