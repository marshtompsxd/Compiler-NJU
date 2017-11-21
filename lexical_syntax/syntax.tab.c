/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "syntax.y" /* yacc.c:339  */

#include <stdio.h>
#include "lex.yy.h"
#include "ParsingNode.h"

int prev_error_lineno = 0;

void yyerror(char* msg );

void ErrorTypeBHandler(int lineno, char* msg);


#line 79 "syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    ID = 260,
    SEMI = 261,
    COMMA = 262,
    ASSIGNOP = 263,
    RELOP = 264,
    PLUS = 265,
    MINUS = 266,
    STAR = 267,
    DIV = 268,
    OR = 269,
    AND = 270,
    DOT = 271,
    NOT = 272,
    TYPE = 273,
    LP = 274,
    RP = 275,
    LB = 276,
    RB = 277,
    LC = 278,
    RC = 279,
    STRUCT = 280,
    RETURN = 281,
    IF = 282,
    ELSE = 283,
    WHILE = 284,
    END = 285,
    LOWER_THAN_RP = 286,
    LOWER_THAN_ELSE = 287,
    LOWER_THAN_SEMI = 288,
    LOWER_THAN_RC = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "syntax.y" /* yacc.c:355  */

    struct ParsingNode *node;

#line 158 "syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 175 "syntax.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    41,    41,    44,    45,    48,    49,    50,    51,    52,
      53,    56,    57,    61,    62,    65,    66,    67,    70,    71,
      74,    78,    79,    80,    81,    84,    85,    86,    89,    90,
      93,    97,    98,    99,   102,   103,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   124,   125,   128,   129,   130,   131,   134,   135,   138,
     139,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   169,   170
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "OR", "AND", "DOT",
  "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "END", "LOWER_THAN_RP", "LOWER_THAN_ELSE",
  "LOWER_THAN_SEMI", "LOWER_THAN_RC", "$accept", "Program", "ExtDefList",
  "ExtDef", "ExtDecList", "Specifier", "StructSpecifier", "OptTag", "Tag",
  "VarDec", "FunDec", "VarList", "ParamDec", "CompSt", "StmtList", "Stmt",
  "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
# endif

#define YYPACT_NINF -62

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-62)))

