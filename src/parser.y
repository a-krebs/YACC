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
<-- MAKE PLACES DEFINITIONS.TOKENS FILE HERE -->

%%


program                 
 : program_head decls compound_stat PERIOD
;

program_head            
: PROGRAM ID L_PAREN ID COMMA ID R_PAREN SEMICOLON
;

decls
: const_decl_part
type_decl_part        
var_decl_part
proc_decl_part
;

const_decl_part         
: CONST const_decl_list SEMICOLON
|
;

const_decl_list         
: const_decl
| const_decl_list SEMICOLON const_decl
;

const_decl              
: ID EQUAL expr
;

type_decl_part          
: TYPE type_decl_list SEMICOLON
|
;

type_decl_list          
: type_decl
| type_decl_list SEMICOLON type_decl
;

type_decl               
: ID EQUAL type
;




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
: scalar_list COMMA ID
| ID COMMA ID
;

// scalar_list             
// : ID
// | scalar_list ',' ID
// ;

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
;

field                   
: ID COLON type
;

var_decl_part
: VAR var_decl_list SEMICOLON
|
;

var_decl_list
: var_decl
| var_decl_list SEMICOLON var_decl
;

var_decl                
: ID COLON type
| ID COMMA var_decl
;

proc_decl_part
: proc_decl_list
|
;

proc_decl_list
: proc_decl
| proc_decl_list proc_decl
;

proc_decl
: proc_heading decls compound_stat SEMICOLON
;

proc_heading
: PROCEDURE ID f_parm_decl SEMICOLON
| FUNCTION ID f_parm_decl COLON ID SEMICOLON
;

f_parm_decl
: L_PAREN f_parm_list R_PAREN
| L_PAREN R_PAREN
;

f_parm_list
: f_parm
| f_parm_list SEMICOLON f_parm
;

f_parm
: ID COLON ID
| VAR ID COLON ID
;

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
|
;

simple_stat
: var ASSIGN expr
| proc_invok
| compound_stat
;

proc_invok  
: plist_finvok R_PAREN
| ID L_PAREN R_PAREN
;

var
: ID
| var PERIOD ID
| subscripted_var RS_BRACKET
;

subscripted_var
: var LS_BRACKET expr
| subscripted_var COMMA expr
;

expr
: simple_expr
| expr EQUAL     simple_expr
| expr NOT_EQUAL simple_expr
| expr LESS_OR_EQUAL simple_expr
| expr LESS     simple_expr
| expr GREATER_OR_EQUAL simple_expr
| expr GREATER     simple_expr
;

// expr_list               
// : expr_list ',' expr
// | expr
// ;

simple_expr
: term
| PLUS term
| MINUS term
| simple_expr PLUS term
| simple_expr MINUS term
| simple_expr OR  term
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
| unsigned_const
| L_PAREN expr R_PAREN
 | func_invok
| NOT factor
;

unsigned_const          
: unsigned_num
// | ID
| STRING_CONST
;

unsigned_num
: INT_CONST
| REAL_CONST
;

func_invok
: plist_finvok R_PAREN
| ID L_PAREN R_PAREN
;

plist_finvok
: ID L_PAREN parm
| plist_finvok COMMA parm
;

parm
: expr
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



%%

yyerror(char *s) {
	/* Simple, naive for now, will add more features as project
	 * progresses */
	struct Error *e = recordError(s, yylineno);
#if DEBUG
	printf("New error on line %d\n", yylineno);
#endif
	printError(e);
}
