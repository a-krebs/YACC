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
      struct String string;
      char *id;
      double real;
      int integer;
	struct ElementArray *elemarray;
      Symbol *symbol;
      ProxySymbol *proxy;
	void * voidtype;



/* Line 293 of yacc.c  */
#line 265 "src/parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 277 "src/parser.tab.c"

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
#define YYLAST   419

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  147
/* YYNRULES -- Number of states.  */
#define YYNSTATES  273

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
     162,   164,   165,   167,   170,   175,   178,   183,   190,   195,
     199,   203,   206,   209,   213,   216,   222,   224,   228,   232,
     237,   242,   248,   252,   254,   258,   260,   262,   263,   267,
     269,   271,   273,   275,   279,   282,   286,   288,   292,   294,
     296,   300,   304,   308,   312,   316,   320,   322,   325,   328,
     332,   336,   340,   342,   346,   350,   354,   358,   362,   364,
     366,   368,   372,   374,   377,   379,   381,   383,   385,   387,
     389,   391,   395,   397,   401,   406,   410,   415,   417,   421,
     423,   430,   435,   440,   442,   444,   446,   453,   458,   460,
     462,   465,   467,   470,   472,   476,   478,   482
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    -1,     1,    58,    -1,    58,     1,
      -1,     1,    58,     1,    -1,    59,    60,    86,    34,    -1,
      59,     1,    34,    -1,    24,   111,    30,   111,   109,   111,
      31,   110,    -1,    24,   110,    -1,    24,   111,    30,   110,
      -1,    24,   111,   110,    -1,    61,    64,    76,    79,    -1,
       1,    -1,    27,    62,   110,    -1,    -1,    63,    -1,    62,
     110,    63,    -1,   112,    55,    94,    -1,     1,    -1,    25,
      65,   110,    -1,    -1,    66,    -1,    65,   110,    66,    -1,
     111,    55,    67,    -1,     1,    -1,    71,    -1,    68,    -1,
      69,    -1,   111,    -1,    30,    70,    31,    -1,    70,   109,
     111,    -1,   111,    -1,     5,    72,    23,    67,    -1,    10,
      74,    15,    -1,    32,    73,    33,    -1,    32,     1,    33,
      -1,     1,    33,    -1,    32,     1,    -1,    68,    -1,    94,
      38,    94,    -1,    75,    -1,    74,    36,    75,    -1,   111,
      37,    67,    -1,    26,    77,   110,    -1,    -1,    78,    -1,
      77,   110,    78,    -1,   111,    37,    67,    -1,   111,   109,
      78,    -1,    80,    -1,    -1,    81,    -1,    80,    81,    -1,
      82,    60,    86,   110,    -1,    82,   110,    -1,    29,   111,
      83,   110,    -1,    28,   111,    83,    37,    68,   110,    -1,
      28,   111,    83,   110,    -1,    29,     3,   110,    -1,    28,
       3,   110,    -1,    29,   110,    -1,    28,   110,    -1,    30,
      84,    31,    -1,    30,    31,    -1,    26,     3,     1,    37,
      68,    -1,    85,    -1,    84,   110,    85,    -1,     3,    37,
      68,    -1,    26,     3,    37,    68,    -1,     3,     1,    37,
      68,    -1,    26,     3,     1,    37,    68,    -1,    14,    87,
      15,    -1,    88,    -1,    87,   110,    88,    -1,    89,    -1,
     107,    -1,    -1,    90,    39,    94,    -1,   101,    -1,    86,
      -1,   112,    -1,   111,    -1,    90,    34,   111,    -1,    91,
      33,    -1,    90,    32,    92,    -1,    93,    -1,    92,   109,
      93,    -1,    94,    -1,    95,    -1,    94,    55,    95,    -1,
      94,    54,    95,    -1,    94,    52,    95,    -1,    94,    53,
      95,    -1,    94,    50,    95,    -1,    94,    51,    95,    -1,
      96,    -1,    49,    96,    -1,    48,    96,    -1,    95,    49,
      96,    -1,    95,    48,    96,    -1,    95,    47,    96,    -1,
      97,    -1,    96,    46,    97,    -1,    96,    45,    97,    -1,
      96,    44,    97,    -1,    96,    43,    97,    -1,    96,    42,
      97,    -1,     1,    -1,    90,    -1,    99,    -1,    30,    94,
      98,    -1,   102,    -1,    41,    97,    -1,    31,    -1,     1,
      -1,   100,    -1,    13,    -1,    11,    -1,    12,    -1,   103,
      -1,   111,    30,    31,    -1,   104,    -1,   111,    30,    31,
      -1,   111,    30,   105,    31,    -1,   111,     1,    31,    -1,
     111,    30,   105,    31,    -1,   106,    -1,   105,   109,   106,
      -1,    94,    -1,    16,    94,    17,   108,    18,    88,    -1,
      16,    94,    17,    88,    -1,    19,    94,    20,    88,    -1,
      21,    -1,    22,    -1,    89,    -1,    16,    94,    17,   108,
      18,   108,    -1,    19,    94,    20,   108,    -1,    21,    -1,
      22,    -1,     1,    35,    -1,    35,    -1,     1,    36,    -1,
      36,    -1,     3,    40,   111,    -1,     3,    -1,     4,    40,
     112,    -1,     4,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    79,    79,    80,    81,    82,    86,    87,    91,    94,
      97,   100,   107,   111,   115,   120,   124,   125,   129,   131,
     135,   137,   141,   142,   146,   148,   152,   154,   156,   161,
     166,   171,   173,   178,   180,   185,   187,   190,   193,   199,
     201,   206,   208,   213,   218,   220,   224,   225,   229,   231,
     236,   237,   241,   242,   246,   248,   253,   255,   257,   260,
     263,   266,   268,   273,   275,   277,   283,   285,   290,   292,
     294,   297,   303,   307,   308,   312,   313,   314,   318,   320,
     321,   325,   327,   329,   331,   337,   342,   344,   349,   354,
     356,   358,   360,   362,   364,   366,   371,   373,   375,   377,
     379,   381,   386,   388,   390,   392,   394,   396,   398,   403,
     405,   407,   409,   411,   416,   417,   421,   423,   432,   434,
     439,   441,   447,   450,   461,   463,   468,   474,   476,   480,
     486,   487,   488,   490,   492,   497,   498,   499,   501,   503,
     508,   510,   514,   516,   520,   522,   527,   529
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
  "simple_stat", "var", "subscripted_var", "subscripted_var_index_list",
  "subscripted_var_index", "expr", "simple_expr", "term", "factor",
  "R_PAREN_or_error", "unsigned_const", "unsigned_num", "proc_invok",
  "func_invok", "plist_pinvok", "plist_finvok", "parm_list", "parm",
  "struct_stat", "matched_stat", "comma_or_error", "semicolon_or_error",
  "ID_or_err", "decl_ID_or_err", 0
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
      82,    82,    82,    83,    83,    83,    84,    84,    85,    85,
      85,    85,    86,    87,    87,    88,    88,    88,    89,    89,
      89,    90,    90,    90,    90,    91,    92,    92,    93,    94,
      94,    94,    94,    94,    94,    94,    95,    95,    95,    95,
      95,    95,    96,    96,    96,    96,    96,    96,    96,    97,
      97,    97,    97,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   103,   103,   104,   105,   105,   106,
     107,   107,   107,   107,   107,   108,   108,   108,   108,   108,
     109,   109,   110,   110,   111,   111,   112,   112
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     3,     4,     3,     8,     2,
       4,     3,     4,     1,     3,     0,     1,     3,     3,     1,
       3,     0,     1,     3,     3,     1,     1,     1,     1,     1,
       3,     3,     1,     4,     3,     3,     3,     2,     2,     1,
       3,     1,     3,     3,     3,     0,     1,     3,     3,     3,
       1,     0,     1,     2,     4,     2,     4,     6,     4,     3,
       3,     2,     2,     3,     2,     5,     1,     3,     3,     4,
       4,     5,     3,     1,     3,     1,     1,     0,     3,     1,
       1,     1,     1,     3,     2,     3,     1,     3,     1,     1,
       3,     3,     3,     3,     3,     3,     1,     2,     2,     3,
       3,     3,     1,     3,     3,     3,     3,     3,     1,     1,
       1,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     3,     4,     3,     4,     1,     3,     1,
       6,     4,     4,     1,     1,     1,     6,     4,     1,     1,
       2,     1,     2,     1,     3,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,   145,   143,
       9,     0,     1,     4,    13,     0,     0,    21,     5,   142,
       0,     0,    11,     7,    19,   147,     0,    16,     0,    77,
       0,     0,    45,   144,    10,     0,     0,     0,     0,     0,
       0,   133,   134,    80,     0,    73,    75,     0,     0,    79,
     120,    76,     0,    81,     6,    25,     0,    22,     0,     0,
      51,     0,   141,     0,   146,    17,   108,   118,   119,   117,
       0,     0,     0,     0,   109,    18,    89,    96,   102,   110,
     116,   112,   122,    82,     0,     0,    72,    77,     0,     0,
       0,    84,     0,     0,     0,     0,     0,    46,     0,     0,
       0,    12,    50,    52,     0,   140,     0,     0,   113,    98,
      97,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    77,    77,    74,     0,
      86,    88,    83,    78,   125,   121,   129,     0,   127,    23,
       0,     0,     0,    24,    27,    28,    26,    29,    44,     0,
       0,     0,    62,     0,     0,    61,     0,    53,    13,     0,
      55,     0,   115,   114,   111,    94,    95,    92,    93,    91,
      90,   101,   100,    99,   107,   106,   105,   104,   103,   123,
       0,     0,     0,   133,   134,   131,    75,     0,   132,     0,
     124,     0,     0,     0,     0,     0,    41,     0,     0,    32,
      47,    48,    49,    60,     0,     0,     0,    59,     0,     0,
       8,   126,     0,     0,    77,    87,   128,    37,   108,    39,
       0,     0,    82,     0,    34,     0,     0,    30,     0,     0,
       0,     0,    64,     0,    66,     0,    58,    56,    54,    77,
      77,   130,    36,    35,     0,    33,    42,    43,    31,     0,
       0,     0,     0,    63,     0,     0,     0,   137,    40,     0,
       0,    68,     0,     0,    67,    57,    77,    65,    70,     0,
      69,   136,    71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    16,    17,    26,    27,    32,    56,
      57,   143,   144,   145,   198,   146,   194,   220,   195,   196,
      60,    96,    97,   101,   102,   103,   104,   206,   233,   234,
      43,    44,   185,    46,    74,    48,   129,   130,   136,    76,
      77,    78,   164,    79,    80,    49,    81,    50,    82,   137,
     138,    51,   187,   191,    10,    83,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -157