#define YYTABLE_NINF -52

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      31,   -62,    10,    44,   -62,    31,    12,   -62,    32,    40,
     -62,   -62,   -62,    66,    61,   -62,    69,    -2,    60,    23,
     -62,    25,   111,   -62,   132,    11,    35,   -62,   114,   132,
     127,    31,   133,   -62,   132,   140,   145,   -62,   -62,   -62,
     143,    20,   142,    62,   -62,    -1,    81,   160,   -62,   -62,
     -62,   147,   -62,    31,   -62,   149,   -62,   -62,   -62,   -62,
     155,   200,   200,   200,    73,   163,   168,   -62,   164,    62,
     118,   200,   183,   -62,   132,   -62,   -62,   153,    97,    99,
     227,   184,   134,   158,   175,   -62,   -62,   105,   -62,   200,
     200,   200,   200,   200,   200,   200,   200,   188,   180,   269,
     -62,   100,   -62,   176,   -62,   213,     7,   -62,   -62,   189,
     -62,   186,   241,   187,   255,   -62,   -62,   203,   283,   316,
      97,    97,    99,    99,   296,   309,   -62,   190,    85,   197,
     200,   -62,   200,    94,   -62,   -62,    62,    62,    62,    62,
     -62,   -62,   191,   -62,   204,   283,   -62,   -62,   195,   202,
     205,   -62,   -62,   -62,   -62,   -62,    62,    62,   -62,   -62
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    13,    18,     0,     2,     3,     0,    14,    20,     0,
      16,     1,     4,     8,    21,     6,     0,    11,     0,     0,
      10,     0,     0,     5,     0,     0,     0,     7,     0,     0,
       0,    51,     0,    26,     0,     0,    29,     9,    21,    12,
       0,     0,    32,    34,    17,    59,     0,    57,    15,    52,
      27,    30,    25,     0,    24,     0,    22,    33,    77,    78,
      76,     0,     0,     0,     0,     0,     0,    37,     0,    34,
       0,     0,    55,    53,     0,    28,    23,     0,    70,    71,
       0,     0,     0,     0,     0,    31,    35,    42,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      54,    59,    58,     0,    73,    86,     0,    69,    46,     0,
      38,     0,     0,     0,     0,    43,    44,     0,    61,    64,
      65,    66,    67,    68,    63,    62,    75,     0,     0,     0,
       0,    81,     0,    84,    72,    45,     0,     0,     0,     0,
      47,    80,     0,    74,     0,    60,    85,    82,     0,    49,
      39,    48,    41,    79,    56,    83,     0,     0,    50,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -62,   -62,   226,   -62,   194,     4,   -62,   -62,   -62,   -23,
     -62,   179,   -62,   228,   217,   -34,   110,   -62,   170,   -62,
     -61,   113
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    16,    29,     7,     9,    10,    17,
      18,    35,    36,    67,    68,    69,    30,    31,    46,    47,
      70,   106
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,    79,    80,    82,     6,    24,    45,    71,   133,     6,
      99,    51,    40,    13,    41,     8,   105,    14,    15,    25,
      25,    55,   112,   114,    28,    34,    32,   134,   118,   119,
     120,   121,   122,   123,   124,   125,    42,   128,   -51,   -51,
     -51,     1,    56,     1,    11,    33,   -51,   -51,     2,     1,
       2,   101,   -51,     1,   -51,   -19,     2,    34,   -51,   -51,
       2,   -51,   -51,    19,   -51,    58,    59,    60,   121,   145,
      22,   105,    20,    61,    81,    23,    58,    59,    60,    62,
      21,    63,    72,    26,    61,    26,   142,    73,    64,    65,
      62,    66,    63,    89,    90,    91,    92,    93,    94,    95,
      96,    97,   149,   150,   151,   152,    98,   143,   130,    93,
      94,   115,   116,    97,   147,    97,   148,    37,    98,    87,
      98,    25,   158,   159,    88,   117,    89,    90,    91,    92,
      93,    94,    95,    96,    97,   109,    43,    38,    44,    98,
     110,    49,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    48,    53,    50,   103,    98,    58,    59,    60,   111,
      52,    58,    59,    60,    61,    54,    57,    74,    25,    61,
      62,    76,    63,   104,    77,    62,   113,    63,    58,    59,
      60,   127,    83,    58,    59,    60,    61,    84,    85,   100,
     108,    61,    62,   126,    63,   135,   131,    62,   144,    63,
      58,    59,    60,    58,    59,    60,   136,   138,    61,   140,
     154,    61,   141,   153,    62,   155,    63,    62,    39,    63,
     132,    89,    90,    91,    92,    93,    94,    95,    96,    97,
     156,    12,    75,   157,    98,    89,    90,    91,    92,    93,
      94,    95,    96,    97,   102,   146,    27,   107,    98,    89,
      90,    91,    92,    93,    94,    95,    96,    97,     0,     0,
       0,   137,    98,    89,    90,    91,    92,    93,    94,    95,
      96,    97,     0,     0,     0,   139,    98,    89,    90,    91,
     129,    93,    94,    95,    96,    97,    86,     0,     0,     0,
      98,    89,    90,    91,    92,    93,    94,    95,    96,    97,
       0,     0,     0,     0,    98,    90,    91,    92,    93,    94,
       0,    96,    97,     0,     0,     0,     0,    98,    90,    91,
      92,    93,    94,     0,     0,    97,    91,    92,    93,    94,
      98,     0,    97,     0,     0,     0,     0,    98
};

