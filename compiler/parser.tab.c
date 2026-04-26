
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

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

/* Line 189 of yacc.c  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex(void);
extern int yyline;
extern char *yytext;
extern FILE *yyin;

void yyerror(const char *s);

extern ASTNode *ast_root;

/* Helper to parse JavaType from token types */
static JavaType current_type;


/* Line 189 of yacc.c  */
#line 93 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
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
     INT_LITERAL = 258,
     DOUBLE_LIT = 259,
     IDENTIFIER = 260,
     STRING_LIT = 261,
     BOOL_LIT = 262,
     CHAR_LIT = 263,
     CLASS = 264,
     PUBLIC = 265,
     PRIVATE = 266,
     PROTECTED = 267,
     STATIC = 268,
     VOID = 269,
     INT = 270,
     DOUBLE = 271,
     FLOAT = 272,
     LONG = 273,
     CHAR = 274,
     BOOLEAN = 275,
     STRING_TYPE = 276,
     IF = 277,
     ELSE = 278,
     WHILE = 279,
     FOR = 280,
     RETURN = 281,
     NEW = 282,
     NULL_LIT = 283,
     SYSOUT_PRINTLN = 284,
     SYSOUT_PRINT = 285,
     PLUS = 286,
     MINUS = 287,
     TIMES = 288,
     DIVIDE = 289,
     MODULO = 290,
     EQ = 291,
     NEQ = 292,
     LT = 293,
     GT = 294,
     LTE = 295,
     GTE = 296,
     AND = 297,
     OR = 298,
     NOT = 299,
     BITAND = 300,
     BITOR = 301,
     BITXOR = 302,
     BITNOT = 303,
     SHL = 304,
     SHR = 305,
     INCREMENT = 306,
     DECREMENT = 307,
     PLUS_ASSIGN = 308,
     MINUS_ASSIGN = 309,
     TIMES_ASSIGN = 310,
     DIVIDE_ASSIGN = 311,
     ASSIGN = 312,
     LPAREN = 313,
     RPAREN = 314,
     LBRACE = 315,
     RBRACE = 316,
     LBRACKET = 317,
     RBRACKET = 318,
     COMMA = 319,
     SEMICOLON = 320,
     DOT = 321,
     UMINUS = 322
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 20 "parser.y"

    double dval;
    char *sval;
    int bval;
    int ival;
    char cval;
    struct ASTNode *node;
    int jtype;
    int accmod;



