/* Cmput 415 - YACC - Bison parser */
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Error.h"
#include "ErrorLL.h"
#include "args.h"
#include "Actions.h"

extern struct args givenArgs;	/* from args.h */
extern int yylex(void);
extern int yylineno;
extern int yyleng;
extern int yyerrok;
extern char *yytext;
extern int colno;

#if DEBUG
        yydebug = 1;
#endif
%}
<-- MAKE PLACES DEFINITIONS.TOKENS FILE HERE -->

%%

file
: program
| error program
| program error
| error program error
;

program
: program_head decls compound_stat PERIOD
| program_head error PERIOD
;

program_head
: PROGRAM ID_or_err L_PAREN ID_or_err comma_or_error ID_or_err R_PAREN semicolon_or_error
| PROGRAM semicolon_or_error
| PROGRAM ID_or_err L_PAREN semicolon_or_error
| PROGRAM ID_or_err semicolon_or_error
;


// no | here since this is a list
decls
: const_decl_part
  type_decl_part
  var_decl_part
  proc_decl_part
| error
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
| error
;

type_decl_part
: TYPE type_decl_list semicolon_or_error
	{ enterTypeDeclPart(); }
|
;

type_decl_list
: type_decl
| type_decl_list semicolon_or_error type_decl
;

type_decl
: ID_or_err EQUAL type
	{ setType($<hash>1, $<hash>3); }
| error
;

type
: structured_type
| simple_type
| scalar_type
;

simple_type
: REAL
| INT
| BOOL
| CHAR
| ID_or_err
;

scalar_type
: L_PAREN scalar_list R_PAREN
;

scalar_list
: scalar_list comma_or_error ID_or_err
| ID_or_err
;

structured_type
: ARRAY array_type_decl OF type
| RECORD field_list END
;

array_type_decl
: LS_BRACKET array_type RS_BRACKET
| LS_BRACKET error RS_BRACKET
	{yyerrok;}
| error RS_BRACKET
	{yyerrok;}
| LS_BRACKET error
	{yyerrok;}
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
| ID_or_err comma_or_error var_decl
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
| proc_heading semicolon_or_error
;

proc_heading
: PROCEDURE ID_or_err f_parm_decl semicolon_or_error
| FUNCTION ID_or_err f_parm_decl COLON simple_type semicolon_or_error
| PROCEDURE ID semicolon_or_error
	{yyerrok;}
| FUNCTION ID semicolon_or_error
	{yyerrok;}
| PROCEDURE semicolon_or_error
| FUNCTION semicolon_or_error
;

f_parm_decl
: L_PAREN f_parm_list R_PAREN
| L_PAREN R_PAREN
| VAR ID error COLON simple_type
	{yyerrok;}
;

f_parm_list
: f_parm
| f_parm_list semicolon_or_error f_parm
;

f_parm
: ID COLON simple_type
| VAR ID COLON simple_type
| ID error COLON simple_type
	{yyerrok;}
| VAR ID error COLON simple_type
	{yyerrok;}
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
| subscripted_var comma_or_error expr
;

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
| error
;

factor
: var
| unsigned_const
| L_PAREN expr R_PAREN_or_error
| func_invok
| NOT factor
;

R_PAREN_or_error
: R_PAREN
| error
;

unsigned_const
: unsigned_num
// intentionall commented out. var and unsigned_const both reduce to ID in the
// same place, so this is redundant.
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
| plist_finvok error R_PAREN
	{ yyerrok; }
;

plist_finvok
: ID_or_err L_PAREN parm
| plist_finvok comma_or_error parm
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

comma_or_error
: error COMMA
	{yyerrok;}
| COMMA
;

semicolon_or_error
: error SEMICOLON
	{ yyerrok;}
| SEMICOLON
;

ID_or_err
: ID UNREC ID_or_err
| ID
	{ $<hash>$ = getHashElement($<id>1); }
;


%%

char *appENDErrorToken(char *s, char *token)
{
        char extraText[] = " Error token: ";
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

        errMsg = appENDErrorToken(s, yytext);
        if (errMsg) e = recordError(errMsg, yylineno, colno, SYNTAX);
        else e = recordError(s, yylineno, colno, SYNTAX);

#if DEBUG
        printf("New error on line %d\n", yylineno);
#endif
	if (givenArgs.q == 0) {
        	printError(e);
	}
        if (errMsg) free(errMsg);
}
