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
#include "SymbolAll.h"
#include "ActionsAll.h"
#include "Utils.h"
#include "Tree.h"

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
#line 107 "src/parser.tab.c"

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
#line 38 "src/generated_parser.y"

      char character;
      struct String string;
      char *id;
      double real;
      int integer;
      struct ElementArray *elemarray;
      Symbol *symbol;
      ProxySymbol *proxy;
      void * voidtype;
      struct treeNode *node;



/* Line 293 of yacc.c  */
#line 268 "src/parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 280 "src/parser.tab.c"

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
#define YYLAST   440

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  162
/* YYNRULES -- Number of states.  */
#define YYNSTATES  304

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
     162,   164,   165,   167,   170,   175,   178,   181,   184,   188,
     191,   193,   199,   203,   206,   208,   212,   215,   221,   223,
     227,   231,   236,   241,   247,   251,   253,   257,   259,   261,
     262,   266,   268,   270,   272,   276,   279,   281,   283,   287,
     290,   294,   296,   300,   302,   304,   308,   312,   316,   320,
     324,   328,   330,   333,   336,   340,   344,   348,   350,   354,
     358,   362,   366,   370,   372,   374,   376,   380,   382,   385,
     387,   389,   391,   393,   395,   397,   399,   403,   405,   409,
     414,   418,   423,   425,   429,   431,   433,   438,   442,   445,
     449,   451,   453,   456,   458,   463,   467,   471,   473,   475,
     478,   481,   484,   487,   490,   493,   496,   498,   501,   503,
     507,   509,   513
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    58,    -1,     1,    58,    -1,    58,     1,
      -1,     1,    58,     1,    -1,    59,    60,    88,    34,    -1,
      59,     1,    34,    -1,    24,   122,    30,   122,   120,   122,
      31,   121,    -1,    24,   121,    -1,    24,   122,    30,   121,
      -1,    24,   122,   121,    -1,    61,    64,    76,    79,    -1,
       1,    -1,    27,    62,   121,    -1,    -1,    63,    -1,    62,
     121,    63,    -1,   123,    55,    97,    -1,     1,    -1,    25,
      65,   121,    -1,    -1,    66,    -1,    65,   121,    66,    -1,
     122,    55,    67,    -1,     1,    -1,    71,    -1,    68,    -1,
      69,    -1,   122,    -1,    30,    70,    31,    -1,    70,   120,
     122,    -1,   122,    -1,     5,    72,    23,    67,    -1,    10,
      74,    15,    -1,    32,    73,    33,    -1,    32,     1,    33,
      -1,     1,    33,    -1,    32,     1,    -1,    68,    -1,    97,
      38,    97,    -1,    75,    -1,    74,    36,    75,    -1,   122,
      37,    67,    -1,    26,    77,   121,    -1,    -1,    78,    -1,
      77,   121,    78,    -1,   122,    37,    67,    -1,   122,   120,
      78,    -1,    80,    -1,    -1,    81,    -1,    80,    81,    -1,
      82,    60,    88,   121,    -1,    82,   121,    -1,    29,    83,
      -1,    28,    84,    -1,   122,    85,   121,    -1,     3,   121,
      -1,   121,    -1,   122,    85,    37,    68,   121,    -1,   122,
      85,   121,    -1,     3,   121,    -1,   121,    -1,    30,    86,
      31,    -1,    30,    31,    -1,    26,     3,     1,    37,    68,
      -1,    87,    -1,    86,   121,    87,    -1,     3,    37,    68,
      -1,    26,     3,    37,    68,    -1,     3,     1,    37,    68,
      -1,    26,     3,     1,    37,    68,    -1,    14,    89,    15,
      -1,    90,    -1,    89,   121,    90,    -1,    91,    -1,   111,
      -1,    -1,    92,    39,    97,    -1,   104,    -1,    88,    -1,
     122,    -1,    93,    34,   122,    -1,    94,    33,    -1,   123,
      -1,   122,    -1,    93,    34,   122,    -1,    94,    33,    -1,
      93,    32,    95,    -1,    96,    -1,    95,   120,    96,    -1,
      97,    -1,    98,    -1,    97,    55,    98,    -1,    97,    54,
      98,    -1,    97,    52,    98,    -1,    97,    53,    98,    -1,
      97,    50,    98,    -1,    97,    51,    98,    -1,    99,    -1,
      49,    99,    -1,    48,    99,    -1,    98,    49,    99,    -1,
      98,    48,    99,    -1,    98,    47,    99,    -1,   100,    -1,
      99,    46,   100,    -1,    99,    45,   100,    -1,    99,    44,
     100,    -1,    99,    43,   100,    -1,    99,    42,   100,    -1,
       1,    -1,    93,    -1,   102,    -1,    30,    97,   101,    -1,
     105,    -1,    41,   100,    -1,    31,    -1,     1,    -1,   103,
      -1,    13,    -1,    11,    -1,    12,    -1,   106,    -1,   122,
      30,    31,    -1,   107,    -1,   122,    30,    31,    -1,   122,
      30,   108,    31,    -1,   122,     1,    31,    -1,   122,    30,
     108,    31,    -1,   109,    -1,   108,   120,   109,    -1,    97,
      -1,    97,    -1,   115,     1,   117,   118,    -1,   115,   117,
     118,    -1,   115,   116,    -1,    19,   110,   112,    -1,    21,
      -1,    22,    -1,    20,    90,    -1,    91,    -1,   115,     1,
     117,   119,    -1,   115,   117,   119,    -1,    19,   110,   114,
      -1,    21,    -1,    22,    -1,    20,   113,    -1,    16,    97,
      -1,    17,    90,    -1,    17,   113,    -1,    18,    90,    -1,
      18,   113,    -1,     1,    35,    -1,    35,    -1,     1,    36,
      -1,    36,    -1,     3,    40,   122,    -1,     3,    -1,     4,
      40,   123,    -1,     4,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    83,    84,    85,    89,    90,    94,    97,
     100,   103,   109,   111,   115,   120,   124,   125,   129,   131,
     135,   137,   141,   142,   146,   148,   152,   154,   156,   161,
     166,   171,   173,   178,   180,   185,   187,   190,   193,   199,
     201,   206,   208,   213,   218,   221,   225,   226,   230,   232,
     237,   238,   242,   243,   247,   249,   254,   256,   261,   263,
     266,   271,   273,   275,   278,   284,   286,   288,   294,   296,
     301,   303,   305,   308,   314,   318,   319,   323,   324,   325,
     329,   331,   332,   336,   338,   340,   345,   347,   349,   351,
     356,   361,   363,   368,   373,   375,   377,   379,   381,   383,
     385,   390,   392,   394,   396,   398,   400,   405,   407,   409,
     411,   413,   415,   417,   422,   424,   426,   428,   430,   435,
     436,   440,   442,   451,   453,   458,   460,   466,   469,   480,
     482,   487,   493,   495,   499,   504,   509,   510,   511,   512,
     514,   516,   521,   526,   527,   528,   529,   531,   533,   538,
     543,   548,   553,   558,   563,   568,   570,   574,   576,   580,
     582,   587,   589
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
  "proc_decl_list", "proc_decl", "proc_heading", "proc_heading_proc",
  "proc_heading_func", "f_parm_decl", "f_parm_list", "f_parm",
  "compound_stat", "stat_list", "stat", "simple_stat", "assigned_var",
  "var", "subscripted_var", "subscripted_var_index_list",
  "subscripted_var_index", "expr", "simple_expr", "term", "factor",
  "R_PAREN_or_error", "unsigned_const", "unsigned_num", "proc_invok",
  "func_invok", "plist_pinvok", "plist_finvok", "parm_list", "parm",
  "while_expr", "struct_stat", "do_loop_stat", "matched_stat",
  "do_loop_matched_stat", "if_part", "then_stat_part",
  "then_matched_stat_part", "else_stat_part", "else_matched_stat_part",
  "comma_or_error", "semicolon_or_error", "ID_or_err", "decl_ID_or_err", 0
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
      79,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      83,    84,    84,    84,    84,    85,    85,    85,    86,    86,
      87,    87,    87,    87,    88,    89,    89,    90,    90,    90,
      91,    91,    91,    92,    92,    92,    93,    93,    93,    93,
      94,    95,    95,    96,    97,    97,    97,    97,    97,    97,
      97,    98,    98,    98,    98,    98,    98,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   100,   100,   100,   101,
     101,   102,   102,   103,   103,   104,   104,   105,   105,   106,
     106,   107,   108,   108,   109,   110,   111,   111,   111,   111,
     111,   111,   112,   113,   113,   113,   113,   113,   113,   114,
     115,   116,   117,   118,   119,   120,   120,   121,   121,   122,
     122,   123,   123
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     3,     4,     3,     8,     2,
       4,     3,     4,     1,     3,     0,     1,     3,     3,     1,
       3,     0,     1,     3,     3,     1,     1,     1,     1,     1,
       3,     3,     1,     4,     3,     3,     3,     2,     2,     1,
       3,     1,     3,     3,     3,     0,     1,     3,     3,     3,
       1,     0,     1,     2,     4,     2,     2,     2,     3,     2,
       1,     5,     3,     2,     1,     3,     2,     5,     1,     3,
       3,     4,     4,     5,     3,     1,     3,     1,     1,     0,
       3,     1,     1,     1,     3,     2,     1,     1,     3,     2,
       3,     1,     3,     1,     1,     3,     3,     3,     3,     3,
       3,     1,     2,     2,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     1,     1,     1,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     4,
       3,     4,     1,     3,     1,     1,     4,     3,     2,     3,
       1,     1,     2,     1,     4,     3,     3,     1,     1,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     1,     3,
       1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,   160,   158,
       9,     0,     1,     4,    13,     0,     0,    21,     5,   157,
       0,     0,    11,     7,    19,   162,     0,    16,     0,    79,
       0,     0,    45,   159,    10,     0,     0,     0,     0,     0,
       0,   140,   141,    82,     0,    75,    77,     0,     0,     0,
      81,   125,    78,     0,     0,    86,     6,    25,     0,    22,
       0,     0,    51,     0,   156,     0,   161,    17,   113,   123,
     124,   122,     0,     0,     0,     0,   114,     0,    18,    94,
     101,   107,   115,   121,   117,   127,    87,   150,   135,     0,
      74,    79,     0,     0,     0,    89,     0,    79,   138,     0,
       0,     0,     0,     0,     0,    46,     0,     0,     0,    12,
      50,    52,     0,   155,     0,     0,   118,   103,   102,     0,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    79,   139,    76,    80,
       0,    91,    93,    88,     0,     0,     0,   140,   141,   151,
      77,   152,     0,    79,   137,   130,   126,   134,     0,   132,
      23,     0,     0,     0,    24,    27,    28,    26,    29,    44,
       0,     0,     0,    57,    64,     0,     0,    56,    60,     0,
      53,    13,     0,    55,     0,   120,   119,   116,    88,    99,
     100,    97,    98,    96,    95,   106,   105,   104,   112,   111,
     110,   109,   108,   128,     0,   142,     0,     0,   147,   148,
     143,     0,   136,     0,     0,     0,   153,   129,     0,     0,
       0,     0,     0,    41,     0,     0,    32,    47,    48,    49,
      63,     0,     0,     0,    59,     0,     0,     8,   131,    92,
       0,     0,     0,    79,   146,     0,    79,   145,   133,    37,
     113,    39,     0,     0,    87,     0,    34,     0,     0,    30,
       0,     0,     0,     0,    66,     0,    68,     0,    62,    58,
      54,     0,     0,     0,   149,   144,   154,    36,    35,     0,
      33,    42,    43,    31,     0,     0,     0,     0,    65,     0,
       0,    40,     0,     0,    70,     0,     0,    69,    61,    67,
      72,     0,    71,    73
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    16,    17,    26,    27,    32,    58,
      59,   164,   165,   166,   225,   167,   221,   252,   222,   223,
      62,   104,   105,   109,   110,   111,   112,   177,   173,   233,
     265,   266,    43,    44,   205,    46,    47,    76,    77,   140,
     141,    88,    79,    80,    81,   187,    82,    83,    50,    84,
      51,    85,   158,   159,    89,    52,   137,   151,   244,    53,
      98,    99,   154,   247,   218,    10,    86,    55
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -233
static const yytype_int16 yypact[] =
{
      97,    15,    49,    87,   132,   342,   292,   109,   119,  -233,
    -233,    50,  -233,  -233,    65,    27,   157,   149,  -233,  -233,
     208,    49,  -233,  -233,  -233,   152,    71,  -233,   159,   360,
     183,   200,   202,  -233,  -233,    48,   231,   358,   297,   297,
     297,  -233,  -233,  -233,    89,  -233,  -233,   204,   240,   230,
    -233,  -233,  -233,    29,     2,  -233,  -233,  -233,    71,  -233,
     226,   208,   285,   248,  -233,   208,  -233,  -233,  -233,  -233,
    -233,  -233,   297,   227,   186,   186,   241,   233,   373,   212,
     393,  -233,  -233,  -233,  -233,  -233,   255,   373,   373,   276,
    -233,   360,   297,   297,   208,   264,   287,   390,  -233,   289,
     280,    13,   374,   330,    71,  -233,    20,   127,   140,  -233,
     285,  -233,   325,  -233,   284,   155,  -233,   393,   393,   208,
    -233,   297,   297,   297,   297,   297,   297,   186,   186,   186,
     227,   227,   227,   227,   227,   275,   360,  -233,  -233,   373,
     180,  -233,   373,   283,   394,   289,   297,   301,   307,  -233,
     313,  -233,   145,   360,  -233,  -233,  -233,   373,   201,  -233,
    -233,    59,   208,   208,  -233,  -233,  -233,  -233,  -233,   208,
     330,   208,   193,  -233,  -233,   128,   193,  -233,  -233,   128,
    -233,   109,   157,  -233,    71,  -233,  -233,  -233,  -233,   212,
     212,   212,   212,   212,   212,   393,   393,   393,  -233,  -233,
    -233,  -233,  -233,  -233,   211,  -233,   297,   297,  -233,  -233,
    -233,   156,  -233,   312,   287,   316,  -233,  -233,   297,   303,
     317,   314,    32,  -233,   304,   219,  -233,  -233,  -233,  -233,
    -233,   339,   286,    41,  -233,    71,    71,  -233,  -233,  -233,
     324,   287,   331,   390,  -233,   316,   390,  -233,  -233,  -233,
     162,  -233,   315,   367,    63,   330,  -233,   208,   330,  -233,
     208,   354,    21,   370,  -233,   147,  -233,   208,  -233,  -233,
    -233,   394,   331,   394,  -233,  -233,  -233,  -233,  -233,   297,
    -233,  -233,  -233,  -233,   320,   341,   208,    34,  -233,   146,
      71,   373,   208,   208,  -233,   343,   208,  -233,  -233,  -233,
    -233,   208,  -233,  -233
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -233,  -233,   384,  -233,   277,  -233,  -233,   353,  -233,  -233,
     290,  -161,  -183,  -233,  -233,  -233,  -233,  -233,  -233,   134,
    -233,  -233,   111,  -233,  -233,   291,  -233,  -233,  -233,   216,
    -233,   107,   -12,  -233,   -24,   -96,  -233,   -22,    -9,  -233,
     234,   -27,   308,    37,     6,  -233,  -233,  -233,  -233,  -233,
    -233,  -233,   272,   181,  -131,  -233,  -233,    24,  -233,   -91,
    -233,   -88,  -143,  -232,   -25,    12,    -2,   189
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -161
static const yytype_int16 yytable[] =
{
      11,   150,   212,   100,    30,    45,   152,    48,   145,   228,
      65,    78,    87,   275,    68,   213,     8,    25,    33,    35,
      49,    63,   285,    22,    69,    70,    71,    54,    24,    60,
      96,    25,   101,    34,   -87,   295,   -87,   251,    37,     2,
     275,   -83,     7,    72,   156,   115,    97,   256,   210,    63,
       7,     7,     8,   211,    73,    64,    91,   170,   286,   106,
     219,    74,    75,   114,   215,   139,   142,   138,   257,    48,
     102,   296,     7,   149,   157,    48,   240,     9,   267,   116,
      21,   171,    49,    64,   290,     9,     9,    12,    49,    54,
       7,   220,   143,   135,   280,    54,   -29,   282,     1,    23,
      60,   168,   212,   294,    90,   175,   179,     9,   157,   299,
     300,   117,   118,   302,    48,   206,   169,   188,   303,   174,
     178,     2,    48,   242,   183,     9,   245,    49,     7,   216,
     172,    48,    -2,    13,    54,    49,   198,   199,   200,   201,
     202,     7,    54,   176,    49,    19,   214,   150,     7,   262,
     150,    54,   152,   272,   231,   152,   185,   241,   232,    20,
     224,   226,    97,     9,   195,   196,   197,   106,   168,   106,
     236,    29,   263,   144,    31,   210,     9,   210,   288,   142,
     211,    63,   211,     9,   230,   -38,   186,    68,   234,     8,
      25,   157,    36,   253,     7,   277,   237,    69,    70,    71,
     260,    57,    63,     8,    28,   121,   122,   123,   124,   125,
     126,     8,    63,   -90,    38,    64,    72,    56,   254,  -160,
      63,    48,   216,  -160,    48,    66,    28,    73,    61,     9,
       8,    25,   217,    20,    49,    25,    64,    49,    69,    70,
      71,    54,   238,    92,    54,   268,    64,   269,   270,    48,
     259,    48,   291,   168,    64,   224,   168,    72,   283,   127,
     128,   129,    49,    95,    49,   168,   120,   274,    73,    54,
     276,    54,    93,    93,    94,   119,    68,   289,     8,    25,
     227,   103,   229,   113,   168,   135,    69,    70,    71,   262,
     168,   168,    -3,    18,   168,   274,   136,   276,    68,   168,
       8,    25,   298,   -85,   144,    72,   203,   153,    69,    70,
      71,   155,   263,   107,   108,   184,    73,   264,   250,  -147,
       8,    25,   -84,    74,    75,  -148,   181,    72,    69,    70,
      71,  -143,   243,     8,   246,   161,   249,   255,    73,   -15,
     162,   258,   261,    14,   271,    74,    75,    72,   278,   273,
     -15,   -15,    15,   -15,   -15,   284,   -15,   292,    73,    24,
     163,     9,    25,     8,    25,    74,    75,   -15,   -15,    15,
     -15,   -15,   -14,   287,    29,    57,    39,     8,   293,    40,
     301,    41,    42,   -14,   -14,     6,   -14,   -14,   -20,   182,
      67,   281,   160,     8,    25,   235,   297,     8,    25,   248,
     -20,   180,   -20,   -20,    29,   279,    39,   204,    29,   146,
      39,   147,   148,   207,     0,   208,   209,   121,   122,   123,
     124,   125,   126,   121,   122,   123,   124,   125,   126,   189,
     190,   191,   192,   193,   194,   130,   131,   132,   133,   134,
     239
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-233))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       2,    97,   145,     1,    16,    29,    97,    29,    96,   170,
      35,    38,    39,   245,     1,   146,     3,     4,    20,    21,
      29,     1,     1,    11,    11,    12,    13,    29,     1,    31,
       1,     4,    30,    21,    32,     1,    34,   220,    26,    24,
     272,    39,     1,    30,    31,    72,    17,    15,   144,     1,
       1,     1,     3,   144,    41,    35,    44,    37,    37,    61,
       1,    48,    49,    65,   152,    92,    93,    91,    36,    91,
      58,    37,     1,    97,   101,    97,   207,    36,    37,    73,
      30,   106,    91,    35,   267,    36,    36,     0,    97,    91,
       1,    32,    94,    30,   255,    97,    33,   258,     1,    34,
     102,   103,   245,   286,    15,   107,   108,    36,   135,   292,
     293,    74,    75,   296,   136,   140,   104,   119,   301,   107,
     108,    24,   144,   211,   112,    36,   214,   136,     1,   153,
       3,   153,     0,     1,   136,   144,   130,   131,   132,   133,
     134,     1,   144,     3,   153,    36,     1,   243,     1,     3,
     246,   153,   243,   241,    26,   246,     1,     1,    30,    40,
     162,   163,    17,    36,   127,   128,   129,   169,   170,   171,
     182,    14,    26,    17,    25,   271,    36,   273,    31,   206,
     271,     1,   273,    36,   172,    23,    31,     1,   176,     3,
       4,   218,    40,   220,     1,    33,   184,    11,    12,    13,
     225,     1,     1,     3,    15,    50,    51,    52,    53,    54,
      55,     3,     1,    33,    55,    35,    30,    34,   220,    26,
       1,   243,   246,    30,   246,    36,    37,    41,    26,    36,
       3,     4,    31,    40,   243,     4,    35,   246,    11,    12,
      13,   243,    31,    39,   246,   233,    35,   235,   236,   271,
      31,   273,   279,   255,    35,   257,   258,    30,   260,    47,
      48,    49,   271,    33,   273,   267,    33,   243,    41,   271,
     246,   273,    32,    32,    34,    34,     1,   265,     3,     4,
     169,    55,   171,    35,   286,    30,    11,    12,    13,     3,
     292,   293,     0,     1,   296,   271,    20,   273,     1,   301,
       3,     4,   290,    39,    17,    30,    31,    18,    11,    12,
      13,    31,    26,    28,    29,    31,    41,    31,     1,    18,
       3,     4,    39,    48,    49,    18,     1,    30,    11,    12,
      13,    18,    20,     3,    18,     5,    33,    23,    41,    14,
      10,    37,     3,     1,    20,    48,    49,    30,    33,    18,
      25,    26,    27,    28,    29,     1,    14,    37,    41,     1,
      30,    36,     4,     3,     4,    48,    49,    25,    26,    27,
      28,    29,    14,     3,    14,     1,    16,     3,    37,    19,
      37,    21,    22,    25,    26,     1,    28,    29,    14,   112,
      37,   257,   102,     3,     4,   179,   289,     3,     4,   218,
      26,   110,    28,    29,    14,    38,    16,   135,    14,    19,
      16,    21,    22,    19,    -1,    21,    22,    50,    51,    52,
      53,    54,    55,    50,    51,    52,    53,    54,    55,   121,
     122,   123,   124,   125,   126,    42,    43,    44,    45,    46,
     206
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    24,    57,    58,    59,    58,     1,     3,    36,
     121,   122,     0,     1,     1,    27,    60,    61,     1,    36,
      40,    30,   121,    34,     1,     4,    62,    63,   123,    14,
      88,    25,    64,   122,   121,   122,    40,   121,    55,    16,
      19,    21,    22,    88,    89,    90,    91,    92,    93,    94,
     104,   106,   111,   115,   122,   123,    34,     1,    65,    66,
     122,    26,    76,     1,    35,   120,   123,    63,     1,    11,
      12,    13,    30,    41,    48,    49,    93,    94,    97,    98,
      99,   100,   102,   103,   105,   107,   122,    97,    97,   110,
      15,   121,    39,    32,    34,    33,     1,    17,   116,   117,
       1,    30,   121,    55,    77,    78,   122,    28,    29,    79,
      80,    81,    82,    35,   122,    97,   100,    99,    99,    34,
      33,    50,    51,    52,    53,    54,    55,    47,    48,    49,
      42,    43,    44,    45,    46,    30,    20,   112,    90,    97,
      95,    96,    97,   122,    17,   117,    19,    21,    22,    90,
      91,   113,   115,    18,   118,    31,    31,    97,   108,   109,
      66,     5,    10,    30,    67,    68,    69,    71,   122,   121,
      37,   120,     3,    84,   121,   122,     3,    83,   121,   122,
      81,     1,    60,   121,    31,     1,    31,   101,   122,    98,
      98,    98,    98,    98,    98,    99,    99,    99,   100,   100,
     100,   100,   100,    31,   108,    90,   120,    19,    21,    22,
      91,   115,   118,   110,     1,   117,    90,    31,   120,     1,
      32,    72,    74,    75,   122,    70,   122,    78,    67,    78,
     121,    26,    30,    85,   121,    85,    88,   121,    31,    96,
     110,     1,   117,    20,   114,   117,    18,   119,   109,    33,
       1,    68,    73,    97,   122,    23,    15,    36,    37,    31,
     120,     3,     3,    26,    31,    86,    87,    37,   121,   121,
     121,    20,   117,    18,   113,   119,   113,    33,    33,    38,
      67,    75,    67,   122,     1,     1,    37,     3,    31,   121,
      68,    97,    37,    37,    68,     1,    37,    87,   121,    68,
      68,    37,    68,    68
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
#line 95 "src/generated_parser.y"
    { doProgramDecl((yyvsp[(2) - (8)].id), (yyvsp[(4) - (8)].id), (yyvsp[(5) - (8)].id));
	  inDecl = 1; }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 98 "src/generated_parser.y"
    { doProgramDecl(NULL, NULL, NULL);
	  inDecl = 1; }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 101 "src/generated_parser.y"
    { doProgramDecl((yyvsp[(2) - (4)].id), NULL, NULL);
	  inDecl = 1; }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 104 "src/generated_parser.y"
    { doProgramDecl((yyvsp[(2) - (3)].id), NULL, NULL);
	  inDecl = 1; }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 110 "src/generated_parser.y"
    { exitDeclPart(); }
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

  case 45:

