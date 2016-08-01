/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     ID = 259,
     SEMI = 260,
     COMMA = 261,
     TYPE = 262,
     LP = 263,
     RP = 264,
     LB = 265,
     RB = 266,
     LC = 267,
     RC = 268,
     STRUCT = 269,
     RETURN = 270,
     IF = 271,
     ELSE = 272,
     BREAK = 273,
     CONT = 274,
     FOR = 275,
     ASSIGNOP = 276,
     BINARYOP10 = 277,
     BINARYOP9 = 278,
     BINARYOP8 = 279,
     BINARYOP7 = 280,
     BINARYOP6 = 281,
     BINARYOP5 = 282,
     BINARYOP4 = 283,
     BINARYOP3 = 284,
     BINARYOP2 = 285,
     BINARYOP1 = 286,
     UNARYOP = 287,
     DOT = 288
   };
#endif
/* Tokens.  */
#define INT 258
#define ID 259
#define SEMI 260
#define COMMA 261
#define TYPE 262
#define LP 263
#define RP 264
#define LB 265
#define RB 266
#define LC 267
#define RC 268
#define STRUCT 269
#define RETURN 270
#define IF 271
#define ELSE 272
#define BREAK 273
#define CONT 274
#define FOR 275
#define ASSIGNOP 276
#define BINARYOP10 277
#define BINARYOP9 278
#define BINARYOP8 279
#define BINARYOP7 280
#define BINARYOP6 281
#define BINARYOP5 282
#define BINARYOP4 283
#define BINARYOP3 284
#define BINARYOP2 285
#define BINARYOP1 286
#define UNARYOP 287
#define DOT 288




