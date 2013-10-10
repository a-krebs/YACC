%{
/* Cmput 415 - YACC - Bison parser */	

#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
extern int yylex(void);
extern int yylineno;
%}

%error-verbose
%union {
	char character;
	char *string;
	char *id;
	double real;
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

/* Types and identifiers */
%token <character> CHAR
%token <id> ID
%token <integer> INT
%token <real> REAL
%token <string> STRING


/* etc */
%token ASSIGN COMMA L_PAREN R_PAREN LS_BRACKET RS_BRACKET PERIOD
%token SEMICOLON COLON

%%

program                 : program_head decls compound_stat PERIOD
                        ;

program_head            : PROGRAM ID L_PAREN ID COMMA ID R_PAREN SEMICOLON
                        ;

decls                   : const_decl_part
                          type_decl_part        
                          var_decl_part
                          proc_decl_part
                        ;

const_decl_part         : CONST const_decl_list SEMICOLON
                        |
                        ;

const_decl_list         : const_decl
                        | const_decl_list SEMICOLON const_decl
                        ;

const_decl              : ID EQUAL expr
                        ;

type_decl_part          : TYPE type_decl_list SEMICOLON
                        |
                        ;

type_decl_list          : type_decl
                        | type_decl_list SEMICOLON type_decl
                        ;

type_decl               : ID EQUAL type
                        ;

type                    : simple_type
                        | structured_type
                        ;

simple_type             : scalar_type
                        | ID
                        ;

scalar_type             : L_PAREN scalar_list R_PAREN
                        | INT
                        | CHAR
                        ;

scalar_list             : ID
                        | scalar_list COMMA ID
                        ;

structured_type         : ARRAY LS_BRACKET array_type RS_BRACKET OF type
                        | RECORD field_list END
                        ;

array_type              : simple_type
                        | expr PERIOD PERIOD expr
                        ;

field_list              : field
                        | field_list SEMICOLON field
                        ;

field                   : ID COLON type
                        ;

var_decl_part           : VAR var_decl_list SEMICOLON
                        |
                        ;

var_decl_list           : var_decl
                        | var_decl_list SEMICOLON var_decl
                        ;

var_decl                : ID COLON type
                        | ID COMMA var_decl
                        ;

proc_decl_part          : proc_decl_list
                        |
                        ;

proc_decl_list          : proc_decl
                        | proc_decl_list proc_decl
                        ;

proc_decl               : proc_heading decls compound_stat SEMICOLON
                        ;

proc_heading            : PROCEDURE ID f_parm_decl SEMICOLON
                        | FUNCTION ID f_parm_decl COLON ID SEMICOLON
                        ;

f_parm_decl             : L_PAREN f_parm_list R_PAREN
                        | L_PAREN R_PAREN
                        ;

f_parm_list             : f_parm
                        | f_parm_list SEMICOLON f_parm
                        ;

f_parm                  : ID COLON ID
                        | VAR ID COLON ID
                        ;

compound_stat           : _BEGIN stat_list END
                        ;       

stat_list               : stat
                        | stat_list SEMICOLON stat
                        ;

stat                    : simple_stat
                        | struct_stat
                        |
                        ;

simple_stat             : var ':=' expr
                        | proc_invok
                        | compound_stat
                        ;

proc_invok              : plist_finvok R_PAREN
                        | ID L_PAREN R_PAREN
                        ;

var                     : ID
                        | var PERIOD ID
                        | subscripted_var RS_BRACKET
                        ;

subscripted_var         : var LS_BRACKET expr
                        | subscripted_var ',' expr
                        ;

expr                    : simple_expr
                        | expr EQUAL     simple_expr
                        | expr NOT_EQUAL simple_expr
                        | expr LESS_OR_EQUAL simple_expr
                        | expr LESS     simple_expr
                        | expr GREATER_OR_EQUAL simple_expr
                        | expr GREATER     simple_expr
                        ;

expr_list               : expr_list COMMA expr
                        | expr
                        ;

simple_expr             : term
                        | PLUS term
                        | MINUS term
                        | simple_expr PLUS term
                        | simple_expr MINUS term
                        | simple_expr OR  term
                        ;

term                    : factor
                        | term MULTIPLY factor
                        | term DIVIDE factor
                        | term DIV factor
                        | term MOD factor
                        | term AND factor
                        ;

factor                  : var
                        | unsigned_const
                        | L_PAREN expr R_PAREN
                        | func_invok
                        | NOT factor
                        ;

unsigned_const          : unsigned_num
                        | ID
                        | STRING
                        ;

unsigned_num            : INT
                        | REAL
                        ;

func_invok              : plist_finvok R_PAREN
                        | ID L_PAREN R_PAREN
                        ;

plist_finvok            : ID L_PAREN parm
                        | plist_finvok COMMA parm
                        ;

parm                    : expr

struct_stat             : IF expr THEN matched_stat ELSE stat
                        | IF expr THEN stat
                        | WHILE expr DO stat
                        | CONTINUE
                        | EXIT
                        ;

matched_stat            : simple_stat
                        | IF expr THEN matched_stat ELSE matched_stat
                        | WHILE expr DO matched_stat
                        | CONTINUE
                        | EXIT
                        ;

%%

yyerror(s) char *s; {
	printError(s);
	printf("%d\n", yylineno);
}

