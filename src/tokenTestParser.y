%{

/*  Unit test rule for lexical entites */

#include <stdio.h>
#include <stdlib.h>

%}

<-- MAKE PLACES DEFINITIONS.TOKENS FILE HERE -->

%%

program		:tokens_list 		
		;

tokens_list	:token
		|tokens_list token
		
token           :types_list 
		|operators_list
		|etc_list
		|keywords_list
		|constant_list
		;

constant_list	:INT_CONST		{printf("INT_CONST \
					    ( %d)\n", $<integer>1);}
		|REAL_CONST		{printf("REAL_CONST \
					    (%f)\n", $<real>1);}
		|STRING_CONST           {printf("STRING_CONST \
					    (%s)\n", $<string>1);}
types_list	:CHAR
		|ID                     {printf("ID (%s)\n",$<id>1);}
		|INT                    {printf("INT\n");}
		|REAL                   {printf("REAL\n");}
		|ARRAY			{printf("ARRAY\n");}
		;

operators_list	:PLUS                   {printf("PLUS\n");}
		|MINUS                  {printf("MINUS\n");}
		|MULTIPLY               {printf("MULTIPLY\n");}
		|MOD                    {printf("MOD\n");}
		|DIVIDE                 {printf("DIVIDE\n");}        
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
		|UNREC		{printf("UNREC\n");}
		;

keywords_list	:AND		{printf("AND\n");}
		|CONTINUE	{printf("CONTINUE\n");}
		|PROCEDURE	{printf("PROCEDURE\n");}
		|TYPE		{printf("TYPE\n");}
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
yyerror(char *s) {
	printf("Test parser encountered an error, this should not happen.\n");
}
		
