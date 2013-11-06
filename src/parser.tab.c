/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 2 "src/generated_parser.y"


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


/* Line 268 of yacc.c  */
#line 105 "src/parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 293 of yacc.c  */
#line 36 "src/generated_parser.y"

      char character;
      char *string;
      char *id;
      double real;
      int integer;
      Symbol *symbol;
      ProxySymbol *proxy;



/* Line 293 of yacc.c  */
#line 263 "src/parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 275 "src/parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   425

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNRULES -- Number of states.  */
#define YYNSTATES  272

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   310

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    15,    20,    24,    33,
      36,    41,    45,    50,    52,    56,    57,    59,    63,    67,
      69,    73,    74,    76,    80,    84,    86,    88,    90,    92,
      94,    98,   102,   104,   109,   113,   117,   121,   124,   127,
     129,   133,   135,   139,   143,   147,   148,   150,   154,   158,
     162,   164,   165,   167,   170,   175,   178,   183,   190,   194,
     198,   201,   204,   208,   211,   217,   219,   223,   227,   232,
     237,   243,   247,   249,   253,   255,   257,   258,   262,   264,
     266,   268,   270,   274,   277,   281,   285,   287,   289,   293,
     297,   301,   305,   309,   313,   315,   318,   321,   325,   329,
     333,   335,   339,   343,   347,   351,   355,   357,   359,   361,
     365,   367,   370,   372,   374,   376,   378,   380,   382,   385,
     389,   393,   397,   400,   404,   408,   412,   416,   418,   425,
     430,   435,   437,   439,   441,   448,   453,   455,   457,   460,
     462,   465,   467,   471,   473,   477
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    -1,     1,    58,    -1,    58,     1,
      -1,     1,    58,     1,    -1,    59,    60,    86,    34,    -1,
      59,     1,    34,    -1,    24,   109,    30,   109,   107,   109,
      31,   108,    -1,    24,   108,    -1,    24,   109,    30,   108,
      -1,    24,   109,   108,    -1,    61,    64,    76,    79,    -1,
       1,    -1,    27,    62,   108,    -1,    -1,    63,    -1,    62,
     108,    63,    -1,   110,    55,    93,    -1,     1,    -1,    25,
      65,   108,    -1,    -1,    66,    -1,    65,   108,    66,    -1,
     109,    55,    67,    -1,     1,    -1,    71,    -1,    68,    -1,
      69,    -1,   109,    -1,    30,    70,    31,    -1,    70,   107,
     109,    -1,   109,    -1,     5,    72,    23,    67,    -1,    10,
      74,    15,    -1,    32,    73,    33,    -1,    32,     1,    33,
      -1,     1,    33,    -1,    32,     1,    -1,    68,    -1,    93,
      38,    93,    -1,    75,    -1,    74,    36,    75,    -1,   109,
      37,    67,    -1,    26,    77,   108,    -1,    -1,    78,    -1,
      77,   108,    78,    -1,   109,    37,    67,    -1,   109,   107,
      78,    -1,    80,    -1,    -1,    81,    -1,    80,    81,    -1,
      82,    60,    86,   108,    -1,    82,   108,    -1,    29,   109,
      83,   108,    -1,    28,   109,    83,    37,    68,   108,    -1,
      29,     3,   108,    -1,    28,     3,   108,    -1,    29,   108,
      -1,    28,   108,    -1,    30,    84,    31,    -1,    30,    31,
      -1,    26,     3,     1,    37,    68,    -1,    85,    -1,    84,
     108,    85,    -1,     3,    37,    68,    -1,    26,     3,    37,
      68,    -1,     3,     1,    37,    68,    -1,    26,     3,     1,
      37,    68,    -1,    14,    87,    15,    -1,    88,    -1,    87,
     108,    88,    -1,    89,    -1,   105,    -1,    -1,    90,    39,
      93,    -1,   100,    -1,    86,    -1,   110,    -1,   109,    -1,
      90,    34,   109,    -1,    91,    33,    -1,    90,    32,    92,
      -1,    91,   107,    92,    -1,    93,    -1,    94,    -1,    93,
      55,    94,    -1,    93,    54,    94,    -1,    93,    52,    94,
      -1,    93,    53,    94,    -1,    93,    50,    94,    -1,    93,
      51,    94,    -1,    95,    -1,    49,    95,    -1,    48,    95,
      -1,    94,    49,    95,    -1,    94,    48,    95,    -1,    94,
      47,    95,    -1,    96,    -1,    95,    46,    96,    -1,    95,
      45,    96,    -1,    95,    44,    96,    -1,    95,    43,    96,
      -1,    95,    42,    96,    -1,     1,    -1,    90,    -1,    98,
      -1,    30,    93,    97,    -1,   102,    -1,    41,    96,    -1,
      31,    -1,     1,    -1,    99,    -1,    13,    -1,    11,    -1,
      12,    -1,   101,    31,    -1,   109,    30,    31,    -1,   109,
      30,   104,    -1,   101,   107,   104,    -1,   103,    31,    -1,
     109,    30,    31,    -1,   103,     1,    31,    -1,   109,    30,
     104,    -1,   103,   107,   104,    -1,    93,    -1,    16,    93,
      17,   106,    18,    88,    -1,    16,    93,    17,    88,    -1,
      19,    93,    20,    88,    -1,    21,    -1,    22,    -1,    89,
      -1,    16,    93,    17,   106,    18,   106,    -1,    19,    93,
      20,   106,    -1,    21,    -1,    22,    -1,     1,    35,    -1,
      35,    -1,     1,    36,    -1,    36,    -1,     3,    40,   109,
      -1,     3,    -1,     4,    40,   110,    -1,     4,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    77,    77,    78,    79,    80,    84,    85,    89,    92,
      95,    98,   105,   109,   113,   118,   122,   123,   127,   129,
     133,   135,   139,   140,   144,   146,   150,   152,   154,   159,
     164,   169,   171,   176,   178,   183,   185,   188,   191,   197,
     199,   204,   206,   211,   216,   218,   222,   223,   227,   229,
     234,   235,   239,   240,   244,   246,   251,   253,   255,   258,
     261,   263,   268,   270,   272,   278,   280,   285,   287,   289,
     292,   298,   302,   303,   307,   308,   309,   313,   315,   316,
     320,   322,   324,   326,   331,   333,   338,   343,   345,   347,
     349,   351,   353,   355,   360,   362,   364,   366,   368,   370,
     375,   377,   379,   381,   383,   385,   387,   392,   394,   396,
     398,   400,   405,   406,   410,   412,   417,   419,   424,   426,
     433,   435,   441,   444,   447,   454,   456,   462,   468,   469,
     470,   472,   474,   479,   480,   481,   483,   485,   490,   492,
     496,   498,   502,   504,   509,   511
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "DECL_ID", "ARRAY", "BOOL", "CHAR",
  "INT", "REAL", "RECORD", "INT_CONST", "REAL_CONST", "STRING_CONST",
  "_BEGIN", "END", "IF", "THEN", "ELSE", "WHILE", "DO", "CONTINUE", "EXIT",
  "OF", "PROGRAM", "TYPE", "VAR", "CONST", "FUNCTION", "PROCEDURE",
  "L_PAREN", "R_PAREN", "LS_BRACKET", "RS_BRACKET", "PERIOD", "COMMA",
  "SEMICOLON", "COLON", "RANGE", "ASSIGN", "UNREC", "NOT", "AND", "MOD",
  "DIV", "DIVIDE", "MULTIPLY", "OR", "MINUS", "PLUS", "GREATER_OR_EQUAL",
  "GREATER", "LESS_OR_EQUAL", "LESS", "NOT_EQUAL", "EQUAL", "$accept",
  "file", "program", "program_head", "decls", "const_decl_part",
  "const_decl_list", "const_decl", "type_decl_part", "type_decl_list",
  "type_decl", "type", "simple_type", "scalar_type", "scalar_list",
  "structured_type", "array_type_decl", "array_type", "field_list",
  "field", "var_decl_part", "var_decl_list", "var_decl", "proc_decl_part",
  "proc_decl_list", "proc_decl", "proc_heading", "f_parm_decl",
  "f_parm_list", "f_parm", "compound_stat", "stat_list", "stat",
  "simple_stat", "var", "subscripted_var", "subscripted_var_index", "expr",
  "simple_expr", "term", "factor", "R_PAREN_or_error", "unsigned_const",
  "unsigned_num", "proc_invok", "plist_pinvok", "func_invok",
  "plist_finvok", "parm", "struct_stat", "matched_stat", "comma_or_error",
  "semicolon_or_error", "ID_or_err", "decl_ID_or_err", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    57,    57,    57,    58,    58,    59,    59,
      59,    59,    60,    60,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    67,    68,
      69,    70,    70,    71,    71,    72,    72,    72,    72,    73,
      73,    74,    74,    75,    76,    76,    77,    77,    78,    78,
      79,    79,    80,    80,    81,    81,    82,    82,    82,    82,
      82,    82,    83,    83,    83,    84,    84,    85,    85,    85,
      85,    86,    87,    87,    88,    88,    88,    89,    89,    89,
      90,    90,    90,    90,    91,    91,    92,    93,    93,    93,
      93,    93,    93,    93,    94,    94,    94,    94,    94,    94,
      95,    95,    95,    95,    95,    95,    95,    96,    96,    96,
      96,    96,    97,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   102,   103,   103,   104,   105,   105,
     105,   105,   105,   106,   106,   106,   106,   106,   107,   107,
     108,   108,   109,   109,   110,   110
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     3,     4,     3,     8,     2,
       4,     3,     4,     1,     3,     0,     1,     3,     3,     1,
       3,     0,     1,     3,     3,     1,     1,     1,     1,     1,
       3,     3,     1,     4,     3,     3,     3,     2,     2,     1,
       3,     1,     3,     3,     3,     0,     1,     3,     3,     3,
       1,     0,     1,     2,     4,     2,     4,     6,     3,     3,
       2,     2,     3,     2,     5,     1,     3,     3,     4,     4,
       5,     3,     1,     3,     1,     1,     0,     3,     1,     1,
       1,     1,     3,     2,     3,     3,     1,     1,     3,     3,
       3,     3,     3,     3,     1,     2,     2,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     3,
       1,     2,     1,     1,     1,     1,     1,     1,     2,     3,
       3,     3,     2,     3,     3,     3,     3,     1,     6,     4,
       4,     1,     1,     1,     6,     4,     1,     1,     2,     1,
       2,     1,     3,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,   143,   141,
       9,     0,     1,     4,    13,     0,     0,    21,     5,   140,
       0,     0,    11,     7,    19,   145,     0,    16,     0,    76,
       0,     0,    45,   142,    10,     0,     0,     0,     0,     0,
       0,   131,   132,    79,     0,    72,    74,     0,     0,    78,
       0,    75,    81,    80,     6,    25,     0,    22,     0,     0,
      51,     0,   139,     0,   144,    17,   106,   116,   117,   115,
       0,     0,     0,     0,   107,    18,    87,    94,   100,   108,
     114,   110,     0,    81,     0,     0,    71,    76,     0,     0,
       0,    83,     0,   118,     0,     0,     0,     0,     0,    46,
       0,     0,     0,    12,    50,    52,     0,   138,     0,     0,
     111,    96,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   122,     0,
       0,    76,    76,    73,    84,    86,    82,    77,    85,   127,
     121,   119,   120,    23,     0,     0,     0,    24,    27,    28,
      26,    29,    44,     0,     0,     0,    61,     0,     0,    60,
       0,    53,    13,     0,    55,     0,   113,   112,   109,    92,
      93,    90,    91,    89,    88,    99,    98,    97,   105,   104,
     103,   102,   101,   124,   126,   123,   125,     0,     0,   131,
     132,   129,    74,     0,   130,     0,     0,     0,     0,    41,
       0,     0,    32,    47,    48,    49,    59,     0,     0,     0,
      58,     0,     0,     8,     0,     0,    76,    37,   106,    39,
       0,     0,    81,     0,    34,     0,     0,    30,     0,     0,
       0,     0,    63,     0,    65,     0,    56,    54,    76,    76,
     128,    36,    35,     0,    33,    42,    43,    31,     0,     0,
       0,     0,    62,     0,     0,     0,   135,    40,     0,     0,
      67,     0,     0,    66,    57,    76,    64,    69,     0,    68,
     134,    70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    16,    17,    26,    27,    32,    56,
      57,   147,   148,   149,   201,   150,   197,   220,   198,   199,
      60,    98,    99,   103,   104,   105,   106,   209,   233,   234,
      43,    44,   191,    46,    74,    48,   134,   139,    76,    77,
      78,   168,    79,    80,    49,    50,    81,    82,   140,    51,
     193,    63,    10,    83,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -208