static const yytype_int16 yycheck[] =
{
      61,    62,    63,    64,     0,     7,    29,     8,     1,     5,
      71,    34,     1,     1,     3,     5,    77,     5,     6,    21,
      21,     1,    83,    84,     1,    21,     1,    20,    89,    90,
      91,    92,    93,    94,    95,    96,     1,    98,     3,     4,
       5,    18,    22,    18,     0,    20,    11,    24,    25,    18,
      25,    74,    17,    18,    19,    23,    25,    53,    23,    24,
      25,    26,    27,    23,    29,     3,     4,     5,   129,   130,
       1,   132,     6,    11,     1,     6,     3,     4,     5,    17,
      19,    19,     1,    23,    11,    23,     1,     6,    26,    27,
      17,    29,    19,     8,     9,    10,    11,    12,    13,    14,
      15,    16,   136,   137,   138,   139,    21,    22,     8,    12,
      13,     6,     7,    16,    20,    16,    22,     6,    21,     1,
      21,    21,   156,   157,     6,    20,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     1,    26,     5,    24,    21,
       6,    31,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    24,     7,    20,     1,    21,     3,     4,     5,     1,
      20,     3,     4,     5,    11,    22,    24,     7,    21,    11,
      17,    22,    19,    20,    19,    17,     1,    19,     3,     4,
       5,     1,    19,     3,     4,     5,    11,    19,    24,     6,
       6,    11,    17,     5,    19,     6,    20,    17,     1,    19,
       3,     4,     5,     3,     4,     5,    20,    20,    11,     6,
       6,    11,    22,    22,    17,    20,    19,    17,    24,    19,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      28,     5,    53,    28,    21,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    74,   132,    18,    20,    21,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    20,    21,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    20,    21,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    69,    -1,    -1,    -1,
      21,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    21,     9,    10,    11,    12,    13,
      -1,    15,    16,    -1,    -1,    -1,    -1,    21,     9,    10,
      11,    12,    13,    -1,    -1,    16,    10,    11,    12,    13,
      21,    -1,    16,    -1,    -1,    -1,    -1,    21
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    25,    36,    37,    38,    40,    41,     5,    42,
      43,     0,    37,     1,     5,     6,    39,    44,    45,    23,
       6,    19,     1,     6,     7,    21,    23,    48,     1,    40,
      51,    52,     1,    20,    40,    46,    47,     6,     5,    39,
       1,     3,     1,    51,    24,    44,    53,    54,    24,    51,
      20,    44,    20,     7,    22,     1,    22,    24,     3,     4,
       5,    11,    17,    19,    26,    27,    29,    48,    49,    50,
      55,     8,     1,     6,     7,    46,    22,    19,    55,    55,
      55,     1,    55,    19,    19,    24,    49,     1,     6,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    21,    55,
       6,    44,    53,     1,    20,    55,    56,    20,     6,     1,
       6,     1,    55,     1,    55,     6,     7,    20,    55,    55,
      55,    55,    55,    55,    55,    55,     5,     1,    55,    11,
       8,    20,     7,     1,    20,     6,    20,    20,    20,    20,
       6,    22,     1,    22,     1,    55,    56,    20,    22,    50,
      50,    50,    50,    22,     6,    20,    28,    28,    50,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    38,    38,    38,
      38,    39,    39,    40,    40,    41,    41,    41,    42,    42,
      43,    44,    44,    44,    44,    45,    45,    45,    46,    46,
      47,    48,    48,    48,    49,    49,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    51,    51,    52,    52,    52,    52,    53,    53,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    56,    56
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     2,     4,
       3,     1,     3,     1,     1,     5,     2,     5,     0,     1,
       1,     1,     4,     5,     4,     4,     3,     4,     3,     1,
       2,     4,     2,     3,     0,     2,     2,     1,     3,     5,
       7,     5,     2,     3,     3,     4,     3,     4,     5,     5,
       7,     0,     2,     3,     4,     3,     7,     1,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     4,     3,     1,     1,     1,     5,
       4,     4,     5,     6,     4,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 41 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AProgram, 1, (yyvsp[0].node));ParsingRoot = (yyval.node);}
