/* Cmput 415 - YACC - Bison parser */     

/*
* TODO:
* - check all tokens are used in grammer and vice versa
* - create testing cases!
*/

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Error.h"
#include "ErrorLL.h"
extern int yylex(void);
extern int yylineno;
extern int yyleng;
extern char *yytext;
extern int colno;

#if DEBUG
	yydebug = 1;
#endif
%}
<-- MAKE PLACES DEFINITIONS.TOKENS FILE HERE -->

%%


program                 
 : program_head decls compound_stat PERIOD
 | error program_head decls compound_stat PERIOD
;

program_head            
: PROGRAM ID_or_err L_PAREN ID_or_err COMMA ID_or_err R_PAREN semicolon_or_error
;

decls
: const_decl_part
type_decl_part        
var_decl_part
proc_decl_part
;

const_decl_part         
: CONST const_decl_list semicolon_or_error
|
;

const_decl_list         
: const_decl
| const_decl_list semicolon_or_error const_decl
;

const_decl              
: ID_or_err EQUAL expr
;

type_decl_part          
: TYPE type_decl_list semicolon_or_error
|
;

type_decl_list          
: type_decl
| type_decl_list semicolon_or_error type_decl
;

type_decl               
: ID_or_err EQUAL type
;




type                    
: simple_type
| structured_type
;

simple_type             
: scalar_type
| REAL
| ID_or_err
;

scalar_type             
: L_PAREN scalar_list R_PAREN  
| INT
| BOOL
| CHAR
;

scalar_list             
: scalar_list COMMA ID_or_err
| ID_or_err COMMA ID_or_err
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
| field_list semicolon_or_error field
;

field                   
: ID_or_err COLON type
;

var_decl_part
: VAR var_decl_list semicolon_or_error
|
;

var_decl_list
: var_decl
| var_decl_list semicolon_or_error var_decl
;

var_decl                
: ID_or_err COLON type
| ID_or_err COMMA var_decl
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
: proc_heading decls compound_stat semicolon_or_error
;

proc_heading
: PROCEDURE ID_or_err f_parm_decl semicolon_or_error
| FUNCTION ID_or_err f_parm_decl COLON ID_or_err semicolon_or_error
;

f_parm_decl
: L_PAREN f_parm_list R_PAREN
| L_PAREN R_PAREN
;

f_parm_list
: f_parm
| f_parm_list semicolon_or_error f_parm
;

f_parm
: ID_or_err COLON ID_or_err
| VAR ID_or_err COLON ID_or_err
;

compound_stat
: _BEGIN stat_list END
;       

stat_list
: stat
| stat_list semicolon_or_error stat
;

stat  
: simple_stat
| struct_stat
|
| error simple_stat
| error struct_stat
;

simple_stat
: var ASSIGN expr
| proc_invok
| compound_stat
;

proc_invok  
: plist_finvok R_PAREN
| ID_or_err L_PAREN R_PAREN
;

var
: ID_or_err
| var PERIOD ID_or_err
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
| ID_or_err L_PAREN R_PAREN
;

plist_finvok
: ID_or_err L_PAREN parm
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

semicolon_or_error
: error SEMICOLON 
| SEMICOLON
;

ID_or_err
: ID UNREC ID_or_err
| ID
;


%%

char *appendErrorToken(char *s, char *token)
{
	char extraText[] = "  Error token: ";
	size_t sLen;
	size_t tokenLen;
	size_t extraTextLen;
	char *ret;

	if ((!token)) {
		return NULL;
	}
	sLen = strlen(s);
	tokenLen = strlen(token);
	extraTextLen = strlen(extraText);
	ret = calloc(1, sizeof(char)*(sLen + tokenLen + extraTextLen + 1));

	strcat(ret, s);
	strcat(ret, extraText);
	strcat(ret, token);
	return ret;

}

yyerror(char *s) {

	struct Error *e = NULL;
	char *errMsg = NULL;

	errMsg = appendErrorToken(s, yytext);
	if (errMsg) e = recordError(errMsg, yylineno, colno);
	else e = recordError(s, yylineno, colno);

#if DEBUG
	printf("New error on line %d\n", yylineno);
#endif
	printError(e);
	if (errMsg) free(errMsg);
}
