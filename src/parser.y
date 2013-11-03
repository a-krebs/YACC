/* Cmput 415 - YACC - Bison parser */
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Error.h"
#include "ErrorLL.h"
#include "args.h"
#include "Actions.h"
#include "Symbol.h"

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
	{ exitConstDeclPart(); }
|
;

const_decl_list
: const_decl
| const_decl_list semicolon_or_error const_decl
;

const_decl
: ID_or_err EQUAL expr
	{ doConstDecl($<id>1, $<tmp>3); }
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
	{ $<symbol>$ = createRangeType($<tmp>1, $<tmp>3); }
;

field_list
: field
	{ $<symbol>$ = createRecordType($<tmp>1); }
| field_list SEMICOLON field
	{ $<symbol>$ = appendFieldToRecordType($<symbol>1, $<tmp>3); }
;

field
: ID_or_err COLON type
	{ $<tmp>$ = newTmpRecordField($<id>1, $<symbol>3); }
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
	{ $<symbol>$ = enterProcDecl($<id>2, $<symbol>3);
	  /* TODO check what we're doing for f_parm_decl  */ }
| FUNCTION ID_or_err f_parm_decl COLON simple_type semicolon_or_error
	{ $<symbol>$ = enterFuncDecl($<id>2, $<symbol>3); }
| PROCEDURE ID semicolon_or_error
	{ $<symbol>$ = enterProcDecl($<id>2, NULL);
	  yyerrok; }
| FUNCTION ID semicolon_or_error
	{ $<symbol>$ = enterFuncDecl($<id>2, NULL);
	  yyerrok; }
| PROCEDURE semicolon_or_error
	{ $<symbol>$ = enterProcDecl((void*)NULL, (void*)NULL); }
| FUNCTION semicolon_or_error
	{ $<symbol>$ = enterProcDecl((void*)NULL, (void*)NULL); }
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
	{ assignOp($<tmp>1, $<tmp>3); }
| proc_invok
	{ /* TODO */ }
| compound_stat
;

proc_invok
: plist_finvok R_PAREN
| ID_or_err L_PAREN R_PAREN
;

var
: ID_or_err
	{ $<tmp>$ = hashLookupToTmp($<id>1); }
| var PERIOD ID_or_err
	{ $<tmp>$ = recordAccessToTmp($<id>1, $<id>3 ); }
| subscripted_var RS_BRACKET
	{ $<tmp>$ = $<tmp>1; }
;

subscripted_var
: var LS_BRACKET expr
	{ $<tmp>$ = $<tmp>3; }
| subscripted_var comma_or_error expr
	{ /* TODO */ }
;

expr
: simple_expr
	{ $<tmp>$ = $<tmp>1; }
| expr EQUAL simple_expr
	{ $<tmp>$ = eqOp($<tmp>1, $<tmp>3); }
| expr NOT_EQUAL simple_expr
	{ $<tmp>$ = notEqOp($<tmp>1, $<tmp>3); }
| expr LESS_OR_EQUAL simple_expr
	{ $<tmp>$ = lessOrEqOp($<tmp>1, $<tmp>3); }
| expr LESS simple_expr
	{ $<tmp>$ = lessOp($<tmp>1, $<tmp>3); }
| expr GREATER_OR_EQUAL simple_expr
	{ $<tmp>$ = gtOrEqOp($<tmp>1, $<tmp>3); }
| expr GREATER simple_expr
	{ $<tmp>$ = gtOp($<tmp>1, $<tmp>3); }
;

simple_expr
: term
	{ $<tmp>$ = $<tmp>1; }
| PLUS term
	{ $<tmp>$ = unaryPlusOp($<tmp>2); }
| MINUS term
	{ $<tmp>$ = unaryMinusOp($<tmp>2); }
| simple_expr PLUS term
	{ $<tmp>$ = plusOp($<tmp>1, $<tmp>3); }
| simple_expr MINUS term
	{ $<tmp>$ = minusOp($<tmp>1, $<tmp>3); }
| simple_expr OR term
	{ $<tmp>$ = orOp($<tmp>1, $<tmp>3); }
;

term
: factor
	{ $<tmp>$ = $<tmp>1; }
| term MULTIPLY factor
	{ $<tmp>$ = multOp($<tmp>1, $<tmp>3); }
| term DIVIDE factor
	{ $<tmp>$ = divideOp($<tmp>1, $<tmp>3); }
| term DIV factor
	{ $<tmp>$ = divOp($<tmp>1, $<tmp>3); }
| term MOD factor
	{ $<tmp>$ = modOp($<tmp>1, $<tmp>3); }
| term AND factor
	{ $<tmp>$ = andOp($<tmp>1, $<tmp>3); }
| error
;

factor
: var
	{ $<tmp>$ = $<tmp>1; }
| unsigned_const
	{ $<tmp>$ = getTmpFromSymbol($<symbol>1); }
| L_PAREN expr R_PAREN_or_error
	{ $<tmp>$ = $<tmp>2; }
| func_invok
	{ $<tmp>$ = $<tmp>1; }
| NOT factor
	{ $<tmp>$ = unaryNotOp($<tmp>2); }
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
	{ $<symbol>$ = anonStringLiteral($<string>1); }
	// return String struct from Type.h
;

unsigned_num
: INT_CONST
	{ $<symbol>$ = anonIntLiteral($<integer>1); }
| REAL_CONST
	{ $<symbol>$ = anonRealLiteral($<real>1); }
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