#line 1391 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 44 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateDummyNode(AExtDefList);}
#line 1397 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 45 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExtDefList, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1403 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 48 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExtDef, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1409 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 49 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExtDef, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1415 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 50 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExtDef, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1421 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 51 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"}\", maybe Missing \";\".");}
#line 1427 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 52 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \";\".");}
#line 1433 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 53 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \";\".");}
#line 1439 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 56 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExtDecList, 1, (yyvsp[0].node));}
#line 1445 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 57 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExtDecList, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1451 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 61 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(ASpecifier, 1, (yyvsp[0].node));}
#line 1457 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 62 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(ASpecifier, 1, (yyvsp[0].node));}
#line 1463 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 65 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AStructSpecifier, 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1469 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 66 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AStructSpecifier, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1475 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 67 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \"}\".");}
#line 1481 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 70 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateDummyNode(AOptTag);}
#line 1487 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 71 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AOptTag, 1, (yyvsp[0].node));}
#line 1493 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 74 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(ATag, 1, (yyvsp[0].node));}
#line 1499 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 78 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AVarDec, 1, (yyvsp[0].node));}
#line 1505 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 79 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AVarDec, 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1511 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 80 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \"]\", maybe Missing \"]\".");}
#line 1517 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 81 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"[\".");}
#line 1523 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 84 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AFunDec, 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1529 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 85 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AFunDec, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1535 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 86 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"(\".");}
#line 1541 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 89 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AVarList, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1547 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 90 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AVarList, 1, (yyvsp[0].node));}
#line 1553 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 93 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AParamDec, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1559 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 97 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(ACompSt, 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1565 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 98 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Missing \"}\"");}
#line 1571 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 99 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \"}\".");}
#line 1577 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 102 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateDummyNode(AStmtList);}
#line 1583 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 103 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AStmtList, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1589 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 106 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AStmt, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1595 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 107 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AStmt, 1, (yyvsp[0].node));}
#line 1601 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 108 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AStmt, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1607 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 109 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AStmt, 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1613 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 110 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AStmt, 7, (yyvsp[-6].node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1619 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 111 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AStmt, 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1625 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 112 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Missing \";\".");}
#line 1631 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 113 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \";\", maybe Missing \";\".");}
#line 1637 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 114 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error near \",\".");}
#line 1643 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 115 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \";\".");}
#line 1649 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 116 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \";\".");}
#line 1655 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 117 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error near \")\"");}
#line 1661 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 118 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \")\"");}
#line 1667 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 119 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \")\"");}
#line 1673 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 120 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \")\"");}
#line 1679 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 124 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateDummyNode(ADefList);}
#line 1685 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 125 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(ADefList, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1691 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 128 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(ADef, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1697 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 129 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Missing \";\".");}
#line 1703 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 130 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Missing \";\".");}
#line 1709 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 131 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Missing \";\".");}
#line 1715 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 134 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(ADecList, 1, (yyvsp[0].node));}
#line 1721 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 135 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(ADecList, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1727 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 138 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(ADec, 1, (yyvsp[0].node));}
#line 1733 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 139 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(ADec, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1739 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 143 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1745 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 144 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1751 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 145 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1757 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 146 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1763 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 147 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1769 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 148 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1775 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 149 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1781 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 150 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1787 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 151 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1793 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 152 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1799 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 153 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 2, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1805 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 154 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1811 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 155 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1817 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 156 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1823 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 157 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1829 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 158 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 1, (yyvsp[0].node));}
#line 1835 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 159 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 1, (yyvsp[0].node));}
#line 1841 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 160 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AExp, 1, (yyvsp[0].node));}
#line 1847 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 161 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Missing \"]\".");}
#line 1853 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 162 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"[\".");}
#line 1859 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 163 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"(\".");}
#line 1865 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 164 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \")\".");}
#line 1871 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 165 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \")\".");}
#line 1877 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 166 "syntax.y" /* yacc.c:1646  */
    {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"(\".");}
#line 1883 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 169 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AArgs, 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1889 "syntax.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 170 "syntax.y" /* yacc.c:1646  */
    {(yyval.node) = GenerateVariableNode(AArgs, 1, (yyvsp[0].node));}
#line 1895 "syntax.tab.c" /* yacc.c:1646  */
    break;


#line 1899 "syntax.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 173 "syntax.y" /* yacc.c:1906  */



void yyerror(char* msg __attribute__((unused))) {  
    ParsingSwitch = false;
    prev_error_lineno = yylineno;  
    //printf("syntax error\n");
}

void ErrorTypeBHandler(int lineno, char* msg){
    ParsingSwitch = false;
    printf("\033[31mError type B at Line %d: %s\033[0m\n", lineno, msg);
}