/* Line 214 of yacc.c  */
#line 209 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 221 "parser.tab.c"

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
# if YYENABLE_NLS
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  73
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1054

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNRULES -- Number of states.  */
#define YYNSTATES  232

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   322

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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    12,    19,    20,    22,
      24,    26,    28,    29,    31,    33,    34,    37,    39,    41,
      52,    60,    66,    68,    70,    72,    74,    76,    78,    80,
      82,    86,    90,    94,    95,    97,    99,   103,   106,   108,
     111,   113,   115,   117,   119,   121,   123,   125,   127,   133,
     137,   142,   147,   152,   157,   162,   170,   176,   184,   192,
     196,   199,   205,   215,   220,   224,   227,   230,   233,   237,
     241,   245,   248,   254,   259,   265,   268,   269,   271,   273,
     277,   281,   285,   289,   293,   297,   301,   305,   309,   313,
     317,   321,   325,   329,   333,   337,   341,   345,   349,   352,
     355,   358,   360,   362,   365,   368,   370,   372,   374,   376,
     378,   383,   390,   395,   401,   406,   408
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      69,     0,    -1,    70,    -1,    84,    -1,    71,    -1,    70,
      71,    -1,    72,     9,     5,    60,    75,    61,    -1,    -1,
      73,    -1,    10,    -1,    11,    -1,    12,    -1,    -1,    13,
      -1,    76,    -1,    -1,    76,    77,    -1,    78,    -1,    79,
      -1,    72,    74,    80,     5,    58,    81,    59,    60,    84,
      61,    -1,    72,    74,    80,     5,    57,    99,    65,    -1,
      72,    74,    80,     5,    65,    -1,    15,    -1,    16,    -1,
      17,    -1,    18,    -1,    19,    -1,    20,    -1,    21,    -1,
      14,    -1,    15,    62,    63,    -1,    16,    62,    63,    -1,
      21,    62,    63,    -1,    -1,    82,    -1,    83,    -1,    82,
      64,    83,    -1,    80,     5,    -1,    85,    -1,    84,    85,
      -1,    86,    -1,    87,    -1,    88,    -1,    90,    -1,    91,
      -1,    94,    -1,    95,    -1,    96,    -1,    80,     5,    57,
      99,    65,    -1,    80,     5,    65,    -1,     5,    57,    99,
      65,    -1,     5,    53,    99,    65,    -1,     5,    54,    99,
      65,    -1,     5,    55,    99,    65,    -1,     5,    56,    99,
      65,    -1,     5,    62,    99,    63,    57,    99,    65,    -1,
      22,    58,    99,    59,    89,    -1,    22,    58,    99,    59,
      89,    23,    89,    -1,    22,    58,    99,    59,    89,    23,
      88,    -1,    60,    84,    61,    -1,    60,    61,    -1,    24,
      58,    99,    59,    89,    -1,    25,    58,    92,    65,    99,
      65,    93,    59,    89,    -1,    80,     5,    57,    99,    -1,
       5,    57,    99,    -1,     5,    51,    -1,     5,    52,    -1,
      51,     5,    -1,     5,    57,    99,    -1,     5,    53,    99,
      -1,    26,    99,    65,    -1,    26,    65,    -1,    29,    58,
      99,    59,    65,    -1,    29,    58,    59,    65,    -1,    30,
      58,    99,    59,    65,    -1,    99,    65,    -1,    -1,    98,
      -1,    99,    -1,    98,    64,    99,    -1,    99,    31,    99,
      -1,    99,    32,    99,    -1,    99,    33,    99,    -1,    99,
      34,    99,    -1,    99,    35,    99,    -1,    99,    36,    99,
      -1,    99,    37,    99,    -1,    99,    38,    99,    -1,    99,
      39,    99,    -1,    99,    40,    99,    -1,    99,    41,    99,
      -1,    99,    42,    99,    -1,    99,    43,    99,    -1,    99,
      45,    99,    -1,    99,    46,    99,    -1,    99,    47,    99,
      -1,    99,    49,    99,    -1,    99,    50,    99,    -1,    44,
      99,    -1,    48,    99,    -1,    32,    99,    -1,   100,    -1,
     101,    -1,   100,    51,    -1,   100,    52,    -1,     3,    -1,
       4,    -1,     6,    -1,     8,    -1,     7,    -1,     5,    58,
      97,    59,    -1,     5,    66,     5,    58,    97,    59,    -1,
       5,    62,    99,    63,    -1,    27,    80,    62,    99,    63,
      -1,    58,    80,    59,   101,    -1,     5,    -1,    58,    99,
      59,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    82,    82,    83,    87,    91,    98,   104,   105,   109,
     110,   111,   115,   116,   120,   124,   127,   134,   135,   139,
     145,   151,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   174,   175,   179,   183,   190,   196,   200,
     207,   208,   209,   210,   211,   212,   213,   214,   218,   221,
     227,   230,   235,   240,   245,   250,   258,   261,   264,   270,
     271,   275,   281,   287,   290,   296,   302,   308,   314,   317,
     325,   328,   334,   337,   340,   346,   352,   353,   357,   361,
     368,   369,   370,   371,   372,   373,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   393,   394,   395,   399,   400,   401,   402,   403,
     404,   407,   410,   413,   416,   419,   420
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_LITERAL", "DOUBLE_LIT",
  "IDENTIFIER", "STRING_LIT", "BOOL_LIT", "CHAR_LIT", "CLASS", "PUBLIC",
  "PRIVATE", "PROTECTED", "STATIC", "VOID", "INT", "DOUBLE", "FLOAT",
  "LONG", "CHAR", "BOOLEAN", "STRING_TYPE", "IF", "ELSE", "WHILE", "FOR",
  "RETURN", "NEW", "NULL_LIT", "SYSOUT_PRINTLN", "SYSOUT_PRINT", "PLUS",
  "MINUS", "TIMES", "DIVIDE", "MODULO", "EQ", "NEQ", "LT", "GT", "LTE",
  "GTE", "AND", "OR", "NOT", "BITAND", "BITOR", "BITXOR", "BITNOT", "SHL",
  "SHR", "INCREMENT", "DECREMENT", "PLUS_ASSIGN", "MINUS_ASSIGN",
  "TIMES_ASSIGN", "DIVIDE_ASSIGN", "ASSIGN", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "LBRACKET", "RBRACKET", "COMMA", "SEMICOLON", "DOT", "UMINUS",
  "$accept", "program", "class_list", "class_decl", "opt_access_mod",
  "access_mod", "opt_static", "class_body", "class_member_list",
  "class_member", "method_decl", "field_decl", "type_spec",
  "opt_param_list", "param_list", "typed_param", "statement_list",
  "statement", "var_decl_stmt", "assign_stmt", "if_stmt", "block",
  "while_stmt", "for_stmt", "for_init", "for_update", "return_stmt",
  "print_stmt", "expr_stmt", "opt_arg_list", "arg_list", "expression",
  "postfix_expr", "primary", 0
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    68,    69,    69,    70,    70,    71,    72,    72,    73,
      73,    73,    74,    74,    75,    76,    76,    77,    77,    78,
      79,    79,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    81,    81,    82,    82,    83,    84,    84,
      85,    85,    85,    85,    85,    85,    85,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    88,    88,    88,    89,
      89,    90,    91,    92,    92,    93,    93,    93,    93,    93,
      94,    94,    95,    95,    95,    96,    97,    97,    98,    98,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   100,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     6,     0,     1,     1,
       1,     1,     0,     1,     1,     0,     2,     1,     1,    10,
       7,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     0,     1,     1,     3,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     3,
       4,     4,     4,     4,     4,     7,     5,     7,     7,     3,
       2,     5,     9,     4,     3,     2,     2,     2,     3,     3,
       3,     2,     5,     4,     5,     2,     0,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       4,     6,     4,     5,     4,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       7,   105,   106,   115,   107,   109,   108,     9,    10,    11,
      29,    22,    23,    24,    25,    26,    27,    28,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     4,     0,     8,     0,     3,    38,    40,    41,    42,
      43,    44,    45,    46,    47,     0,   101,   102,     0,     0,
       0,     0,     0,    76,     0,     0,     0,     0,     0,     0,
       0,     0,   115,    71,     0,     0,     0,     0,   100,    98,
      99,     0,     0,     1,     5,     0,     0,    39,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    75,   103,   104,     0,
       0,     0,     0,     0,     0,    77,    78,     0,     0,    30,
      31,    32,     0,     0,     0,     0,     0,     0,    70,     0,
       0,     0,     0,     0,   116,     0,     0,    49,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    51,    52,    53,    54,
      50,   110,     0,   112,    76,     0,     0,     0,     0,     0,
       0,     0,    73,     0,     0,   114,    15,     0,    79,     0,
       0,     0,    56,    61,    64,     0,     0,   112,   113,    72,
      74,     0,     7,    48,     0,   111,    60,     0,     0,    63,
       0,     6,    12,    16,    17,    18,    55,    59,    58,    57,
       0,     0,     0,    13,     0,    65,    66,     0,     0,    67,
       0,     0,    69,    68,    62,     0,     0,    33,    21,     0,
       0,     0,    34,    35,    20,    37,     0,     0,     0,    36,
       0,    19
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    29,    30,    31,    32,    33,   204,   181,   182,   193,
     194,   195,    34,   221,   222,   223,    35,    36,    37,    38,
      39,   172,    40,    41,   116,   202,    42,    43,    44,   104,
     105,    45,    46,    47
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -170
static const yytype_int16 yypact[] =
{
     351,  -170,  -170,   176,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,    38,    41,  -170,  -170,  -170,  -170,    50,   -14,    62,
      63,    75,    -3,    71,    72,   451,   451,   451,   421,    40,
     115,  -170,   122,  -170,   130,   386,  -170,  -170,  -170,  -170,
    -170,  -170,  -170,  -170,  -170,   127,    34,  -170,   451,   451,
     451,   451,   451,   451,   451,   132,    81,    82,    83,   451,
     451,   456,    47,  -170,   479,    76,    84,   451,  -170,  -170,
    -170,    88,   788,  -170,  -170,   144,    53,  -170,   451,   451,
     451,   451,   451,   451,   451,   451,   451,   451,   451,   451,
     451,   451,   451,   451,   451,   451,  -170,  -170,  -170,   500,
     521,   542,   563,   584,    91,    92,   933,   689,    94,  -170,
    -170,  -170,   817,   846,    97,   150,   106,   451,  -170,   451,
     110,   875,   904,    90,  -170,   118,   451,  -170,    23,    23,
    -170,  -170,  -170,   993,   993,  1004,  1004,  1004,  1004,   973,
     953,   -12,   294,   453,   152,   152,  -170,  -170,  -170,  -170,
    -170,  -170,   451,   123,   451,   119,   119,   451,   124,   451,
     722,   755,  -170,   126,   128,  -170,  -170,   605,   933,   451,
     129,   196,   171,  -170,   933,   451,   626,  -170,  -170,  -170,
    -170,   136,    43,  -170,   647,  -170,  -170,   244,   -17,   933,
      -1,  -170,   193,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
      -6,   202,   149,  -170,    -3,  -170,  -170,   451,   451,  -170,
     119,   204,   933,   933,  -170,    57,   451,    -3,  -170,   668,
     214,   165,   163,  -170,  -170,  -170,   175,    -3,   386,  -170,
     292,  -170
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -170,  -170,  -170,   206,    55,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,   -22,  -170,  -170,    12,  -169,   -34,  -170,  -170,
      58,  -104,  -170,  -170,  -170,  -170,  -170,  -170,  -170,    87,
    -170,   -18,  -170,   120
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -15
static const yytype_int16 yytable[] =
{
      65,    77,   187,    64,   200,    18,    71,    68,    69,    70,
      72,    10,    11,    12,    13,    14,    15,    16,    17,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      99,   100,   101,   102,   103,   106,   107,    94,    95,   115,
      73,   112,   113,   171,    59,   205,   206,   207,   121,   122,
     201,   208,   173,     7,     8,     9,    80,    81,    82,   230,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,     1,     2,
      62,     4,     5,     6,   199,    97,    98,     1,     2,    62,
       4,     5,     6,     1,     2,    62,     4,     5,     6,   160,
      56,   161,    22,    57,   -14,    53,   214,    25,   167,   117,
     126,    22,    58,    55,   216,   217,    25,    22,   127,    26,
      60,    61,   218,    27,    -7,     7,     8,     9,    26,    66,
      67,    75,    27,    28,   168,    76,   106,   108,   119,   174,
      63,   176,    28,   120,   109,   110,   111,   123,    28,   125,
     151,   184,   154,    77,   157,   158,   152,   189,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   159,    91,    92,    93,   162,    94,    95,   166,   171,
     169,   175,   211,    78,    79,    80,    81,    82,   185,   212,
     213,   179,    96,   180,   188,   220,    77,   191,   219,     1,
       2,     3,     4,     5,     6,   220,   203,   209,   210,   215,
      10,    11,    12,    13,    14,    15,    16,    17,    18,   225,
      19,    20,    21,    22,   226,    23,    24,   227,    25,    48,
      49,    50,    51,    52,    53,   228,    74,   192,    54,   229,
      26,   170,    55,   165,    27,     0,   198,     1,     2,     3,
       4,     5,     6,     0,    28,     0,     0,   186,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     0,    19,    20,
      21,    22,     0,    23,    24,     0,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,     0,
       0,     0,    27,     0,     0,     1,     2,     3,     4,     5,
       6,     0,    28,     0,     0,   197,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     0,    19,    20,    21,    22,
       0,    23,    24,     0,    25,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    26,     0,     0,    91,
      27,    93,     0,    94,    95,     0,     0,     0,     0,     0,
      28,     0,     0,   231,     1,     2,     3,     4,     5,     6,
       0,     7,     8,     9,     0,    10,    11,    12,    13,    14,
      15,    16,    17,    18,     0,    19,    20,    21,    22,     0,
      23,    24,     0,    25,     0,     0,     0,     0,     0,     1,
       2,     3,     4,     5,     6,    26,     0,     0,     0,    27,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    28,
      19,    20,    21,    22,     0,    23,    24,     0,    25,     0,
       0,     0,     0,     0,     1,     2,    62,     4,     5,     6,
      26,     0,     0,     0,    27,    10,    11,    12,    13,    14,
      15,    16,    17,     0,    28,     0,     0,     0,    22,     0,
       0,     0,     0,    25,     1,     2,    62,     4,     5,     6,
       0,   114,     0,     0,     0,    26,     0,     0,     0,    27,
      10,    11,    12,    13,    14,    15,    16,    17,    22,    28,
       0,     0,     0,    25,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    26,     0,     0,    91,    27,
       0,     0,    94,    95,     0,     0,     0,     0,     0,    28,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,     0,    91,    92,    93,     0,    94,    95,
       0,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,   118,    91,    92,    93,     0,    94,
      95,     0,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,   146,    91,    92,    93,     0,
      94,    95,     0,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,   147,    91,    92,    93,
       0,    94,    95,     0,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,   148,    91,    92,
      93,     0,    94,    95,     0,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,   149,    91,
      92,    93,     0,    94,    95,     0,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,   150,
      91,    92,    93,     0,    94,    95,     0,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
     183,    91,    92,    93,     0,    94,    95,     0,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,   190,    91,    92,    93,     0,    94,    95,     0,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,   196,    91,    92,    93,     0,    94,    95,     0,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,   224,    91,    92,    93,     0,    94,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   153,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,     0,    91,    92,    93,
       0,    94,    95,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   177,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     0,
      91,    92,    93,     0,    94,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   178,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,     0,    91,    92,    93,     0,    94,    95,     0,
       0,     0,     0,     0,     0,     0,     0,   124,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,     0,    91,    92,    93,     0,    94,    95,     0,     0,
       0,     0,     0,     0,     0,     0,   155,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
       0,    91,    92,    93,     0,    94,    95,     0,     0,     0,
       0,     0,     0,     0,     0,   156,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,     0,
      91,    92,    93,     0,    94,    95,     0,     0,     0,     0,
       0,     0,     0,     0,   163,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,     0,    91,
      92,    93,     0,    94,    95,     0,     0,     0,     0,     0,
       0,     0,     0,   164,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,     0,    91,    92,
      93,     0,    94,    95,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,     0,     0,    91,    92,
      93,     0,    94,    95,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,     0,     0,     0,    91,    92,
      93,     0,    94,    95,    78,    79,    80,    81,    82,     0,
       0,    85,    86,    87,    88,    78,    79,    80,    81,    82,
       0,     0,    94,    95,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,    95
};

static const yytype_int16 yycheck[] =
{
      22,    35,   171,    21,     5,    22,    28,    25,    26,    27,
      28,    14,    15,    16,    17,    18,    19,    20,    21,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      48,    49,    50,    51,    52,    53,    54,    49,    50,    61,
       0,    59,    60,    60,    58,    51,    52,    53,    66,    67,
      51,    57,   156,    10,    11,    12,    33,    34,    35,   228,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,     3,     4,
       5,     6,     7,     8,   188,    51,    52,     3,     4,     5,
       6,     7,     8,     3,     4,     5,     6,     7,     8,   117,
      62,   119,    27,    62,    61,    58,   210,    32,   126,    62,
      57,    27,    62,    66,    57,    58,    32,    27,    65,    44,
      58,    58,    65,    48,     9,    10,    11,    12,    44,    58,
      58,     9,    48,    58,   152,     5,   154,     5,    62,   157,
      65,   159,    58,    59,    63,    63,    63,    59,    58,     5,
      59,   169,    58,   187,    57,     5,    64,   175,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    65,    45,    46,    47,    65,    49,    50,    60,    60,
      57,    57,   204,    31,    32,    33,    34,    35,    59,   207,
     208,    65,    65,    65,    23,   217,   230,    61,   216,     3,
       4,     5,     6,     7,     8,   227,    13,     5,    59,     5,
      14,    15,    16,    17,    18,    19,    20,    21,    22,     5,
      24,    25,    26,    27,    59,    29,    30,    64,    32,    53,
      54,    55,    56,    57,    58,    60,    30,   182,    62,   227,
      44,   154,    66,   123,    48,    -1,   188,     3,     4,     5,
       6,     7,     8,    -1,    58,    -1,    -1,    61,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    -1,    24,    25,
      26,    27,    -1,    29,    30,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    48,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    58,    -1,    -1,    61,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    25,    26,    27,
      -1,    29,    30,    -1,    32,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    44,    -1,    -1,    45,
      48,    47,    -1,    49,    50,    -1,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    61,     3,     4,     5,     6,     7,     8,
      -1,    10,    11,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    -1,    24,    25,    26,    27,    -1,
      29,    30,    -1,    32,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,    44,    -1,    -1,    -1,    48,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    58,
      24,    25,    26,    27,    -1,    29,    30,    -1,    32,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
      44,    -1,    -1,    -1,    48,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    58,    -1,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    32,     3,     4,     5,     6,     7,     8,
      -1,     5,    -1,    -1,    -1,    44,    -1,    -1,    -1,    48,
      14,    15,    16,    17,    18,    19,    20,    21,    27,    58,
      -1,    -1,    -1,    32,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    44,    -1,    -1,    45,    48,
      -1,    -1,    49,    50,    -1,    -1,    -1,    -1,    -1,    58,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    -1,    45,    46,    47,    -1,    49,    50,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    65,    45,    46,    47,    -1,    49,
      50,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    65,    45,    46,    47,    -1,
      49,    50,    -1,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    65,    45,    46,    47,
      -1,    49,    50,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    65,    45,    46,
      47,    -1,    49,    50,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    65,    45,
      46,    47,    -1,    49,    50,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    65,
      45,    46,    47,    -1,    49,    50,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      65,    45,    46,    47,    -1,    49,    50,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    65,    45,    46,    47,    -1,    49,    50,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    65,    45,    46,    47,    -1,    49,    50,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    65,    45,    46,    47,    -1,    49,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    -1,    45,    46,    47,
      -1,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    -1,    45,    46,    47,    -1,    49,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    45,    46,    47,    -1,    49,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    45,    46,    47,    -1,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    -1,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    -1,    45,
      46,    47,    -1,    49,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    -1,    45,    46,
      47,    -1,    49,    50,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    -1,    -1,    45,    46,
      47,    -1,    49,    50,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    45,    46,
      47,    -1,    49,    50,    31,    32,    33,    34,    35,    -1,
      -1,    38,    39,    40,    41,    31,    32,    33,    34,    35,
      -1,    -1,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    50
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    10,    11,    12,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    24,
      25,    26,    27,    29,    30,    32,    44,    48,    58,    69,
      70,    71,    72,    73,    80,    84,    85,    86,    87,    88,
      90,    91,    94,    95,    96,    99,   100,   101,    53,    54,
      55,    56,    57,    58,    62,    66,    62,    62,    62,    58,
      58,    58,     5,    65,    99,    80,    58,    58,    99,    99,
      99,    80,    99,     0,    71,     9,     5,    85,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    45,    46,    47,    49,    50,    65,    51,    52,    99,
      99,    99,    99,    99,    97,    98,    99,    99,     5,    63,
      63,    63,    99,    99,     5,    80,    92,    62,    65,    62,
      59,    99,    99,    59,    59,     5,    57,    65,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    65,    65,    65,    65,
      65,    59,    64,    63,    58,    59,    59,    57,     5,    65,
      99,    99,    65,    59,    59,   101,    60,    99,    99,    57,
      97,    60,    89,    89,    99,    57,    99,    63,    63,    65,
      65,    75,    76,    65,    99,    59,    61,    84,    23,    99,
      65,    61,    72,    77,    78,    79,    65,    61,    88,    89,
       5,    51,    93,    13,    74,    51,    52,    53,    57,     5,
      59,    80,    99,    99,    89,     5,    57,    58,    65,    99,
      80,    81,    82,    83,    65,     5,    59,    64,    60,    83,
      84,    61
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
        case 2:

/* Line 1455 of yacc.c  */
#line 82 "parser.y"
    { ast_root = (yyvsp[(1) - (1)].node); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 83 "parser.y"
    { ast_root = (yyvsp[(1) - (1)].node); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 87 "parser.y"
    {
        (yyval.node) = ast_new_stmt_list();
        ast_add_item((yyval.node), (yyvsp[(1) - (1)].node));
    ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 91 "parser.y"
    {
        ast_add_item((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
        (yyval.node) = (yyvsp[(1) - (2)].node);
    ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 98 "parser.y"
    {
        (yyval.node) = ast_new_class_decl((yyvsp[(3) - (6)].sval), (AccessMod)(yyvsp[(1) - (6)].accmod), (yyvsp[(5) - (6)].node), yyline);
    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 104 "parser.y"
    { (yyval.accmod) = ACC_DEFAULT; ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 105 "parser.y"
    { (yyval.accmod) = (yyvsp[(1) - (1)].accmod); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 109 "parser.y"
    { (yyval.accmod) = ACC_PUBLIC; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 110 "parser.y"
    { (yyval.accmod) = ACC_PRIVATE; ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 111 "parser.y"
    { (yyval.accmod) = ACC_PROTECTED; ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    { (yyval.bval) = 0; ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 116 "parser.y"
    { (yyval.bval) = 1; ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 120 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 124 "parser.y"
    {
        (yyval.node) = ast_new_stmt_list();
    ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 127 "parser.y"
    {
        ast_add_item((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
        (yyval.node) = (yyvsp[(1) - (2)].node);
    ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 134 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 135 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 139 "parser.y"
    {
        (yyval.node) = ast_new_method_decl((yyvsp[(4) - (10)].sval), (JavaType)(yyvsp[(3) - (10)].jtype), (AccessMod)(yyvsp[(1) - (10)].accmod), (yyvsp[(2) - (10)].bval), (yyvsp[(6) - (10)].node), (yyvsp[(9) - (10)].node), yyline);
    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 145 "parser.y"
    {
        ASTNode *n = ast_new_var_decl((yyvsp[(4) - (7)].sval), (JavaType)(yyvsp[(3) - (7)].jtype), (yyvsp[(6) - (7)].node), yyline);
        n->access = (AccessMod)(yyvsp[(1) - (7)].accmod);
        n->is_static = (yyvsp[(2) - (7)].bval);
        (yyval.node) = n;
    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 151 "parser.y"
    {
        ASTNode *n = ast_new_var_decl((yyvsp[(4) - (5)].sval), (JavaType)(yyvsp[(3) - (5)].jtype), NULL, yyline);
        n->access = (AccessMod)(yyvsp[(1) - (5)].accmod);
        n->is_static = (yyvsp[(2) - (5)].bval);
        (yyval.node) = n;
    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 160 "parser.y"
    { (yyval.jtype) = JTYPE_INT; ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 161 "parser.y"
    { (yyval.jtype) = JTYPE_DOUBLE; ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 162 "parser.y"
    { (yyval.jtype) = JTYPE_FLOAT; ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 163 "parser.y"
    { (yyval.jtype) = JTYPE_LONG; ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    { (yyval.jtype) = JTYPE_CHAR; ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 165 "parser.y"
    { (yyval.jtype) = JTYPE_BOOLEAN; ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 166 "parser.y"
    { (yyval.jtype) = JTYPE_STRING; ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 167 "parser.y"
    { (yyval.jtype) = JTYPE_VOID; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 168 "parser.y"
    { (yyval.jtype) = JTYPE_INT_ARRAY; ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 169 "parser.y"
    { (yyval.jtype) = JTYPE_DOUBLE_ARRAY; ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 170 "parser.y"
    { (yyval.jtype) = JTYPE_STRING_ARRAY; ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 174 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 175 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 179 "parser.y"
    {
        (yyval.node) = ast_new_stmt_list();
        ast_add_item((yyval.node), (yyvsp[(1) - (1)].node));
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 183 "parser.y"
    {
        ast_add_item((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
        (yyval.node) = (yyvsp[(1) - (3)].node);
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 190 "parser.y"
    {
        (yyval.node) = ast_new_typed_param((yyvsp[(2) - (2)].sval), (JavaType)(yyvsp[(1) - (2)].jtype), yyline);
    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 196 "parser.y"
    {
        (yyval.node) = ast_new_stmt_list();
        ast_add_item((yyval.node), (yyvsp[(1) - (1)].node));
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 200 "parser.y"
    {
        ast_add_item((yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
        (yyval.node) = (yyvsp[(1) - (2)].node);
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 207 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 208 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 209 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 211 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 212 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 213 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 214 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 218 "parser.y"
    {
        (yyval.node) = ast_new_var_decl((yyvsp[(2) - (5)].sval), (JavaType)(yyvsp[(1) - (5)].jtype), (yyvsp[(4) - (5)].node), yyline);
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 221 "parser.y"
    {
        (yyval.node) = ast_new_var_decl((yyvsp[(2) - (3)].sval), (JavaType)(yyvsp[(1) - (3)].jtype), NULL, yyline);
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 227 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].node), yyline);
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 230 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(1) - (4)].sval),
            ast_new_binop(OP_ADD, ast_new_ident(strdup((yyvsp[(1) - (4)].sval)), yyline), (yyvsp[(3) - (4)].node), yyline),
            yyline);
    ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 235 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(1) - (4)].sval),
            ast_new_binop(OP_SUB, ast_new_ident(strdup((yyvsp[(1) - (4)].sval)), yyline), (yyvsp[(3) - (4)].node), yyline),
            yyline);
    ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 240 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(1) - (4)].sval),
            ast_new_binop(OP_MUL, ast_new_ident(strdup((yyvsp[(1) - (4)].sval)), yyline), (yyvsp[(3) - (4)].node), yyline),
            yyline);
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 245 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(1) - (4)].sval),
            ast_new_binop(OP_DIV, ast_new_ident(strdup((yyvsp[(1) - (4)].sval)), yyline), (yyvsp[(3) - (4)].node), yyline),
            yyline);
    ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 250 "parser.y"
    {
        ASTNode *access = ast_new_array_access((yyvsp[(1) - (7)].sval), (yyvsp[(3) - (7)].node), yyline);
        access->right = (yyvsp[(6) - (7)].node);
        (yyval.node) = ast_new_expr_stmt(access, yyline);
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 258 "parser.y"
    {
        (yyval.node) = ast_new_if((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), NULL, yyline);
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 261 "parser.y"
    {
        (yyval.node) = ast_new_if((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node), yyline);
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 264 "parser.y"
    {
        (yyval.node) = ast_new_if((yyvsp[(3) - (7)].node), (yyvsp[(5) - (7)].node), (yyvsp[(7) - (7)].node), yyline);
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 270 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    { (yyval.node) = ast_new_stmt_list(); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 275 "parser.y"
    {
        (yyval.node) = ast_new_while((yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node), yyline);
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 281 "parser.y"
    {
        (yyval.node) = ast_new_for((yyvsp[(3) - (9)].node), (yyvsp[(5) - (9)].node), (yyvsp[(7) - (9)].node), (yyvsp[(9) - (9)].node), yyline);
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 287 "parser.y"
    {
        (yyval.node) = ast_new_var_decl((yyvsp[(2) - (4)].sval), (JavaType)(yyvsp[(1) - (4)].jtype), (yyvsp[(4) - (4)].node), yyline);
    ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 290 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].node), yyline);
    ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 296 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(1) - (2)].sval),
            ast_new_binop(OP_ADD, ast_new_ident(strdup((yyvsp[(1) - (2)].sval)), yyline),
                ast_new_int_lit(1, yyline), yyline),
            yyline);
    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 302 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(1) - (2)].sval),
            ast_new_binop(OP_SUB, ast_new_ident(strdup((yyvsp[(1) - (2)].sval)), yyline),
                ast_new_int_lit(1, yyline), yyline),
            yyline);
    ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 308 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(2) - (2)].sval),
            ast_new_binop(OP_ADD, ast_new_ident(strdup((yyvsp[(2) - (2)].sval)), yyline),
                ast_new_int_lit(1, yyline), yyline),
            yyline);
    ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 314 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].node), yyline);
    ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 317 "parser.y"
    {
        (yyval.node) = ast_new_assign((yyvsp[(1) - (3)].sval),
            ast_new_binop(OP_ADD, ast_new_ident(strdup((yyvsp[(1) - (3)].sval)), yyline), (yyvsp[(3) - (3)].node), yyline),
            yyline);
    ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 325 "parser.y"
    {
        (yyval.node) = ast_new_return((yyvsp[(2) - (3)].node), yyline);
    ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 328 "parser.y"
    {
        (yyval.node) = ast_new_return(NULL, yyline);
    ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 334 "parser.y"
    {
        (yyval.node) = ast_new_print((yyvsp[(3) - (5)].node), yyline);
    ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 337 "parser.y"
    {
        (yyval.node) = ast_new_print(ast_new_str_lit(strdup("\"\""), yyline), yyline);
    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 340 "parser.y"
    {
        (yyval.node) = ast_new_print((yyvsp[(3) - (5)].node), yyline);
    ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 346 "parser.y"
    {
        (yyval.node) = ast_new_expr_stmt((yyvsp[(1) - (2)].node), yyline);
    ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 352 "parser.y"
    { (yyval.node) = NULL; ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 353 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 357 "parser.y"
    {
        (yyval.node) = ast_new_stmt_list();
        ast_add_item((yyval.node), (yyvsp[(1) - (1)].node));
    ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 361 "parser.y"
    {
        ast_add_item((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
        (yyval.node) = (yyvsp[(1) - (3)].node);
    ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 368 "parser.y"
    { (yyval.node) = ast_new_binop(OP_ADD, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 369 "parser.y"
    { (yyval.node) = ast_new_binop(OP_SUB, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 370 "parser.y"
    { (yyval.node) = ast_new_binop(OP_MUL, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 371 "parser.y"
    { (yyval.node) = ast_new_binop(OP_DIV, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 372 "parser.y"
    { (yyval.node) = ast_new_binop(OP_MOD, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 373 "parser.y"
    { (yyval.node) = ast_new_binop(OP_EQ, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 374 "parser.y"
    { (yyval.node) = ast_new_binop(OP_NEQ, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 375 "parser.y"
    { (yyval.node) = ast_new_binop(OP_LT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 376 "parser.y"
    { (yyval.node) = ast_new_binop(OP_GT, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 377 "parser.y"
    { (yyval.node) = ast_new_binop(OP_LTE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 378 "parser.y"
    { (yyval.node) = ast_new_binop(OP_GTE, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 379 "parser.y"
    { (yyval.node) = ast_new_binop(OP_AND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 380 "parser.y"
    { (yyval.node) = ast_new_binop(OP_OR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 381 "parser.y"
    { (yyval.node) = ast_new_binop(OP_BITAND, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 382 "parser.y"
    { (yyval.node) = ast_new_binop(OP_BITOR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 383 "parser.y"
    { (yyval.node) = ast_new_binop(OP_BITXOR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 384 "parser.y"
    { (yyval.node) = ast_new_binop(OP_SHL, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 385 "parser.y"
    { (yyval.node) = ast_new_binop(OP_SHR, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), yyline); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 386 "parser.y"
    { (yyval.node) = ast_new_unaryop(OP_NOT, (yyvsp[(2) - (2)].node), yyline); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 387 "parser.y"
    { (yyval.node) = ast_new_unaryop(OP_BITNOT, (yyvsp[(2) - (2)].node), yyline); ;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 388 "parser.y"
    { (yyval.node) = ast_new_unaryop(OP_NEG, (yyvsp[(2) - (2)].node), yyline); ;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 389 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 393 "parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 394 "parser.y"
    { (yyval.node) = ast_new_unaryop(OP_INCREMENT, (yyvsp[(1) - (2)].node), yyline); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 395 "parser.y"
    { (yyval.node) = ast_new_unaryop(OP_DECREMENT, (yyvsp[(1) - (2)].node), yyline); ;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 399 "parser.y"
    { (yyval.node) = ast_new_int_lit((yyvsp[(1) - (1)].ival), yyline); ;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 400 "parser.y"
    { (yyval.node) = ast_new_double_lit((yyvsp[(1) - (1)].dval), yyline); ;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 401 "parser.y"
    { (yyval.node) = ast_new_str_lit((yyvsp[(1) - (1)].sval), yyline); ;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 402 "parser.y"
    { (yyval.node) = ast_new_char_lit((yyvsp[(1) - (1)].cval), yyline); ;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 403 "parser.y"
    { (yyval.node) = ast_new_bool_lit((yyvsp[(1) - (1)].bval), yyline); ;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 404 "parser.y"
    {
        (yyval.node) = ast_new_func_call((yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].node), yyline);
    ;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 407 "parser.y"
    {
        (yyval.node) = ast_new_method_call((yyvsp[(1) - (6)].sval), (yyvsp[(3) - (6)].sval), (yyvsp[(5) - (6)].node), yyline);
    ;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 410 "parser.y"
    {
        (yyval.node) = ast_new_array_access((yyvsp[(1) - (4)].sval), (yyvsp[(3) - (4)].node), yyline);
    ;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 413 "parser.y"
    {
        (yyval.node) = ast_new_new_array((JavaType)(yyvsp[(2) - (5)].jtype), (yyvsp[(4) - (5)].node), yyline);
    ;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 416 "parser.y"
    {
        (yyval.node) = ast_new_cast((JavaType)(yyvsp[(2) - (4)].jtype), (yyvsp[(4) - (4)].node), yyline);
    ;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 419 "parser.y"
    { (yyval.node) = ast_new_ident((yyvsp[(1) - (1)].sval), yyline); ;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 420 "parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;



/* Line 1455 of yacc.c  */
#line 2730 "parser.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 423 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error (line %d): %s near '%s'\n", yyline, s, yytext);
}