static const yytype_int16 yypact[] =
{
      10,    32,    78,    28,   147,   178,   228,    66,    97,  -208,
    -208,    83,  -208,  -208,   126,     8,   142,   116,  -208,  -208,
     163,    78,  -208,  -208,  -208,   135,    91,  -208,   155,   371,
     154,   248,   176,  -208,  -208,     4,   214,   325,   242,   242,
     242,  -208,  -208,  -208,    61,  -208,  -208,   200,   107,  -208,
     114,  -208,   205,  -208,  -208,  -208,    91,  -208,   185,   163,
     256,   215,  -208,   163,  -208,  -208,  -208,  -208,  -208,  -208,
     242,    13,   297,   297,   246,   364,   133,   298,  -208,  -208,
    -208,  -208,   182,   234,    -4,   308,  -208,   371,   242,   163,
     242,  -208,   242,  -208,   242,   160,   370,   217,    91,  -208,
      36,   100,   123,  -208,   256,  -208,   320,  -208,   227,   145,
    -208,   298,   298,   242,   242,   242,   242,   242,   242,   297,
     297,   297,    13,    13,    13,    13,    13,    47,  -208,   242,
     258,   391,   371,  -208,  -208,   364,  -208,   364,  -208,   364,
    -208,  -208,  -208,  -208,   130,   163,   163,  -208,  -208,  -208,
    -208,  -208,   163,   217,   163,    92,  -208,   109,    92,  -208,
     109,  -208,    66,   142,  -208,    91,  -208,  -208,  -208,   133,
     133,   133,   133,   133,   133,   298,   298,   298,  -208,  -208,
    -208,  -208,  -208,  -208,  -208,  -208,  -208,   242,   242,   268,
     269,  -208,   274,   275,  -208,   241,   264,   272,     0,  -208,
     259,   184,  -208,  -208,  -208,  -208,  -208,   294,     7,   266,
    -208,    91,    91,  -208,   265,   315,   371,  -208,    63,  -208,
     271,   326,   211,   217,  -208,   163,   217,  -208,   163,   301,
      22,   311,  -208,   122,  -208,   163,  -208,  -208,   391,   391,
    -208,  -208,  -208,   242,  -208,  -208,  -208,  -208,   285,   286,
     163,    54,  -208,   131,    91,   293,  -208,   364,   163,   163,
    -208,   287,   163,  -208,  -208,   391,  -208,  -208,   163,  -208,
    -208,  -208
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -208,  -208,   324,  -208,   224,  -208,  -208,   295,  -208,  -208,
     235,  -146,  -152,  -208,  -208,  -208,  -208,  -208,  -208,   108,
    -208,  -208,   127,  -208,  -208,   232,  -208,   177,  -208,    99,
      -8,  -208,   -23,  -127,   -27,  -208,   263,   -18,   307,   -31,
     -57,  -208,  -208,  -208,  -208,  -208,  -208,  -208,    38,  -208,
    -207,   -47,    19,    -2,   150
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -144
static const yytype_int16 yytable[] =
{
      11,    92,    47,    94,   192,    61,    45,   204,    30,    24,
     230,     1,    25,   131,   110,   224,     8,    25,    33,    35,
      75,    84,    85,   249,    67,    68,    69,    52,    12,    58,
      22,   255,   256,   231,     2,   129,   225,    61,   232,    62,
      34,   111,   112,    70,   219,    37,   113,   114,   115,   116,
     117,   118,   109,   154,    71,   261,     2,   100,   270,   250,
      47,   108,     7,    87,   133,   178,   179,   180,   181,   182,
     135,    62,   137,   153,   135,    96,    86,   244,   183,     7,
     246,     8,   107,   254,     7,    52,   -38,   136,   175,   176,
     177,   262,     7,     7,    58,   151,   241,     9,   260,   157,
     160,     7,    19,   155,    47,    47,   266,   267,    61,   194,
     269,   192,   192,    21,     9,    61,   271,   152,  -143,     9,
     156,   159,  -143,     7,     7,   164,   158,     9,     9,    52,
      52,   195,    20,   142,   230,   207,     9,    20,   192,   208,
      91,    31,    62,   200,   202,    93,   166,    -2,    13,    62,
     100,   151,   100,   252,   228,   212,    29,   231,     9,     9,
      23,    66,   196,     8,    25,    28,     8,   184,   186,   214,
     215,    67,    68,    69,   206,    36,   167,   210,   221,    14,
     119,   120,   121,   127,   213,    61,    64,    28,    54,    47,
      70,   141,   -15,   240,   222,   113,   114,   115,   116,   117,
     118,    71,    59,   -15,   -15,    15,   -15,   -15,    72,    73,
      38,    47,    47,   128,    52,   227,   194,    62,    25,    62,
       8,   151,   144,   200,   151,   257,   247,   145,    -3,    18,
     236,   237,    88,   151,    89,    95,    52,    52,    47,    90,
      97,   130,   240,    66,   -29,     8,    25,   146,   151,    55,
     107,     8,   253,    67,    68,    69,   151,   151,   165,    66,
     151,     8,    25,    52,   130,   218,   151,     8,    25,    67,
      68,    69,    70,   264,   217,    67,    68,    69,    88,   203,
      89,   205,   238,    71,   101,   102,  -136,  -137,    70,   185,
      72,    73,  -133,   216,    70,   223,   226,   229,    66,    71,
       8,    25,   248,   235,   242,    71,    72,    73,    67,    68,
      69,   265,    72,    73,   251,   113,   114,   115,   116,   117,
     118,   162,   258,   259,   268,     6,    24,    70,   132,    25,
     163,   143,    65,   245,   -15,   239,   161,   211,    71,   -14,
     122,   123,   124,   125,   126,   -15,   -15,    15,   -15,   -15,
     -14,   -14,   263,   -14,   -14,   138,     9,     0,   113,   114,
     115,   116,   117,   118,   243,   113,   114,   115,   116,   117,
     118,    55,     0,     8,     8,    25,   113,   114,   115,   116,
     117,   118,     0,     0,   -20,    29,     0,    39,     0,     0,
      40,     0,    41,    42,     8,    25,   -20,     0,   -20,   -20,
       0,     0,     0,     0,     0,    29,     0,   187,     0,     0,
     188,     0,   189,   190,   113,   114,   115,   116,   117,   118,
     169,   170,   171,   172,   173,   174
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-208))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       2,    48,    29,    50,   131,     1,    29,   153,    16,     1,
       3,     1,     4,    17,    71,    15,     3,     4,    20,    21,
      38,    39,    40,     1,    11,    12,    13,    29,     0,    31,
      11,   238,   239,    26,    24,    82,    36,     1,    31,    35,
      21,    72,    73,    30,   196,    26,    50,    51,    52,    53,
      54,    55,    70,   100,    41,     1,    24,    59,   265,    37,
      87,    63,     1,    44,    87,   122,   123,   124,   125,   126,
      88,    35,    90,    37,    92,    56,    15,   223,    31,     1,
     226,     3,    35,   235,     1,    87,    23,    89,   119,   120,
     121,    37,     1,     1,    96,    97,    33,    36,   250,   101,
     102,     1,    36,     3,   131,   132,   258,   259,     1,   132,
     262,   238,   239,    30,    36,     1,   268,    98,    26,    36,
     101,   102,    30,     1,     1,   106,     3,    36,    36,   131,
     132,     1,    40,    95,     3,    26,    36,    40,   265,    30,
      33,    25,    35,   145,   146,    31,     1,     0,     1,    35,
     152,   153,   154,    31,   201,   163,    14,    26,    36,    36,
      34,     1,    32,     3,     4,    15,     3,   129,   130,   187,
     188,    11,    12,    13,   155,    40,    31,   158,   196,     1,
      47,    48,    49,     1,   165,     1,    36,    37,    34,   216,
      30,    31,    14,   216,   196,    50,    51,    52,    53,    54,
      55,    41,    26,    25,    26,    27,    28,    29,    48,    49,
      55,   238,   239,    31,   216,    31,   239,    35,     4,    35,
       3,   223,     5,   225,   226,   243,   228,    10,     0,     1,
     211,   212,    32,   235,    34,    30,   238,   239,   265,    39,
      55,    30,   265,     1,    33,     3,     4,    30,   250,     1,
      35,     3,   233,    11,    12,    13,   258,   259,    31,     1,
     262,     3,     4,   265,    30,     1,   268,     3,     4,    11,
      12,    13,    30,   254,    33,    11,    12,    13,    32,   152,
      34,   154,    17,    41,    28,    29,    18,    18,    30,    31,
      48,    49,    18,    18,    30,    23,    37,     3,     1,    41,
       3,     4,     1,    37,    33,    41,    48,    49,    11,    12,
      13,    18,    48,    49,     3,    50,    51,    52,    53,    54,
      55,     1,    37,    37,    37,     1,     1,    30,    20,     4,
     106,    96,    37,   225,    14,    20,   104,   160,    41,    14,
      42,    43,    44,    45,    46,    25,    26,    27,    28,    29,
      25,    26,   253,    28,    29,    92,    36,    -1,    50,    51,
      52,    53,    54,    55,    38,    50,    51,    52,    53,    54,
      55,     1,    -1,     3,     3,     4,    50,    51,    52,    53,
      54,    55,    -1,    -1,    14,    14,    -1,    16,    -1,    -1,
      19,    -1,    21,    22,     3,     4,    26,    -1,    28,    29,
      -1,    -1,    -1,    -1,    -1,    14,    -1,    16,    -1,    -1,
      19,    -1,    21,    22,    50,    51,    52,    53,    54,    55,
     113,   114,   115,   116,   117,   118
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    24,    57,    58,    59,    58,     1,     3,    36,
     108,   109,     0,     1,     1,    27,    60,    61,     1,    36,
      40,    30,   108,    34,     1,     4,    62,    63,   110,    14,
      86,    25,    64,   109,   108,   109,    40,   108,    55,    16,
      19,    21,    22,    86,    87,    88,    89,    90,    91,   100,
     101,   105,   109,   110,    34,     1,    65,    66,   109,    26,
      76,     1,    35,   107,   110,    63,     1,    11,    12,    13,
      30,    41,    48,    49,    90,    93,    94,    95,    96,    98,
      99,   102,   103,   109,    93,    93,    15,   108,    32,    34,
      39,    33,   107,    31,   107,    30,   108,    55,    77,    78,
     109,    28,    29,    79,    80,    81,    82,    35,   109,    93,
      96,    95,    95,    50,    51,    52,    53,    54,    55,    47,
      48,    49,    42,    43,    44,    45,    46,     1,    31,   107,
      30,    17,    20,    88,    92,    93,   109,    93,    92,    93,
     104,    31,   104,    66,     5,    10,    30,    67,    68,    69,
      71,   109,   108,    37,   107,     3,   108,   109,     3,   108,
     109,    81,     1,    60,   108,    31,     1,    31,    97,    94,
      94,    94,    94,    94,    94,    95,    95,    95,    96,    96,
      96,    96,    96,    31,   104,    31,   104,    16,    19,    21,
      22,    88,    89,   106,    88,     1,    32,    72,    74,    75,
     109,    70,   109,    78,    67,    78,   108,    26,    30,    83,
     108,    83,    86,   108,    93,    93,    18,    33,     1,    68,
      73,    93,   109,    23,    15,    36,    37,    31,   107,     3,
       3,    26,    31,    84,    85,    37,   108,   108,    17,    20,
      88,    33,    33,    38,    67,    75,    67,   109,     1,     1,
      37,     3,    31,   108,    68,   106,   106,    93,    37,    37,
      68,     1,    37,    85,   108,    18,    68,    68,    37,    68,
     106,    68
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:

