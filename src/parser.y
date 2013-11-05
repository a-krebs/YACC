/* Cmput 415 - YACC - Bison parser */
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Error.h"
#include "ErrorLL.h"
#include "args.h"
#include "Symbol.h"
#include "Actions.h"

extern struct args givenArgs;	/* from args.h */
extern int yylex(void);
extern int yylineno;
extern int yyleng;
extern int yyerrok;
extern char *yytext;
extern int colno;

/* 
 * Flag to set if we're in constant declaration.
 * 
 * This will enable/disable parts of the grammar. Specifically, when inDecl == 1
 * the var production will not reduce to a function invokation.
 */
extern int inDecl;

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
	{ inDecl = 1; }
| PROGRAM semicolon_or_error
	{ inDecl = 1; }
| PROGRAM ID_or_err L_PAREN semicolon_or_error
	{ inDecl = 1; }
| PROGRAM ID_or_err semicolon_or_error
	{ inDecl = 1; }
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
	{ exitConstDeclPart(); 
	  inDecl = 0;
	}
|
	{ inDecl = 0; }
;

const_decl_list
: const_decl
| const_decl_list semicolon_or_error const_decl
;

const_decl
: decl_ID_or_err EQUAL expr
	{ doConstDecl($<id>1, $<proxy>3); }
| error
;

type_decl_part
: TYPE type_decl_list semicolon_or_error
	{ exitTypeDeclPart(); }
|
;

type_decl_list
: type_decl
| type_decl_list semicolon_or_error type_decl
;

type_decl
: ID_or_err EQUAL type
	{ doTypeDecl($<id>1, $<symbol>3); }
| error
;

type
: structured_type
| simple_type
	{ $<symbol>$ = $<symbol>1; }
| scalar_type
	{ $<symbol>$ = $<symbol>1; }
;

simple_type
: ID_or_err
	{ $<symbol>$ = simpleTypeLookup($<id>1); }
;

scalar_type
: L_PAREN scalar_list R_PAREN
	{ $<symbol>$ = $<symbol>2; }
;

scalar_list
: scalar_list comma_or_error ID_or_err
	{ $<symbol>$ = appendToScalarListType($<symbol>1, $<id>3); }
| ID_or_err
	{ $<symbol>$ = createScalarListType($<id>1); }
;

structured_type
: ARRAY array_type_decl OF type
	{ $<symbol>$ = createArrayType($<symbol>2, $<symbol>4); }
| RECORD field_list END
	{ $<symbol>$ = $<symbol>2; }
;

array_type_decl
: LS_BRACKET array_type RS_BRACKET
	{ $<symbol>$ = $<symbol>2; }
| LS_BRACKET error RS_BRACKET
	{yyerrok;}
| error RS_BRACKET
	{yyerrok;}
| LS_BRACKET error
	{yyerrok;}
;

array_type
: simple_type
	{ $<symbol>$ = assertArrIndexType($<symbol>1); }
| expr RANGE expr
	{ $<symbol>$ = createRangeType($<proxy>1, $<proxy>3); }
;

field_list
: field
	{ $<symbol>$ = createRecordType($<proxy>1); }
| field_list SEMICOLON field
	{ $<symbol>$ = appendFieldToRecordType($<symbol>1, $<proxy>3); }
;

field
: ID_or_err COLON type
	{ $<proxy>$ = newRecordFieldProxy($<id>1, $<symbol>3); }
;

var_decl_part
: VAR var_decl_list semicolon_or_error
	{ exitVarDeclPart(); }
|
;

var_decl_list
: var_decl
| var_decl_list semicolon_or_error var_decl
;

var_decl
: ID_or_err COLON type
	{ $<symbol>$ = doVarDecl($<id>1, $<symbol>3); }
| ID_or_err comma_or_error var_decl
	{ $<symbol>$ = doVarDecl($<id>1, $<symbol>2); }
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
	{ exitProcOrFuncDecl(); }
| proc_heading semicolon_or_error
	{ exitProcOrFuncDecl(); }
;

proc_heading
: PROCEDURE ID_or_err f_parm_decl semicolon_or_error
	{ $<symbol>$ = enterProcDecl($<id>2, $<proxy>3);
	  /* TODO check what we're doing for f_parm_decl  */ }
| FUNCTION ID_or_err f_parm_decl COLON simple_type semicolon_or_error
	{ $<symbol>$ = enterFuncDecl($<id>2, $<proxy>3); }
| PROCEDURE ID semicolon_or_error
	{ $<symbol>$ = enterProcDecl($<id>2, NULL);
	  yyerrok; }
| FUNCTION ID semicolon_or_error
	{ $<symbol>$ = enterFuncDecl($<id>2, NULL);
	  yyerrok; }
| PROCEDURE semicolon_or_error
	{ $<symbol>$ = enterProcDecl(NULL, NULL); }
| FUNCTION semicolon_or_error
	{ $<symbol>$ = enterProcDecl(NULL, NULL); }
;

f_parm_decl
: L_PAREN f_parm_list R_PAREN
	{ $<proxy>$ = $<proxy>2; }
