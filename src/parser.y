/* Cmput 415 - YACC - Bison parser */     

/*
* TODO:
* - check all tokens are used in grammer and vice versa
* - create testing cases!
*/

%{

#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "ErrorLL.h"
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

/* types: */
%token BOOL CHAR STRING INT REAL RECORD

/* control statements: */
%token _BEGIN END IF THEN ELSE WHILE DO CONTINUE EXIT OF

/* kinds: */
%token ID CONST INT_CONST REAL_CONST

/* declaration operators: */
%token PROGRAM TYPE VAR ARRAY FUNCTION PROCEDURE 

/* structure tokons: */
%token L_PAREN R_PAREN LS_BRACKET RS_BRACKET
%token PERIOD COMMA SEMICOLON COLON RANGE ASSIGN

/* operators: (keep in mind priority before changing order) */
%left NOT 
%left MULTIPLY DIVIDE DIV MOD AND
%left PLUS MINUS OR
%left EQUAL NOT_EQUAL LESS LESS_OR_EQUAL GREATER GREATER_OR_EQUAL


%%


program
: program_header decls compound_stat PERIOD
;

program_header
: PROGRAM ID L_PAREN ID COMMA ID R_PAREN SEMICOLON
;

decls
: const_decl_part type_decl_part var_decl_part proc_decl_part          
;


/* cosntant declartions part: */
const_decl_part
: CONST const_decl_list SEMICOLON
| /* or nothing */
;

const_decl_list
: const_decl
| const_decl_list SEMICOLON const_decl
;

const_decl
: ID EQUAL expr
;

/* type declartions part: */
type_decl_part
: TYPE type_decl_list SEMICOLON
| /* or nothing */
;

type_decl_list
: type_decl
| type_decl_list SEMICOLON type_decl
;

type_decl
: ID EQUAL type
;


/* variable declartions part: */
var_decl_part
: VAR var_decl_list SEMICOLON
| /* do nothing */
;

var_decl_list
: var_decl
| var_decl_list SEMICOLON var_decl
;

var_decl
: ID COLON type
| ID COMMA var_decl
;


/* procedures declartion part: */
proc_decl_part
: proc_decl_list
| /* do nothing */
;

proc_decl_list
: proc_decl
| proc_decl_list proc_decl
;

proc_decl
: proc_heading decls compound_stat SEMICOLON
;

proc_heading
: PROCEDURE ID func_parm_decl SEMICOLON
| FUNCTION ID func_parm_decl COLON ID SEMICOLON
;

func_parm_decl
: L_PAREN func_parm_list R_PAREN
| L_PAREN R_PAREN
;

func_parm_list
: func_parm 
| func_parm_list SEMICOLON func_parm
;

func_parm
: ID COLON ID
| VAR ID COLON ID
;


/* program/function bodies */
compound_stat
: _BEGIN stat_list END
;

stat_list
: stat 
| stat_list SEMICOLON stat 
;

stat 
: simple_stat
| struct_stat
| /* do nothing */
;

struct_stat             
: IF expr THEN matched_stat ELSE stat
| IF expr THEN stat
| WHILE expr DO stat
| CONTINUE
| EXIT
;

matched_stat
: simple_stat
| IF expr THEN matched_stat ELSE matched_stat
| WHILE expr DO matched_stat
| CONTINUE
| EXIT
;

simple_stat
: var ASSIGN expr
| proc_invok
| compound_stat
;

/**/

proc_invok
: parm_list_func_invoke R_PAREN
| ID L_PAREN R_PAREN
;

func_invoke
: parm_list_func_invoke R_PAREN
| ID  L_PAREN R_PAREN
;

parm_list_func_invoke
: ID L_PAREN parm 
| parm_list_func_invoke COMMA parm
;

parm 
: expr
;

/**/

var
: ID
| var PERIOD ID
| subscripted_var RS_BRACKET
;

subscripted_var
: var LS_BRACKET expr
| subscripted_var COMMA expr
;


/* expression grammer */
expr
: simple_expr
| expr EQUAL simple_expr
| expr NOT_EQUAL simple_expr
| expr LESS_OR_EQUAL simple_expr
| expr LESS simple_expr
| expr GREATER_OR_EQUAL simple_expr
| expr GREATER simple_expr
;

simple_expr
: term
| PLUS term
| MINUS term
| simple_expr PLUS term
| simple_expr MINUS term
| simple_expr OR term
;

term
: factor
| term MULTIPLY factor
| term DIVIDE factor
| term DIV factor
| term MOD factor
| term AND factor
;

factor
: var 
/* | unsigned_const */
/* | L_PAREN expr R_PAREN */
| func_invoke 
| NOT factor
;

/*
unsigned_const
: unsigned_num
| ID
| STRING
;

unsigned_num
: INT_CONST
| REAL_CONST
;*/


/* type grammer */
type
: simple_type
| structured_type
;

simple_type
: scalar_type
| REAL
| ID
;

scalar_type
: L_PAREN scalar_list R_PAREN
| INT
| BOOL
| CHAR
;

scalar_list
: ID
| scalar_list COMMA ID

structured_type
: ARRAY LS_BRACKET array_type RS_BRACKET OF type
| RECORD field_list END
;

array_type
: simple_type
| expr RANGE expr
;

field_list
: field
| field_list SEMICOLON field

field
: ID COLON type         
;



%%

yyerror(s) char *s; {
	/* Simple, naive for now, will add more features as project
	 * progresses */
	struct Error *e = recordError(s, yylineno);
	printError(e);
}