/* Line 1806 of yacc.c  */
#line 90 "src/generated_parser.y"
    { doProgramDecl((yyvsp[(2) - (8)].id), (yyvsp[(4) - (8)].id), (yyvsp[(5) - (8)].id));
	  inDecl = 1; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 93 "src/generated_parser.y"
    { doProgramDecl(NULL, NULL, NULL);
	  inDecl = 1; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 96 "src/generated_parser.y"
    { doProgramDecl((yyvsp[(2) - (4)].id), NULL, NULL);
	  inDecl = 1; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 99 "src/generated_parser.y"
    { doProgramDecl((yyvsp[(2) - (3)].id), NULL, NULL);
	  inDecl = 1; }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 114 "src/generated_parser.y"
    { exitConstDeclPart(); 
	  inDecl = 0;
	}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 118 "src/generated_parser.y"
    { inDecl = 0; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 128 "src/generated_parser.y"
    { doConstDecl((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 134 "src/generated_parser.y"
    { exitTypeDeclPart(); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 145 "src/generated_parser.y"
    { doTypeDecl((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 151 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(1) - (1)].symbol); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 153 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(1) - (1)].symbol); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 155 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(1) - (1)].symbol); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 160 "src/generated_parser.y"
    { (yyval.symbol) = simpleTypeLookup((yyvsp[(1) - (1)].id)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 165 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 170 "src/generated_parser.y"
    { (yyval.symbol) = appendToScalarListType((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].id)); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 172 "src/generated_parser.y"
    { (yyval.symbol) = createScalarListType((yyvsp[(1) - (1)].id)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 177 "src/generated_parser.y"
    { (yyval.symbol) = createArrayType((yyvsp[(2) - (4)].symbol), (yyvsp[(4) - (4)].symbol)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 179 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 184 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 186 "src/generated_parser.y"
    { (yyval.symbol) = NULL;
	  yyerrok;}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 189 "src/generated_parser.y"
    { (yyval.symbol) = NULL;
	  yyerrok;}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 192 "src/generated_parser.y"
    { (yyval.symbol) = NULL;
	  yyerrok;}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 198 "src/generated_parser.y"
    { (yyval.symbol) = assertArrIndexType((yyvsp[(1) - (1)].symbol)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 200 "src/generated_parser.y"
    { (yyval.symbol) = createRangeType((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 205 "src/generated_parser.y"
    { (yyval.symbol) = createRecordType((yyvsp[(1) - (1)].proxy)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 207 "src/generated_parser.y"
    { (yyval.symbol) = appendFieldToRecordType((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 212 "src/generated_parser.y"
    { (yyval.proxy) = newRecordFieldProxy((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 217 "src/generated_parser.y"
    { exitVarDeclPart(); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 228 "src/generated_parser.y"
    { (yyval.symbol) = doVarDecl((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 230 "src/generated_parser.y"
    { (yyval.symbol) = doVarDecl((yyvsp[(1) - (3)].id), (yyvsp[(2) - (3)].symbol)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 245 "src/generated_parser.y"
    { exitProcOrFuncDecl(); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 247 "src/generated_parser.y"
    { exitProcOrFuncDecl(); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 252 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl((yyvsp[(2) - (4)].id), (yyvsp[(3) - (4)].proxy)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 254 "src/generated_parser.y"
    { (yyval.symbol) = enterFuncDecl((yyvsp[(2) - (6)].id), (yyvsp[(3) - (6)].proxy)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 256 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl((yyvsp[(2) - (3)].id), NULL);
	  yyerrok; }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 259 "src/generated_parser.y"
    { (yyval.symbol) = enterFuncDecl((yyvsp[(2) - (3)].id), NULL);
	  yyerrok; }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 262 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl(NULL, NULL); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 264 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl(NULL, NULL); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 269 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(2) - (3)].proxy); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 271 "src/generated_parser.y"
    { (yyval.proxy) = NULL; }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 273 "src/generated_parser.y"
    { (yyval.proxy) = NULL;
	  yyerrok; }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 279 "src/generated_parser.y"
    { (yyval.proxy) = createParmList((yyvsp[(1) - (1)].proxy)); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 281 "src/generated_parser.y"
    { (yyval.proxy) = appendParmToParmList((yyvsp[(1) - (3)].proxy), (yyvsp[(2) - (3)].proxy)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 286 "src/generated_parser.y"
    { (yyval.proxy) = createNewParm((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 288 "src/generated_parser.y"
    { (yyval.proxy) = createNewVarParm((yyvsp[(2) - (4)].id), (yyvsp[(4) - (4)].symbol)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 290 "src/generated_parser.y"
    { (yyval.proxy) = createNewParm((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].symbol));
	  yyerrok; }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 293 "src/generated_parser.y"
    { (yyval.proxy) = createNewVarParm((yyvsp[(2) - (5)].id), (yyvsp[(4) - (5)].symbol));
	  yyerrok; }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 314 "src/generated_parser.y"
    { assignOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 321 "src/generated_parser.y"
    { (yyval.proxy) = hashLookupToProxy((yyvsp[(1) - (1)].id)); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 323 "src/generated_parser.y"
    { (yyval.proxy) = hashLookupToProxy((yyvsp[(1) - (1)].id)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 325 "src/generated_parser.y"
    { (yyval.proxy) = recordAccessToProxy((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].id) ); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 327 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (2)].proxy); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 332 "src/generated_parser.y"
    { (yyval.proxy) = arrayIndexAccess((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy));  }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 334 "src/generated_parser.y"
    { (yyval.proxy) = concatArrayIndexList((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 339 "src/generated_parser.y"
    { (yyval.proxy) = createArrayIndexList((yyvsp[(1) - (1)].proxy)); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 344 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 346 "src/generated_parser.y"
    { (yyval.proxy) = eqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 348 "src/generated_parser.y"
    { (yyval.proxy) = notEqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 350 "src/generated_parser.y"
    { (yyval.proxy) = lessOrEqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 352 "src/generated_parser.y"
    { (yyval.proxy) = lessOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 354 "src/generated_parser.y"
    { (yyval.proxy) = gtOrEqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 356 "src/generated_parser.y"
    { (yyval.proxy) = gtOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 361 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 363 "src/generated_parser.y"
    { (yyval.proxy) = unaryPlusOp((yyvsp[(2) - (2)].proxy)); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 365 "src/generated_parser.y"
    { (yyval.proxy) = unaryMinusOp((yyvsp[(2) - (2)].proxy)); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 367 "src/generated_parser.y"
    { (yyval.proxy) = plusOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 369 "src/generated_parser.y"
    { (yyval.proxy) = minusOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 371 "src/generated_parser.y"
    { (yyval.proxy) = orOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 376 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 378 "src/generated_parser.y"
    { (yyval.proxy) = multOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 380 "src/generated_parser.y"
    { (yyval.proxy) = divideOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 382 "src/generated_parser.y"
    { (yyval.proxy) = divOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 384 "src/generated_parser.y"
    { (yyval.proxy) = modOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 386 "src/generated_parser.y"
    { (yyval.proxy) = andOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 388 "src/generated_parser.y"
    { (yyval.proxy) = NULL; }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 393 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 395 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 397 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(2) - (3)].proxy); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 399 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 401 "src/generated_parser.y"
    { (yyval.proxy) = unaryNotOp((yyvsp[(2) - (2)].proxy)); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 411 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 413 "src/generated_parser.y"
    { (yyval.proxy) = proxyStringLiteral((yyvsp[(1) - (1)].string)); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 418 "src/generated_parser.y"
    { (yyval.proxy) = proxyIntLiteral((yyvsp[(1) - (1)].integer)); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 420 "src/generated_parser.y"
    { (yyval.proxy) = proxyRealLiteral((yyvsp[(1) - (1)].real)); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 425 "src/generated_parser.y"
    { /* Action is performed one level lower */ }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 427 "src/generated_parser.y"
    { /* TODO might want to explicitly use an empty arg list here */ 
	  procInvok((yyvsp[(1) - (3)].id), NULL); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 434 "src/generated_parser.y"
    { procInvok((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 436 "src/generated_parser.y"
    { // parm returns the list of arguments
	  (yyval.proxy) = concatArgLists((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 442 "src/generated_parser.y"
    { /* Action is performed one level lower */
	  (yyval.proxy) = (yyvsp[(1) - (2)].proxy); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 445 "src/generated_parser.y"
    { /* TODO might want to explicitly use an empty arg list here */
	  (yyval.proxy) = funcInvok((yyvsp[(1) - (3)].id), NULL); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 448 "src/generated_parser.y"
    { (yyval.proxy) = funcInvok((yyvsp[(1) - (3)].id), NULL);
	  yyerrok; }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 455 "src/generated_parser.y"
    { (yyval.proxy) = funcInvok((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 457 "src/generated_parser.y"
    { // parm returns the list of arguments
	  (yyval.proxy) = concatArgLists((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 463 "src/generated_parser.y"
    { // TODO can we use the same action as for function decl?
	  (yyval.proxy) = createArgList((yyvsp[(1) - (1)].proxy)); }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 471 "src/generated_parser.y"
    { endWhileLoop(); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 473 "src/generated_parser.y"
    { continueLoop(); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 475 "src/generated_parser.y"
    { exitLoop(); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 482 "src/generated_parser.y"
    { endWhileLoop(); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 484 "src/generated_parser.y"
    { continueLoop(); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 486 "src/generated_parser.y"
    { exitLoop(); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 491 "src/generated_parser.y"
    { yyerrok; }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 497 "src/generated_parser.y"
    { yyerrok; }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 503 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (3)].id); }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 505 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 510 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (3)].id); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 512 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;



/* Line 1806 of yacc.c  */
#line 2554 "src/parser.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 515 "src/generated_parser.y"


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

