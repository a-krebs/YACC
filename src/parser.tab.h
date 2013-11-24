/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     DECL_ID = 259,
     ARRAY = 260,
     BOOL = 261,
     CHAR = 262,
     INT = 263,
     REAL = 264,
     RECORD = 265,
     INT_CONST = 266,
     REAL_CONST = 267,
     STRING_CONST = 268,
     _BEGIN = 269,
     END = 270,
     IF = 271,
     THEN = 272,
     ELSE = 273,
     WHILE = 274,
     DO = 275,
     CONTINUE = 276,
     EXIT = 277,
     OF = 278,
     PROGRAM = 279,
     TYPE = 280,
     VAR = 281,
     CONST = 282,
     FUNCTION = 283,
     PROCEDURE = 284,
     L_PAREN = 285,
     R_PAREN = 286,
     LS_BRACKET = 287,
     RS_BRACKET = 288,
     PERIOD = 289,
     COMMA = 290,
     SEMICOLON = 291,
     COLON = 292,
     RANGE = 293,
     ASSIGN = 294,
     UNREC = 295,
     NOT = 296,
     AND = 297,
     MOD = 298,
     DIV = 299,
     DIVIDE = 300,
     MULTIPLY = 301,
     OR = 302,
     MINUS = 303,
     PLUS = 304,
     GREATER_OR_EQUAL = 305,
     GREATER = 306,
     LESS_OR_EQUAL = 307,
     LESS = 308,
     NOT_EQUAL = 309,
     EQUAL = 310
   };
#endif
/* Tokens.  */
#define ID 258
#define DECL_ID 259
#define ARRAY 260
#define BOOL 261
#define CHAR 262
#define INT 263
#define REAL 264
#define RECORD 265
#define INT_CONST 266
#define REAL_CONST 267
#define STRING_CONST 268
#define _BEGIN 269
#define END 270
#define IF 271
#define THEN 272
#define ELSE 273
#define WHILE 274
#define DO 275
#define CONTINUE 276
#define EXIT 277
#define OF 278
#define PROGRAM 279
#define TYPE 280
#define VAR 281
#define CONST 282
#define FUNCTION 283
#define PROCEDURE 284
#define L_PAREN 285
#define R_PAREN 286
#define LS_BRACKET 287
#define RS_BRACKET 288
#define PERIOD 289
#define COMMA 290
#define SEMICOLON 291
#define COLON 292
#define RANGE 293
#define ASSIGN 294
#define UNREC 295
#define NOT 296
#define AND 297
#define MOD 298
#define DIV 299
#define DIVIDE 300
#define MULTIPLY 301
#define OR 302
#define MINUS 303
#define PLUS 304
#define GREATER_OR_EQUAL 305
#define GREATER 306
#define LESS_OR_EQUAL 307
#define LESS 308
#define NOT_EQUAL 309
#define EQUAL 310




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 36 "src/generated_parser.y"

      char character;
      struct String string;
      char *id;
      double real;
      int integer;
	struct ElementArray *elemarray;
      Symbol *symbol;
      ProxySymbol *proxy;
	void * voidtype;



/* Line 2068 of yacc.c  */
#line 174 "src/parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