static const yytype_int16 yypact[] =
{
     117,   -16,    27,    26,    13,   347,   134,    22,    56,  -157,
    -157,    75,  -157,  -157,    38,    70,   112,   113,  -157,  -157,
     162,    27,  -157,  -157,  -157,   136,    58,  -157,   102,   365,
     149,   141,   175,  -157,  -157,    21,   213,   363,   280,   280,
     280,  -157,  -157,  -157,    76,  -157,  -157,   216,   192,  -157,
    -157,  -157,     8,  -157,  -157,  -157,    58,  -157,   180,   162,
     125,   211,  -157,   162,  -157,  -157,  -157,  -157,  -157,  -157,
     280,   147,   169,   169,   177,   358,   254,   297,  -157,  -157,
    -157,  -157,  -157,   210,   152,   142,  -157,   365,   280,   162,
     280,  -157,   220,   241,   259,   217,    58,  -157,    11,    31,
      79,  -157,   125,  -157,   324,  -157,   225,    77,  -157,   297,
     297,   280,   280,   280,   280,   280,   280,   169,   169,   169,
     147,   147,   147,   147,   147,   265,   379,   365,  -157,   151,
    -157,   358,  -157,   358,  -157,  -157,   358,   144,  -157,  -157,
      32,   162,   162,  -157,  -157,  -157,  -157,  -157,   162,   217,
     162,     9,  -157,    39,     9,  -157,    39,  -157,    22,   112,
    -157,    58,  -157,  -157,  -157,   254,   254,   254,   254,   254,
     254,   297,   297,   297,  -157,  -157,  -157,  -157,  -157,  -157,
     197,   280,   280,   245,   252,  -157,   256,   257,  -157,   280,
    -157,   280,   226,   296,   263,     5,  -157,   242,   199,  -157,
    -157,  -157,  -157,  -157,   277,   205,    14,  -157,    58,    58,
    -157,  -157,   281,   304,   365,  -157,  -157,  -157,   -22,  -157,
     271,   352,    53,   217,  -157,   162,   217,  -157,   162,   310,
      15,   302,  -157,   154,  -157,   162,  -157,  -157,  -157,   379,
     379,  -157,  -157,  -157,   280,  -157,  -157,  -157,  -157,   275,
     282,   162,    16,  -157,   130,    58,   299,  -157,   358,   162,
     162,  -157,   285,   162,  -157,  -157,   379,  -157,  -157,   162,
    -157,  -157,  -157
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -157,  -157,   322,  -157,   223,  -157,  -157,   293,  -157,  -157,
     253,  -142,  -156,  -157,  -157,  -157,  -157,  -157,  -157,   121,
    -157,  -157,   170,  -157,  -157,   260,  -157,   207,  -157,   111,
     -10,  -157,   -27,  -123,   -25,  -157,  -157,   181,   -15,   303,
     -29,    -1,  -157,  -157,  -157,  -157,  -157,  -157,  -157,   246,
     187,  -157,  -103,   -30,    10,    -2,   279
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -146
static const yytype_int16 yytable[] =
{
      11,   -38,    45,   186,    47,    63,    30,   201,     2,    92,
       7,   242,    61,    -2,    13,     7,   250,   262,    33,    35,
     224,    22,    61,    75,    84,    85,    12,    52,     7,    58,
       8,    34,     7,   192,   151,  -145,    37,   219,    93,  -145,
     -82,   225,   -82,   109,   110,     9,    62,   -82,   149,    20,
       9,   235,   251,   263,    87,   107,    62,    98,    19,     7,
     128,   106,    47,     9,   193,   204,    94,     9,   150,   205,
     108,    24,    23,   131,    25,   133,     7,     7,   162,   255,
       7,   245,   154,   125,   247,    52,   -29,   132,   171,   172,
     173,    86,    58,   147,     9,   261,    20,   153,   156,   189,
     188,    47,    47,   267,   268,    21,   148,   270,   163,   152,
     155,     9,     9,   272,   160,     9,   186,   186,     1,   174,
     175,   176,   177,   178,    52,    52,    29,   111,   112,   113,
     114,   115,   116,   230,    -3,    18,   256,   257,    31,   197,
     199,     2,    55,   186,     8,    61,    98,   147,    98,   209,
       8,    25,    61,    99,   100,     7,   231,    38,    67,    68,
      69,   203,   127,   271,   207,     8,   212,   213,   228,   126,
      66,   210,     8,    25,   131,   190,    36,    70,   221,    62,
      67,    68,    69,    54,   -85,   253,    62,   241,    71,    47,
       9,   222,   111,   112,   113,   114,   115,   116,    61,    70,
      61,    59,   111,   112,   113,   114,   115,   116,   230,    88,
      71,    89,    52,   188,    47,    47,   236,    25,   237,   238,
       8,   147,   140,   197,   147,    91,   248,   141,   211,   258,
     227,   231,    62,   147,    62,    95,   232,    52,    52,   241,
     125,    47,    66,   254,     8,    25,   105,   142,    88,   147,
      89,   134,    67,    68,    69,    90,   161,   147,   147,   217,
      55,   147,     8,  -138,    52,   265,    66,   147,     8,    25,
    -139,    70,   135,   -20,  -135,   214,    67,    68,    69,   226,
     229,    66,    71,     8,    25,   -20,   223,   -20,   -20,    72,
      73,    67,    68,    69,    28,    70,   179,   218,   239,     8,
      25,   117,   118,   119,   243,   252,    71,    67,    68,    69,
      70,   249,   259,    72,    73,    64,    28,   266,   200,   260,
     202,    71,   269,     6,   240,   158,    70,   159,    72,    73,
      65,   111,   112,   113,   114,   115,   116,    71,   -15,   120,
     121,   122,   123,   124,    72,    73,   246,   139,    14,   -15,
     -15,    15,   -15,   -15,   111,   112,   113,   114,   115,   116,
       9,   -15,   157,   208,    24,   264,     0,    25,     8,    25,
     215,   180,   -15,   -15,    15,   -15,   -15,   -14,   216,    29,
       0,    39,     8,    25,    40,     0,    41,    42,   -14,   -14,
     244,   -14,   -14,    29,     0,   181,     0,     0,   182,     0,
     183,   184,   111,   112,   113,   114,   115,   116,   111,   112,
     113,   114,   115,   116,   165,   166,   167,   168,   169,   170
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-157))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       2,    23,    29,   126,    29,    35,    16,   149,    24,     1,
       1,    33,     1,     0,     1,     1,     1,     1,    20,    21,
      15,    11,     1,    38,    39,    40,     0,    29,     1,    31,
       3,    21,     1,     1,     3,    26,    26,   193,    30,    30,
      32,    36,    34,    72,    73,    36,    35,    39,    37,    40,
      36,    37,    37,    37,    44,    70,    35,    59,    36,     1,
      87,    63,    87,    36,    32,    26,    56,    36,    98,    30,
      71,     1,    34,    88,     4,    90,     1,     1,     1,   235,
       1,   223,     3,    30,   226,    87,    33,    89,   117,   118,
     119,    15,    94,    95,    36,   251,    40,    99,   100,   129,
     127,   126,   127,   259,   260,    30,    96,   263,    31,    99,
     100,    36,    36,   269,   104,    36,   239,   240,     1,   120,
     121,   122,   123,   124,   126,   127,    14,    50,    51,    52,
      53,    54,    55,     3,     0,     1,   239,   240,    25,   141,
     142,    24,     1,   266,     3,     1,   148,   149,   150,   159,
       3,     4,     1,    28,    29,     1,    26,    55,    11,    12,
      13,   151,    20,   266,   154,     3,   181,   182,   198,    17,
       1,   161,     3,     4,   189,    31,    40,    30,   193,    35,
      11,    12,    13,    34,    33,    31,    35,   214,    41,   214,
      36,   193,    50,    51,    52,    53,    54,    55,     1,    30,
       1,    26,    50,    51,    52,    53,    54,    55,     3,    32,
      41,    34,   214,   240,   239,   240,   206,     4,   208,   209,
       3,   223,     5,   225,   226,    33,   228,    10,    31,   244,
      31,    26,    35,   235,    35,    55,    31,   239,   240,   266,
      30,   266,     1,   233,     3,     4,    35,    30,    32,   251,
      34,    31,    11,    12,    13,    39,    31,   259,   260,    33,
       1,   263,     3,    18,   266,   255,     1,   269,     3,     4,
      18,    30,    31,    14,    18,    18,    11,    12,    13,    37,
       3,     1,    41,     3,     4,    26,    23,    28,    29,    48,
      49,    11,    12,    13,    15,    30,    31,     1,    17,     3,
       4,    47,    48,    49,    33,     3,    41,    11,    12,    13,
      30,     1,    37,    48,    49,    36,    37,    18,   148,    37,
     150,    41,    37,     1,    20,     1,    30,   104,    48,    49,
      37,    50,    51,    52,    53,    54,    55,    41,    14,    42,
      43,    44,    45,    46,    48,    49,   225,    94,     1,    25,
      26,    27,    28,    29,    50,    51,    52,    53,    54,    55,
      36,    14,   102,   156,     1,   254,    -1,     4,     3,     4,
     189,   125,    25,    26,    27,    28,    29,    14,   191,    14,
      -1,    16,     3,     4,    19,    -1,    21,    22,    25,    26,
      38,    28,    29,    14,    -1,    16,    -1,    -1,    19,    -1,
      21,    22,    50,    51,    52,    53,    54,    55,    50,    51,
      52,    53,    54,    55,   111,   112,   113,   114,   115,   116
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    24,    57,    58,    59,    58,     1,     3,    36,
     110,   111,     0,     1,     1,    27,    60,    61,     1,    36,
      40,    30,   110,    34,     1,     4,    62,    63,   112,    14,
      86,    25,    64,   111,   110,   111,    40,   110,    55,    16,
      19,    21,    22,    86,    87,    88,    89,    90,    91,   101,
     103,   107,   111,   112,    34,     1,    65,    66,   111,    26,
      76,     1,    35,   109,   112,    63,     1,    11,    12,    13,
      30,    41,    48,    49,    90,    94,    95,    96,    97,    99,
     100,   102,   104,   111,    94,    94,    15,   110,    32,    34,
      39,    33,     1,    30,   110,    55,    77,    78,   111,    28,
      29,    79,    80,    81,    82,    35,   111,    94,    97,    96,
      96,    50,    51,    52,    53,    54,    55,    47,    48,    49,
      42,    43,    44,    45,    46,    30,    17,    20,    88,    92,
      93,    94,   111,    94,    31,    31,    94,   105,   106,    66,
       5,    10,    30,    67,    68,    69,    71,   111,   110,    37,
     109,     3,   110,   111,     3,   110,   111,    81,     1,    60,
     110,    31,     1,    31,    98,    95,    95,    95,    95,    95,
      95,    96,    96,    96,    97,    97,    97,    97,    97,    31,
     105,    16,    19,    21,    22,    88,    89,   108,    88,   109,
      31,   109,     1,    32,    72,    74,    75,   111,    70,   111,
      78,    67,    78,   110,    26,    30,    83,   110,    83,    86,
     110,    31,    94,    94,    18,    93,   106,    33,     1,    68,
      73,    94,   111,    23,    15,    36,    37,    31,   109,     3,
       3,    26,    31,    84,    85,    37,   110,   110,   110,    17,
      20,    88,    33,    33,    38,    67,    75,    67,   111,     1,
       1,    37,     3,    31,   110,    68,   108,   108,    94,    37,
      37,    68,     1,    37,    85,   110,    18,    68,    68,    37,
      68,   108,    68
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
#line 92 "src/generated_parser.y"
    { doProgramDecl((yyvsp[(2) - (8)].id), (yyvsp[(4) - (8)].id), (yyvsp[(5) - (8)].id));
	  inDecl = 1; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 95 "src/generated_parser.y"
    { doProgramDecl(NULL, NULL, NULL);
	  inDecl = 1; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 98 "src/generated_parser.y"
    { doProgramDecl((yyvsp[(2) - (4)].id), NULL, NULL);
	  inDecl = 1; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 101 "src/generated_parser.y"
    { doProgramDecl((yyvsp[(2) - (3)].id), NULL, NULL);
	  inDecl = 1; }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 116 "src/generated_parser.y"
    { exitConstDeclPart(); 
	  inDecl = 0;
	}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 120 "src/generated_parser.y"
    { inDecl = 0; }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 130 "src/generated_parser.y"
    { doConstDecl((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 136 "src/generated_parser.y"
    { exitTypeDeclPart(); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 147 "src/generated_parser.y"
    { doTypeDecl((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 153 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(1) - (1)].symbol); }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 155 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(1) - (1)].symbol); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 157 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(1) - (1)].symbol); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 162 "src/generated_parser.y"
    { (yyval.symbol) = simpleTypeLookup((yyvsp[(1) - (1)].id)); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 167 "src/generated_parser.y"
    { (yyval.symbol) = createScalarListType((yyvsp[(2) - (3)].elemarray)); }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 172 "src/generated_parser.y"
    { (yyval.elemarray) = appendToScalarListType((yyvsp[(1) - (3)].elemarray), (yyvsp[(3) - (3)].id)); }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 174 "src/generated_parser.y"
    { (yyval.elemarray) = createScalarList((yyvsp[(1) - (1)].id)); }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 179 "src/generated_parser.y"
    { (yyval.symbol) = createArrayType((yyvsp[(2) - (4)].symbol), (yyvsp[(4) - (4)].symbol)); }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 181 "src/generated_parser.y"
    { (yyval.symbol) = createRecordType((yyvsp[(2) - (3)].elemarray)); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 186 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(2) - (3)].symbol); }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 188 "src/generated_parser.y"
    { (yyval.symbol) = NULL;
	  yyerrok;}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 191 "src/generated_parser.y"
    { (yyval.symbol) = NULL;
	  yyerrok;}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 194 "src/generated_parser.y"
    { (yyval.symbol) = NULL;
	  yyerrok;}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 200 "src/generated_parser.y"
    { (yyval.symbol) = assertArrIndexType((yyvsp[(1) - (1)].symbol)); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 202 "src/generated_parser.y"
    { (yyval.symbol) = createRangeType((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 207 "src/generated_parser.y"
    { (yyval.elemarray) = createRecordMemberList((yyvsp[(1) - (1)].proxy)); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 209 "src/generated_parser.y"
    { (yyval.elemarray) = appendToRecordMemberList((yyvsp[(1) - (3)].elemarray), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 214 "src/generated_parser.y"
    { (yyval.proxy) = newRecordFieldProxy((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 219 "src/generated_parser.y"
    { exitVarDeclPart(); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 230 "src/generated_parser.y"
    { (yyval.symbol) = doVarDecl((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 232 "src/generated_parser.y"
    { (yyval.symbol) = doVarDecl((yyvsp[(1) - (3)].id), (yyvsp[(2) - (3)].symbol)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 247 "src/generated_parser.y"
    { exitProcOrFuncDecl(); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 249 "src/generated_parser.y"
    { exitProcOrFuncDecl(); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 254 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl((yyvsp[(2) - (4)].id), (yyvsp[(3) - (4)].elemarray)); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 256 "src/generated_parser.y"
    { (yyval.symbol) = enterFuncDecl((yyvsp[(2) - (6)].id), (yyvsp[(3) - (6)].elemarray), (yyvsp[(5) - (6)].symbol)); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 258 "src/generated_parser.y"
    { (yyval.symbol) = enterFuncDecl((yyvsp[(2) - (4)].id), (yyvsp[(3) - (4)].elemarray), NULL); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 261 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl((yyvsp[(2) - (3)].id), NULL);
	  yyerrok; }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 264 "src/generated_parser.y"
    { (yyval.symbol) = enterFuncDecl((yyvsp[(2) - (3)].id), NULL, NULL);
	  yyerrok; }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 267 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl(NULL, NULL); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 269 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl(NULL, NULL); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 274 "src/generated_parser.y"
    { (yyval.elemarray) = (yyvsp[(2) - (3)].elemarray); }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 276 "src/generated_parser.y"
    { (yyval.proxy) = NULL; }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 278 "src/generated_parser.y"
    { (yyval.proxy) = NULL;
	  yyerrok; }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 284 "src/generated_parser.y"
    { (yyval.elemarray) = createParmList((yyvsp[(1) - (1)].symbol)); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 286 "src/generated_parser.y"
    { (yyval.elemarray) = appendParmToParmList((yyvsp[(1) - (3)].elemarray), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 291 "src/generated_parser.y"
    { (yyval.symbol) = createNewParm((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 293 "src/generated_parser.y"
    { (yyval.symbol) = createNewVarParm((yyvsp[(2) - (4)].id), (yyvsp[(4) - (4)].symbol)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 295 "src/generated_parser.y"
    { (yyval.symbol) = NULL;//$<proxy>$ = createNewParm($<id>1, $<symbol>3);
	  yyerrok; }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 298 "src/generated_parser.y"
    { (yyval.symbol) = NULL;//$<proxy>$ = createNewVarParm($<id>2, $<symbol>4);
	  yyerrok; }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 319 "src/generated_parser.y"
    { assignOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 326 "src/generated_parser.y"
    { (yyval.proxy) = hashLookupToProxy((yyvsp[(1) - (1)].id)); }
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 328 "src/generated_parser.y"
    { (yyval.proxy) = hashLookupToProxy((yyvsp[(1) - (1)].id)); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 330 "src/generated_parser.y"
    { (yyval.proxy) = recordAccessToProxy((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].id) ); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 332 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (2)].proxy); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 338 "src/generated_parser.y"
    { (yyval.proxy) = arrayIndexAccess((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy));  }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 343 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy);  }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 345 "src/generated_parser.y"
    { (yyval.proxy) = concatArrayIndexList((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 350 "src/generated_parser.y"
    { (yyval.proxy) = createArrayIndexList((yyvsp[(1) - (1)].proxy)); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 355 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 357 "src/generated_parser.y"
    { (yyval.proxy) = eqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 359 "src/generated_parser.y"
    { (yyval.proxy) = notEqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 361 "src/generated_parser.y"
    { (yyval.proxy) = lessOrEqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 363 "src/generated_parser.y"
    { (yyval.proxy) = lessOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 365 "src/generated_parser.y"
    { (yyval.proxy) = gtOrEqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 367 "src/generated_parser.y"
    { (yyval.proxy) = gtOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 372 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 374 "src/generated_parser.y"
    { (yyval.proxy) = unaryPlusOp((yyvsp[(2) - (2)].proxy)); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 376 "src/generated_parser.y"
    { (yyval.proxy) = unaryMinusOp((yyvsp[(2) - (2)].proxy)); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 378 "src/generated_parser.y"
    { (yyval.proxy) = plusOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 380 "src/generated_parser.y"
    { (yyval.proxy) = minusOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 382 "src/generated_parser.y"
    { (yyval.proxy) = orOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 387 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 389 "src/generated_parser.y"
    { (yyval.proxy) = multOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 391 "src/generated_parser.y"
    { (yyval.proxy) = divideOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 393 "src/generated_parser.y"
    { (yyval.proxy) = divOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 395 "src/generated_parser.y"
    { (yyval.proxy) = modOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 397 "src/generated_parser.y"
    { (yyval.proxy) = andOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 399 "src/generated_parser.y"
    { (yyval.proxy) = NULL; }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 404 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 406 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 408 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(2) - (3)].proxy); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 410 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 412 "src/generated_parser.y"
    { (yyval.proxy) = unaryNotOp((yyvsp[(2) - (2)].proxy)); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 422 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 424 "src/generated_parser.y"
    { 
	    if (getStrlen((yyvsp[(1) - (1)].string)) <= 1) {
	        (yyval.proxy) = proxyCharLiteral((yyvsp[(1) - (1)].string)); 
	} else { (yyval.proxy) = proxyStringLiteral((yyvsp[(1) - (1)].string));} 
	}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 433 "src/generated_parser.y"
    { (yyval.proxy) = proxyIntLiteral((yyvsp[(1) - (1)].integer)); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 435 "src/generated_parser.y"
    { (yyval.proxy) = proxyRealLiteral((yyvsp[(1) - (1)].real)); }
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 440 "src/generated_parser.y"
    { /* Action is performed one level lower and nothing returned */ }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 442 "src/generated_parser.y"
    { /* TODO might want to explicitly use an empty arg list here */ 
	  procInvok((yyvsp[(1) - (3)].id), NULL); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 448 "src/generated_parser.y"
    { /* Action is performed one level lower */
	  (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 451 "src/generated_parser.y"
    { /* TODO might want to explicitly use an empty arg list here */
	  (yyval.proxy) = funcInvok((yyvsp[(1) - (3)].id), NULL); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 462 "src/generated_parser.y"
    { procInvok((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].elemarray)); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 469 "src/generated_parser.y"
    { (yyval.proxy) = funcInvok((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].elemarray)); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 475 "src/generated_parser.y"
    { (yyval.elemarray) = (yyvsp[(1) - (1)].elemarray); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 477 "src/generated_parser.y"
    { (yyval.elemarray) = concatArgLists((yyvsp[(1) - (3)].elemarray), (yyvsp[(3) - (3)].elemarray)); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 481 "src/generated_parser.y"
    { // TODO can we use the same action as for function decl?
	  (yyval.elemarray) = createArgList((yyvsp[(1) - (1)].proxy)); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 489 "src/generated_parser.y"
    { endWhileLoop(); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 491 "src/generated_parser.y"
    { continueLoop(); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 493 "src/generated_parser.y"
    { exitLoop(); }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 500 "src/generated_parser.y"
    { endWhileLoop(); }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 502 "src/generated_parser.y"
    { continueLoop(); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 504 "src/generated_parser.y"
    { exitLoop(); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 509 "src/generated_parser.y"
    { yyerrok; }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 515 "src/generated_parser.y"
    { yyerrok; }
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 521 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (3)].id); }
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 523 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 528 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (3)].id); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 530 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;



/* Line 1806 of yacc.c  */
#line 2564 "src/parser.tab.c"
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
#line 533 "src/generated_parser.y"


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
        if (errMsg) free(errMsg);
}