| L_PAREN R_PAREN
	{ $<proxy>$ = NULL; }
// TODO what is this production for?
| VAR ID error COLON simple_type
	{yyerrok;}
;

f_parm_list
: f_parm
	{ $<proxy>$ = createParmList($<proxy>1); }
| f_parm_list semicolon_or_error f_parm
	{ $<proxy>$ = appendParmToParmList($<proxy>1, $<proxy>2); }
;

f_parm
: ID COLON simple_type
	{ $<proxy>$ = createNewParm($<id>1, $<symbol>3); }
| VAR ID COLON simple_type
	{ $<proxy>$ = createNewVarParm($<id>2, $<symbol>4); }
| ID error COLON simple_type
	{ $<proxy>$ = createNewParm($<id>1, $<symbol>3);
	  yyerrok; }
| VAR ID error COLON simple_type
	{ $<proxy>$ = createNewVarParm($<id>2, $<symbol>4);
	  yyerrok; }
;

compound_stat
: _BEGIN stat_list END
	{ /* TODO maybe refactor this into a begin and end part */ }
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
	{ assignOp($<proxy>1, $<proxy>3); }
| proc_invok
	{ /* TODO */ }
| compound_stat
;

var
: decl_ID_or_err
| ID_or_err
	{ $<proxy>$ = hashLookupToProxy($<id>1); }
| var PERIOD ID_or_err
	{ $<proxy>$ = recordAccessToProxy($<id>1, $<id>3 ); }
| subscripted_var RS_BRACKET
	{ $<proxy>$ = $<proxy>1; }
;

subscripted_var
: var LS_BRACKET expr
	{ $<proxy>$ = $<proxy>3; }
| subscripted_var comma_or_error expr
	{ /* TODO */ }
;

expr
: simple_expr
	{ $<proxy>$ = $<proxy>1; }
| expr EQUAL simple_expr
	{ $<proxy>$ = eqOp($<proxy>1, $<proxy>3); }
| expr NOT_EQUAL simple_expr
	{ $<proxy>$ = notEqOp($<proxy>1, $<proxy>3); }
| expr LESS_OR_EQUAL simple_expr
	{ $<proxy>$ = lessOrEqOp($<proxy>1, $<proxy>3); }
| expr LESS simple_expr
	{ $<proxy>$ = lessOp($<proxy>1, $<proxy>3); }
| expr GREATER_OR_EQUAL simple_expr
	{ $<proxy>$ = gtOrEqOp($<proxy>1, $<proxy>3); }
| expr GREATER simple_expr
	{ $<proxy>$ = gtOp($<proxy>1, $<proxy>3); }
;

simple_expr
: term
	{ $<proxy>$ = $<proxy>1; }
| PLUS term
	{ $<proxy>$ = unaryPlusOp($<proxy>2); }
| MINUS term
	{ $<proxy>$ = unaryMinusOp($<proxy>2); }
| simple_expr PLUS term
	{ $<proxy>$ = plusOp($<proxy>1, $<proxy>3); }
| simple_expr MINUS term
	{ $<proxy>$ = minusOp($<proxy>1, $<proxy>3); }
| simple_expr OR term
	{ $<proxy>$ = orOp($<proxy>1, $<proxy>3); }
;

term
: factor
	{ $<proxy>$ = $<proxy>1; }
| term MULTIPLY factor
	{ $<proxy>$ = multOp($<proxy>1, $<proxy>3); }
| term DIVIDE factor
	{ $<proxy>$ = divideOp($<proxy>1, $<proxy>3); }
| term DIV factor
	{ $<proxy>$ = divOp($<proxy>1, $<proxy>3); }
| term MOD factor
	{ $<proxy>$ = modOp($<proxy>1, $<proxy>3); }
| term AND factor
	{ $<proxy>$ = andOp($<proxy>1, $<proxy>3); }
| error
;

factor
: var
	{ $<proxy>$ = $<proxy>1; }
| unsigned_const
	{ $<proxy>$ = $<proxy>1; }
| L_PAREN expr R_PAREN_or_error
	{ $<proxy>$ = $<proxy>2; }
| func_invok
	{ $<proxy>$ = $<proxy>1; }
| NOT factor
	{ $<proxy>$ = unaryNotOp($<proxy>2); }
;

R_PAREN_or_error
: R_PAREN
| error
;

unsigned_const
: unsigned_num
	{ $<proxy>$ = $<proxy>$; }
| STRING_CONST
	{ $<proxy>$ = proxyStringLiteral($<string>1); }
	// return String struct from Type.h
;

unsigned_num
: INT_CONST
	{ $<proxy>$ = proxyIntLiteral($<integer>1); }
| REAL_CONST
	{ $<proxy>$ = proxyRealLiteral($<real>1); }
;

proc_invok
: plist_finvok R_PAREN
| ID_or_err L_PAREN R_PAREN
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
	{ $<id>$ = $<id>1; }
| ID
	{ $<id>$ = $<id>1; }
;

decl_ID_or_err
: DECL_ID UNREC decl_ID_or_err
	{ $<id>$ = $<id>1; }
| DECL_ID
	{ $<id>$ = $<id>1; }
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