/* Line 1806 of yacc.c  */
#line 221 "src/generated_parser.y"
    { exitVarDeclPart(); }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 231 "src/generated_parser.y"
    { (yyval.symbol) = doVarDecl((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 233 "src/generated_parser.y"
    { (yyval.symbol) = doVarDecl((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 248 "src/generated_parser.y"
    { exitProcOrFuncDecl((yyvsp[(1) - (4)].symbol)); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 250 "src/generated_parser.y"
    { exitProcOrFuncDecl((yyvsp[(1) - (2)].symbol)); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 255 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(2) - (2)].symbol); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 257 "src/generated_parser.y"
    { (yyval.symbol) = (yyvsp[(2) - (2)].symbol); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 262 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl((yyvsp[(1) - (3)].id), (yyvsp[(2) - (3)].elemarray)); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 264 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl((yyvsp[(1) - (2)].id), NULL);
	  yyerrok; }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 267 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl(NULL, NULL); }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 272 "src/generated_parser.y"
    { (yyval.symbol) = enterFuncDecl((yyvsp[(1) - (5)].id), (yyvsp[(2) - (5)].elemarray), (yyvsp[(4) - (5)].symbol)); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 274 "src/generated_parser.y"
    { (yyval.symbol) = enterFuncDecl((yyvsp[(1) - (3)].id), (yyvsp[(2) - (3)].elemarray), NULL); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 276 "src/generated_parser.y"
    { (yyval.symbol) = enterFuncDecl((yyvsp[(2) - (2)].id), NULL, NULL);
	  yyerrok; }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 279 "src/generated_parser.y"
    { (yyval.symbol) = enterProcDecl(NULL, NULL); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 285 "src/generated_parser.y"
    { (yyval.elemarray) = (yyvsp[(2) - (3)].elemarray); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 287 "src/generated_parser.y"
    { (yyval.proxy) = NULL; }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 289 "src/generated_parser.y"
    { (yyval.proxy) = NULL;
	  yyerrok; }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 295 "src/generated_parser.y"
    { (yyval.elemarray) = createParmList((yyvsp[(1) - (1)].symbol)); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 297 "src/generated_parser.y"
    { (yyval.elemarray) = appendParmToParmList((yyvsp[(1) - (3)].elemarray), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 302 "src/generated_parser.y"
    { (yyval.symbol) = createNewParm((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].symbol)); }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 304 "src/generated_parser.y"
    { (yyval.symbol) = createNewVarParm((yyvsp[(2) - (4)].id), (yyvsp[(4) - (4)].symbol)); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 306 "src/generated_parser.y"
    { (yyval.symbol) = NULL;//$<proxy>$ = createNewParm($<id>1, $<symbol>3);
	  yyerrok; }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 309 "src/generated_parser.y"
    { (yyval.symbol) = NULL;//$<proxy>$ = createNewVarParm($<id>2, $<symbol>4);
	  yyerrok; }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 330 "src/generated_parser.y"
    { assignOp((yyvsp[(1) - (3)].symbol), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 337 "src/generated_parser.y"
    { (yyval.symbol) = variableAssignmentLookup((yyvsp[(1) - (1)].id)); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 339 "src/generated_parser.y"
    { (yyval.symbol) = recordFieldAssignmentLookup((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].id)); }
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 341 "src/generated_parser.y"
    { (yyval.symbol) = (Symbol *) (yyvsp[(1) - (2)].proxy); }
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 346 "src/generated_parser.y"
    { (yyval.proxy) = hashLookupToProxy((yyvsp[(1) - (1)].id)); }
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 348 "src/generated_parser.y"
    { (yyval.proxy) = hashLookupToProxy((yyvsp[(1) - (1)].id)); }
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 350 "src/generated_parser.y"
    { (yyval.proxy) = recordAccessToProxy((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].id) ); }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 352 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (2)].proxy); }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 357 "src/generated_parser.y"
    { (yyval.proxy) = arrayIndexAccess((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy));  }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 362 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy);  }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 364 "src/generated_parser.y"
    { (yyval.proxy) = concatArrayIndexList((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 369 "src/generated_parser.y"
    { (yyval.proxy) = createArrayIndexList((yyvsp[(1) - (1)].proxy)); }
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 374 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 376 "src/generated_parser.y"
    { (yyval.proxy) = eqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 378 "src/generated_parser.y"
    { (yyval.proxy) = notEqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 380 "src/generated_parser.y"
    { (yyval.proxy) = lessOrEqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 382 "src/generated_parser.y"
    { (yyval.proxy) = lessOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 384 "src/generated_parser.y"
    { (yyval.proxy) = gtOrEqOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 386 "src/generated_parser.y"
    { (yyval.proxy) = gtOp((yyvsp[(1) - (3)].proxy), (yyvsp[(3) - (3)].proxy)); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 391 "src/generated_parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 393 "src/generated_parser.y"
    { (yyval.node) = unaryPlusOp((yyvsp[(2) - (2)].node)); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 395 "src/generated_parser.y"
    { (yyval.node) = unaryMinusOp((yyvsp[(2) - (2)].node)); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 397 "src/generated_parser.y"
    { (yyval.node) = plusOp((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 399 "src/generated_parser.y"
    { (yyval.node) = minusOp((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 401 "src/generated_parser.y"
    { (yyval.node) = orOp((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 406 "src/generated_parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 408 "src/generated_parser.y"
    { (yyval.node) = multOp((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 410 "src/generated_parser.y"
    { (yyval.node) = divideOp((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 412 "src/generated_parser.y"
    { (yyval.node) = divOp((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 414 "src/generated_parser.y"
    { (yyval.node) = modOp((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 416 "src/generated_parser.y"
    { (yyval.node) = andOp((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 418 "src/generated_parser.y"
    { (yyval.node) = createLeafNode(NULL); }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 423 "src/generated_parser.y"
    { (yyval.node) = createLeafNode((yyvsp[(1) - (1)].proxy)); }
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 425 "src/generated_parser.y"
    { (yyval.node) = createLeafNode((yyvsp[(1) - (1)].proxy)); }
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 427 "src/generated_parser.y"
    { (yyval.node) = createLeafNode((yyvsp[(2) - (3)].proxy)); }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 429 "src/generated_parser.y"
    { (yyval.node) = createLeafNode((yyvsp[(1) - (1)].proxy)); }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 431 "src/generated_parser.y"
    { (yyval.node) = unaryNotOp((yyvsp[(2) - (2)].node)); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 441 "src/generated_parser.y"
    { (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 443 "src/generated_parser.y"
    { 
	    if (getStrlen((yyvsp[(1) - (1)].string)) <= 1) {
	        (yyval.proxy) = proxyCharLiteral((yyvsp[(1) - (1)].string)); 
	} else { (yyval.proxy) = proxyStringLiteral((yyvsp[(1) - (1)].string));} 
	}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 452 "src/generated_parser.y"
    { (yyval.proxy) = proxyIntLiteral((yyvsp[(1) - (1)].integer)); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 454 "src/generated_parser.y"
    { (yyval.proxy) = proxyRealLiteral((yyvsp[(1) - (1)].real)); }
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 459 "src/generated_parser.y"
    { /* Action is performed one level lower and nothing returned */ }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 461 "src/generated_parser.y"
    { /* TODO might want to explicitly use an empty arg list here */ 
	  procInvok((yyvsp[(1) - (3)].id), NULL); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 467 "src/generated_parser.y"
    { /* Action is performed one level lower */
	  (yyval.proxy) = (yyvsp[(1) - (1)].proxy); }
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 470 "src/generated_parser.y"
    { /* TODO might want to explicitly use an empty arg list here */
	  (yyval.proxy) = funcInvok((yyvsp[(1) - (3)].id), NULL); }
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 481 "src/generated_parser.y"
    { procInvok((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].elemarray)); }
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 488 "src/generated_parser.y"
    { (yyval.proxy) = funcInvok((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].elemarray)); }
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 494 "src/generated_parser.y"
    { (yyval.elemarray) = (yyvsp[(1) - (1)].elemarray); }
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 496 "src/generated_parser.y"
    { (yyval.elemarray) = concatArgLists((yyvsp[(1) - (3)].elemarray), (yyvsp[(3) - (3)].elemarray)); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 500 "src/generated_parser.y"
    { (yyval.elemarray) = createArgList((yyvsp[(1) - (1)].proxy)); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 505 "src/generated_parser.y"
    { whileLoopCondCheck((yyvsp[(1) - (1)].proxy)); }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 513 "src/generated_parser.y"
    { endWhileLoop(); }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 515 "src/generated_parser.y"
    { continueLoop(); }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 517 "src/generated_parser.y"
    { exitLoop(); }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 522 "src/generated_parser.y"
    { gotoLoopTop(); }
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 530 "src/generated_parser.y"
    { endWhileLoop(); }
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 532 "src/generated_parser.y"
    { continueLoop(); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 534 "src/generated_parser.y"
    { exitLoop(); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 539 "src/generated_parser.y"
    { gotoLoopTop(); }
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 544 "src/generated_parser.y"
    { ifPart((yyvsp[(2) - (2)].proxy)); }
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 549 "src/generated_parser.y"
    { thenStatPart(); }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 554 "src/generated_parser.y"
    { thenMatchedStatPart(); }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 559 "src/generated_parser.y"
    { elseStatPart(); }
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 564 "src/generated_parser.y"
    { elseStatPart(); }
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 569 "src/generated_parser.y"
    { yyerrok; }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 575 "src/generated_parser.y"
    { yyerrok; }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 581 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (3)].id); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 583 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 588 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (3)].id); }
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 590 "src/generated_parser.y"
    { (yyval.id) = (yyvsp[(1) - (1)].id); }
    break;



/* Line 1806 of yacc.c  */
#line 2702 "src/parser.tab.c"
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
#line 593 "src/generated_parser.y"


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