/* Copy the first part of user declarations.  */
#line 1 "Syntax.y"

    /*
    This is the yacc input to generate parser. It calls yylex() to get the tokens. The generated parser will print a parse tree into a file.
     */
    
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "common.h"
    
    int yywrap(void);
    
    int yylex();
    
    tree* parseEntry(char const* sourceFile/*, char const* outputFile*/);
    
    void yyerror(char const*);
    
    //The stack node, in a doubly linked way.
    struct StackNode {
        int position;
        struct StackNode* next;
        struct StackNode* prev;
    };
    
    //The stack used to identify the parenthesis mismatch
    typedef struct sta {
        struct StackNode* top;
    } stack;
    
    //Allocate space for a stack
    stack* initStack();
    
    //Push element into a stack
    void push(stack* s, int newElem);
    
    //Pop element out of stack
    int pop(stack* s);
    
    extern FILE *yyin, *yyout;
    
    //Create a leaf node in the parse tree for a terminal
    extern tree* createLeaf(char const*, int linenumber);
    
    //Create a internal node in the parse tree for a nonterminal
    void createNode(tree*, char const*, int);
    
    //Print the parse tree
    void printTree(tree* root, int level);
    
    extern int yylineno;
    
    //Stack for detecting unmatched '('
    stack* globalStackP;
    
    //Stack for detecting unmatched '['
    stack* globalStackB;
    
    //Stack for detecting curly unmatched '{'
    stack* globalStackC;
    
    //A flag to indicate whether a mismatch has occurred
    int missMatch;
    
    //The number of errors
    int errorCount;
    
    tree* root;


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 118 "Syntax.y"
{
    tree *node;
}
/* Line 193 of yacc.c.  */
#line 236 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 249 "y.tab.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   287

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNRULES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    30,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    13,    17,    21,    23,
      27,    28,    30,    32,    38,    41,    43,    44,    46,    51,
      56,    60,    62,    63,    66,    71,    74,    75,    78,    81,
      83,    87,    91,    98,   108,   111,   114,   117,   120,   123,
     124,   127,   128,   132,   136,   140,   142,   144,   148,   150,
     154,   156,   157,   161,   165,   169,   173,   177,   181,   185,
     189,   193,   197,   201,   204,   207,   211,   216,   219,   223,
     225,   230,   236,   241,   242,   246,   248,   249,   251,   253,
     255,   257,   259,   261,   263,   265
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    37,    -1,    38,    37,    -1,    -1,    40,
      39,     5,    -1,    40,    39,     1,    -1,    40,    44,    47,
      -1,    54,    -1,    54,     6,    39,    -1,    -1,     7,    -1,
      41,    -1,    14,    42,    60,    51,    61,    -1,    14,     4,
      -1,     4,    -1,    -1,     4,    -1,    43,    62,     3,    63,
      -1,     4,    64,    45,    65,    -1,    46,     6,    45,    -1,
      46,    -1,    -1,    40,    43,    -1,    60,    51,    48,    61,
      -1,    49,    48,    -1,    -1,    57,     5,    -1,    57,     1,
      -1,    47,    -1,    15,    57,     5,    -1,    15,    57,     1,
      -1,    16,    64,    57,    65,    49,    50,    -1,    20,    64,
      56,     5,    56,     5,    56,    65,    49,    -1,    19,     5,
      -1,    19,     1,    -1,    18,     5,    -1,    18,     1,    -1,
      17,    49,    -1,    -1,    52,    51,    -1,    -1,    40,    53,
       5,    -1,    40,    53,     1,    -1,    54,     6,    53,    -1,
      54,    -1,    43,    -1,    43,    21,    55,    -1,    57,    -1,
      60,    59,    61,    -1,    57,    -1,    -1,    57,    32,    57,
      -1,    57,    31,    57,    -1,    57,    30,    57,    -1,    57,
      29,    57,    -1,    57,    28,    57,    -1,    57,    27,    57,
      -1,    57,    26,    57,    -1,    57,    25,    57,    -1,    57,
      24,    57,    -1,    57,    23,    57,    -1,    57,    22,    57,
      -1,    33,    57,    -1,    30,    57,    -1,    64,    57,    65,
      -1,     4,    64,    59,    65,    -1,     4,    58,    -1,    57,
      34,     4,    -1,     3,    -1,     4,    58,    21,    57,    -1,
      57,    34,     4,    21,    57,    -1,    62,    57,    63,    58,
      -1,    -1,    57,     6,    59,    -1,    57,    -1,    -1,    12,
      -1,    13,    -1,     1,    -1,    10,    -1,    11,    -1,     1,
      -1,     8,    -1,     9,    -1,     1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   136,   136,   146,   154,   163,   173,   177,   188,   195,
     204,   213,   220,   230,   241,   251,   258,   267,   275,   288,
     300,   309,   316,   325,   336,   348,   356,   365,   374,   379,
     386,   396,   401,   414,   429,   438,   442,   451,   457,   465,
     474,   482,   491,   501,   507,   516,   525,   532,   544,   552,
     564,   571,   583,   592,   601,   610,   619,   628,   637,   646,
     655,   664,   673,   682,   690,   700,   710,   720,   728,   737,
     745,   755,   769,   779,   788,   797,   804,   813,   818,   822,
     830,   835,   839,   847,   852,   856
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "SEMI", "COMMA", "TYPE",
  "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN", "IF", "ELSE",
  "BREAK", "CONT", "FOR", "ASSIGNOP", "BINARYOP10", "BINARYOP9",
  "BINARYOP8", "BINARYOP7", "BINARYOP6", "BINARYOP5", "BINARYOP4",
  "BINARYOP3", "'-'", "BINARYOP2", "BINARYOP1", "UNARYOP", "DOT",
  "$accept", "PROGRAM", "EXTDEFS", "EXTDEF", "EXTVARS", "SPEC", "STSPEC",
  "OPTTAG", "VAR", "FUNC", "PARAS", "PARA", "STMTBLOCK", "STMTS", "STMT",
  "ESTMT", "DEFS", "DEF", "DECS", "DEC", "INIT", "FOREXP", "EXP", "ARRS",
  "ARGS", "enterLC", "leavingRC", "enterLB", "leavingRB", "enterLP",
  "leavingRP", 0
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
      45,   285,   286,   287,   288
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    38,    39,    39,
      39,    40,    40,    41,    41,    42,    42,    43,    43,    44,
      45,    45,    45,    46,    47,    48,    48,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    50,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    55,    55,
      56,    56,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    58,    58,    59,    59,    59,    60,    61,    61,
      62,    63,    63,    64,    65,    65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     3,     3,     1,     3,
       0,     1,     1,     5,     2,     1,     0,     1,     4,     4,
       3,     1,     0,     2,     4,     2,     0,     2,     2,     1,
       3,     3,     6,     9,     2,     2,     2,     2,     2,     0,
       2,     0,     3,     3,     3,     1,     1,     3,     1,     3,
       1,     0,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     3,     4,     2,     3,     1,
       4,     5,     4,     0,     3,     1,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    11,    16,     0,     2,     4,    10,    12,    14,     0,
       1,     3,    17,     0,    46,     0,     8,    77,    41,    83,
      22,     6,     5,    80,     0,     0,     7,    41,    10,     0,
       0,    41,     0,     0,    21,    69,    73,     0,     0,    47,
      48,    76,     0,     0,    26,    17,     9,     0,    45,    79,
      78,    13,    40,    23,    85,    84,    19,    22,    67,     0,
      76,    64,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    75,     0,     0,    82,    81,
      18,     0,     0,     0,     0,     0,    29,     0,    26,     0,
      43,    42,     0,    20,     0,     0,     0,    62,    61,    60,
      59,    58,    57,    56,    55,    54,    53,    52,    68,    76,
      49,    65,     0,     0,    37,    36,    35,    34,    51,    24,
      25,    28,    27,    44,    70,    73,    66,     0,    74,    31,
      30,     0,     0,    50,    72,    71,     0,    51,    39,     0,
       0,    32,    51,    38,     0,     0,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,    13,    29,     7,     9,    14,    15,
      33,    34,    86,    87,    88,   141,    30,    31,    47,    16,
      39,   132,    89,    58,    76,    27,    51,    25,    80,    42,
      56
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -108
static const yytype_int16 yypact[] =
{
      46,  -108,    28,    50,  -108,    46,    64,  -108,    49,    62,
    -108,  -108,    69,    68,     1,    62,    86,  -108,    46,  -108,
      46,  -108,  -108,  -108,     4,    84,  -108,    46,    92,    92,
      14,    46,    92,    19,    99,  -108,    83,    48,    48,  -108,
     215,    48,    48,    20,   187,  -108,  -108,    75,   101,  -108,
    -108,  -108,  -108,    98,  -108,  -108,  -108,    46,    88,    48,
      48,    76,    76,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,   108,   202,    14,    97,  -108,  -108,
    -108,    48,    69,    78,    81,    69,  -108,    14,   187,   110,
    -108,  -108,    92,  -108,    48,   142,    19,   227,   238,   120,
     184,   246,   253,    70,    33,    63,    63,    76,    93,    48,
    -108,  -108,   155,    48,  -108,  -108,  -108,  -108,    48,  -108,
    -108,  -108,  -108,  -108,   215,    98,  -108,    48,  -108,  -108,
    -108,    97,   111,   215,  -108,   215,   187,    48,   100,   125,
     187,  -108,    48,  -108,    19,   187,  -108
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -108,  -108,   150,  -108,   129,     5,  -108,  -108,   126,  -108,
     102,  -108,   146,    74,  -107,  -108,    57,  -108,    71,   -26,
    -108,   -83,   -24,    67,   -54,     0,   -57,   -35,    80,   -10,
     -73
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -16
static const yytype_int16 yytable[] =
{
      40,    59,    20,    48,   111,     6,    96,    35,    36,    18,
       6,    23,    19,    61,    62,    49,    17,    75,    77,   110,
      54,    78,    24,   126,    41,    32,    60,    50,    55,   138,
     119,    79,     8,   143,    37,    95,    75,    38,   146,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
      10,    35,    36,     1,   139,   128,    19,   112,   136,   144,
       2,   -15,    32,    71,    72,    73,    48,    74,    12,    21,
     124,   145,   113,    22,    17,   118,    90,    19,    37,   114,
      91,    38,   116,   115,    44,    75,   117,    43,    52,   131,
      59,    19,    28,    23,   133,    73,    45,    74,    54,    70,
      71,    72,    73,   135,    74,    57,    55,    92,    23,    94,
      74,   121,   108,   133,   127,   122,   137,   140,   133,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
     142,    74,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    78,    74,    66,    67,    68,    69,    70,
      71,    72,    73,    79,    74,    11,   129,    46,    53,    93,
     130,    26,   120,   123,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,   125,    74,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,     0,    74,
      35,    36,   134,     0,     0,    19,     0,     0,     0,    17,
       0,     0,    81,    82,     0,    83,    84,    85,   109,     0,
      67,    68,    69,    70,    71,    72,    73,    37,    74,     0,
      38,     0,     0,     0,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,     0,    74,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,     0,    74,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
       0,    74,    65,    66,    67,    68,    69,    70,    71,    72,
      73,     0,    74,    68,    69,    70,    71,    72,    73,     0,
      74,    69,    70,    71,    72,    73,     0,    74
};

static const yytype_int16 yycheck[] =
{
      24,    36,    12,    29,    77,     0,    60,     3,     4,     9,
       5,    10,     8,    37,    38,     1,    12,    41,    42,    76,
       1,     1,    21,    96,    24,    20,    36,    13,     9,   136,
      87,    11,     4,   140,    30,    59,    60,    33,   145,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
       0,     3,     4,     7,   137,   109,     8,    81,   131,   142,
      14,    12,    57,    30,    31,    32,    92,    34,     4,     1,
      94,   144,    82,     5,    12,    85,     1,     8,    30,     1,
       5,    33,     1,     5,    27,   109,     5,     3,    31,   113,
     125,     8,     6,    10,   118,    32,     4,    34,     1,    29,
      30,    31,    32,   127,    34,     6,     9,     6,    10,    21,
      34,     1,     4,   137,    21,     5,     5,    17,   142,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       5,    34,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     1,    34,    25,    26,    27,    28,    29,
      30,    31,    32,    11,    34,     5,     1,    28,    32,    57,
       5,    15,    88,    92,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    95,    34,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
       3,     4,   125,    -1,    -1,     8,    -1,    -1,    -1,    12,
      -1,    -1,    15,    16,    -1,    18,    19,    20,     6,    -1,
      26,    27,    28,    29,    30,    31,    32,    30,    34,    -1,
      33,    -1,    -1,    -1,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    -1,    34,    27,    28,    29,    30,    31,    32,    -1,
      34,    28,    29,    30,    31,    32,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,    14,    36,    37,    38,    40,    41,     4,    42,
       0,    37,     4,    39,    43,    44,    54,    12,    60,     8,
      64,     1,     5,    10,    21,    62,    47,    60,     6,    40,
      51,    52,    40,    45,    46,     3,     4,    30,    33,    55,
      57,    60,    64,     3,    51,     4,    39,    53,    54,     1,
      13,    61,    51,    43,     1,     9,    65,     6,    58,    62,
      64,    57,    57,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    34,    57,    59,    57,     1,    11,
      63,    15,    16,    18,    19,    20,    47,    48,    49,    57,
       1,     5,     6,    45,    21,    57,    59,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,     4,     6,
      61,    65,    57,    64,     1,     5,     1,     5,    64,    61,
      48,     1,     5,    53,    57,    63,    65,    21,    59,     1,
       5,    57,    56,    57,    58,    57,    65,     5,    49,    56,
      17,    50,     5,    49,    56,    65,    49
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 136 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "PROGRAM", 1);
    ((yyval.node) -> subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
    root = (yyval.node);
}
    break;

  case 3:
#line 146 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXTDEFS", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 4:
#line 154 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXTDEFS", 1);
    ((yyval.node)->subTrees)[0] = NULL;
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 5:
#line 163 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXTDEF", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 6:
#line 173 "Syntax.y"
    {
    if(!missMatch)
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
}
    break;

  case 7:
#line 177 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXTDEF", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 8:
#line 188 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXTVARS", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 9:
#line 195 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXTVARS", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 10:
#line 204 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXTVARS", 1);
    ((yyval.node)->subTrees)[0] = NULL;
    (yyval.node)->productionId = 3;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 11:
#line 213 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "SPEC", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 12:
#line 220 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "SPEC", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 13:
#line 230 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STSPEC", 5);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (5)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (5)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (5)].node);
    ((yyval.node)->subTrees)[3] = (yyvsp[(4) - (5)].node);
    ((yyval.node)->subTrees)[4] = (yyvsp[(5) - (5)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 14:
#line 241 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STSPEC", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 15:
#line 251 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "OPTTAG", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 16:
#line 258 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "OPTTAG", 1);
    ((yyval.node)->subTrees)[0] = NULL;
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 17:
#line 267 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "VAR", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 18:
#line 275 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "VAR", 4);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (4)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (4)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (4)].node);
    ((yyval.node)->subTrees)[3] = (yyvsp[(4) - (4)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 19:
#line 288 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "FUNC", 4);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (4)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (4)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (4)].node);
    ((yyval.node)->subTrees)[3] = (yyvsp[(4) - (4)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 20:
#line 300 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "PARAS", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 21:
#line 309 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "PARAS", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 22:
#line 316 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "PARAS", 1);
    ((yyval.node)->subTrees)[0] = NULL;
    (yyval.node)->productionId = 3;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 23:
#line 325 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "PARA", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 24:
#line 336 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STMTBLOCK", 4);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (4)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (4)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (4)].node);
    ((yyval.node)->subTrees)[3] = (yyvsp[(4) - (4)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 25:
#line 348 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STMTS", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 26:
#line 356 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STMTS", 1);
    ((yyval.node)->subTrees)[0] = NULL;
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 27:
#line 365 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STMT", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 28:
#line 374 "Syntax.y"
    {
    if(!missMatch) {
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
    }
}
    break;

  case 29:
#line 379 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STMT", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 30:
#line 386 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STMT", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 3;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 31:
#line 396 "Syntax.y"
    {
    if(!missMatch)
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
}
    break;

  case 32:
#line 401 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STMT", 6);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (6)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (6)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (6)].node);
    ((yyval.node)->subTrees)[3] = (yyvsp[(4) - (6)].node);
    ((yyval.node)->subTrees)[4] = (yyvsp[(5) - (6)].node);
    ((yyval.node)->subTrees)[5] = (yyvsp[(6) - (6)].node);
    (yyval.node)->productionId = 4;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 33:
#line 414 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STMT", 9);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (9)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (9)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (9)].node);
    ((yyval.node)->subTrees)[3] = (yyvsp[(4) - (9)].node);
    ((yyval.node)->subTrees)[4] = (yyvsp[(5) - (9)].node);
    ((yyval.node)->subTrees)[5] = (yyvsp[(6) - (9)].node);
    ((yyval.node)->subTrees)[6] = (yyvsp[(7) - (9)].node);
    ((yyval.node)->subTrees)[7] = (yyvsp[(8) - (9)].node);
    ((yyval.node)->subTrees)[8] = (yyvsp[(9) - (9)].node);
    (yyval.node)->productionId = 5;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 34:
#line 429 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STMT", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 6;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 35:
#line 438 "Syntax.y"
    {
    if(!missMatch)
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
}
    break;

  case 36:
#line 442 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "STMT", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 7;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 37:
#line 451 "Syntax.y"
    {
    if(!missMatch)
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
}
    break;

  case 38:
#line 457 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "ESTMT", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 39:
#line 465 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "ESTMT", 1);
    ((yyval.node)->subTrees)[0] = NULL;
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 40:
#line 474 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "DEFS", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 41:
#line 482 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "DEFS", 1);
    ((yyval.node)->subTrees)[0] = NULL;
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 42:
#line 491 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "DEF", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 43:
#line 501 "Syntax.y"
    {
    if(!missMatch)
        fprintf(stderr, "Missing ';' between lines %d to %d.\n", yylineno - 1, yylineno);
}
    break;

  case 44:
#line 507 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "DECS", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 45:
#line 516 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "DECS", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 46:
#line 525 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "DEC", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 47:
#line 532 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "DEC", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 48:
#line 544 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "INIT", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 49:
#line 552 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "INIT", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 50:
#line 564 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "FOREXP", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 51:
#line 571 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "FOREXP", 1);
    ((yyval.node)->subTrees)[0] = NULL;
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 52:
#line 583 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 53:
#line 592 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 54:
#line 601 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = createLeaf("-(BINARYOP2)", yylineno);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 55:
#line 610 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 56:
#line 619 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 57:
#line 628 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 58:
#line 637 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 59:
#line 646 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 60:
#line 655 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 61:
#line 664 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 62:
#line 673 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 63:
#line 682 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 64:
#line 690 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 2);
    ((yyval.node)->subTrees)[0] = createLeaf("-(UNARYOP)", yylineno);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 3;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 65:
#line 700 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 4;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 66:
#line 710 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 4);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (4)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (4)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (4)].node);
    ((yyval.node)->subTrees)[3] = (yyvsp[(4) - (4)].node);
    (yyval.node)->productionId = 5;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 67:
#line 720 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 2);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (2)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (2)].node);
    (yyval.node)->productionId = 6;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 68:
#line 728 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 7;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 69:
#line 737 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 8;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 70:
#line 745 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 4);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (4)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (4)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (4)].node);
    ((yyval.node)->subTrees)[3] = (yyvsp[(4) - (4)].node);
    (yyval.node)->productionId = 9;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 71:
#line 755 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "EXP", 5);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (5)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (5)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (5)].node);
    ((yyval.node)->subTrees)[3] = (yyvsp[(4) - (5)].node);
    ((yyval.node)->subTrees)[4] = (yyvsp[(5) - (5)].node);
    (yyval.node)->productionId = 10;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 72:
#line 769 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "ARRS", 4);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (4)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (4)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (4)].node);
    ((yyval.node)->subTrees)[3] = (yyvsp[(4) - (4)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 73:
#line 779 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "ARRS", 1);
    ((yyval.node)->subTrees)[0] = NULL;
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 74:
#line 788 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "ARGS", 3);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (3)].node);
    ((yyval.node)->subTrees)[1] = (yyvsp[(2) - (3)].node);
    ((yyval.node)->subTrees)[2] = (yyvsp[(3) - (3)].node);
    (yyval.node)->productionId = 1;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 75:
#line 797 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "ARGS", 1);
    ((yyval.node)->subTrees)[0] = (yyvsp[(1) - (1)].node);
    (yyval.node)->productionId = 2;
    (yyval.node)->lineNumber = yylineno;
}
    break;

  case 76:
#line 804 "Syntax.y"
    {
    (yyval.node) = (tree*)malloc(sizeof(tree));
    createNode((yyval.node), "ARGS", 1);
    ((yyval.node)->subTrees)[0] = NULL;
    (yyval.node)->productionId = 3;
    
}
    break;

  case 77:
#line 813 "Syntax.y"
    {
    (yyval.node) = (yyvsp[(1) - (1)].node);
    push(globalStackC, yylineno);
}
    break;

  case 78:
#line 818 "Syntax.y"
    {
    pop(globalStackC);
    (yyval.node) = (yyvsp[(1) - (1)].node);
}
    break;

  case 79:
#line 822 "Syntax.y"
    {
    if(globalStackC->top->prev != NULL && !missMatch) {
        missMatch = 1;
        fprintf(stderr, "Missing matched '}' for the '{' in line %d.\n", pop(globalStackC));
    }
}
    break;

  case 80:
#line 830 "Syntax.y"
    {
    (yyval.node) = (yyvsp[(1) - (1)].node);
    push(globalStackB, yylineno);
}
    break;

  case 81:
#line 835 "Syntax.y"
    {
    (yyval.node) = (yyvsp[(1) - (1)].node);
    pop(globalStackB);
}
    break;

  case 82:
#line 839 "Syntax.y"
    {
    if(globalStackB->top->prev != NULL && !missMatch) {
        missMatch = 1;
        fprintf(stderr, "Missing matched ']' for the '[' in line %d.\n", pop(globalStackB));
    }
}
    break;

  case 83:
#line 847 "Syntax.y"
    {
    (yyval.node) = (yyvsp[(1) - (1)].node);
    push(globalStackP, yylineno);
}
    break;

  case 84:
#line 852 "Syntax.y"
    {
    (yyval.node) = (yyvsp[(1) - (1)].node);
    pop(globalStackP);
}
    break;

  case 85:
#line 856 "Syntax.y"
    {
    if(globalStackP->top->prev != NULL && !missMatch) {
        missMatch = 1;
        fprintf(stderr, "Missing matched ')' for the '(' in line %d.\n", pop(globalStackP));
    }
}
    break;


/* Line 1267 of yacc.c.  */
#line 2588 "y.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 864 "Syntax.y"


tree* parseEntry(char const* sourceFile/*, char const* outputFile*/)
{
    //Initializes three stacks used for parenthese detection.
    globalStackP = initStack();
    globalStackB = initStack();
    globalStackC = initStack();
    
    //Initialize variables used for error detection.
    missMatch = 0;
    errorCount = 0;
    yylineno = 1;
    
    //Open files.
    yyin = fopen(sourceFile, "r");
    if(!yyin) {
        fprintf(stderr, "No such file.\n");
        return NULL;
    }
    /*yyout = fopen(outputFile, "w");
    if(!yyout) {
        fprintf(stderr, "No such file.\n");
        return NULL;
    }*/
    if(yyparse()) {
        printf("Parse Error.\n");
    }
    else {
        if(errorCount > 0)
            printf("Parsing success with syntax error(s).\n");
        /*else
            printf("Parsing success.\n");*/
        //printTree(root, 0);
    }
    if(errorCount > 0) {
        printf("%d error(s) in total.\n", errorCount);
    }
    fclose(yyin);
    //fclose(yyout);
    return root;
}

//A recursive function for parse tree printing.
void printTree(tree* root, int level) {
    int i = 0;
    
    if(root != NULL) {
        
        for(i = 0; i < level; ++i) {
            fprintf(yyout, "%s", "----");
        }
    
        fprintf(yyout, "%s", "|");
        fprintf(yyout, "%s", root->symbol);
        fprintf(yyout, "%s", "\n");
    
        for(i = 0; i < root->childNum; ++i) {
            //The children should have one deeper level than parent.
            printTree((root->subTrees)[i], level + 1);
        }
    }
    
    return;
}

//Initialize a stack
stack* initStack() {
    //Allocate memory for stack
    stack* newStack = (stack*)malloc(sizeof(stack));
    newStack->top = (struct StackNode*)malloc(sizeof(struct StackNode));
    
    //Set the stack as empty
    newStack->top->next = newStack->top->prev = NULL;
    
    return newStack;
}

//Push an element into a stack
void push(stack* s, int newElem) {
    struct StackNode* tempNode = s->top;
    s->top->next = (struct StackNode*)malloc(sizeof(struct StackNode));
    s->top->next->position = newElem;
    s->top->next->next = NULL;
    s->top = s->top->next;
    s->top->prev = tempNode;
}

//Pop an element out of stack
int pop(stack* s) {
    if(s->top->prev != NULL) {
        struct StackNode* tempNode = s->top;
        int topElem = s->top->position;
        s->top = s->top->prev;
        s->top->next = NULL;
        free(tempNode);
        return topElem;
    }
    return -1;
}

//Create an internal parse tree node, with the nonterminal name and children number.
void createNode(tree* newTree, char const* nodeName, int childNum) {
    newTree->symbol = (char*)malloc(sizeof(char) * (strlen(nodeName) + 1));
    strcpy(newTree->symbol, nodeName);
    newTree->subTrees = (tree**)malloc(sizeof(tree*) * childNum);
    newTree->childNum = childNum;
}

void yyerror(char const* errorMessage) {
    ++errorCount;
    fprintf(stderr, "Syntax error.\n");
}

int yywrap(void){return 1;}


