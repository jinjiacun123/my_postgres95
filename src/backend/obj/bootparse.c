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

/* All symbols defined below should begin with Int_yy or YY, to avoid
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
#line 1 "/home/jim/source_code/my_postgres95/src/backend/bootstrap/bootparse.y"

#include "access/xact.h"
#include "bootstrap/bootstrap.h"

#define DO_START {StartTransactionCommand();}

#define DO_END {CommitTransactionCommand();\
  if(!Quiet){ EMITPROMPT}\
  fflush(stdout);\
 }



/* Line 268 of yacc.c  */
#line 85 "y.tab.c"

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
   enum Int_yytokentype {
     ID = 258,
     OPEN = 259
   };
#endif
/* Tokens.  */
#define ID 258
#define OPEN 259




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 14 "/home/jim/source_code/my_postgres95/src/backend/bootstrap/bootparse.y"

  int ival;



/* Line 293 of yacc.c  */
#line 135 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define Int_yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 147 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 Int_yytype_uint8;
#else
typedef unsigned char Int_yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 Int_yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char Int_yytype_int8;
#else
typedef short int Int_yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 Int_yytype_uint16;
#else
typedef unsigned short int Int_yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 Int_yytype_int16;
#else
typedef short int Int_yytype_int16;
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
YYID (int Int_yyi)
#else
static int
YYID (Int_yyi)
    int Int_yyi;
#endif
{
  return Int_yyi;
}
#endif

#if ! defined Int_yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined Int_yyoverflow || YYERROR_VERBOSE */


#if (! defined Int_yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union Int_yyalloc
{
  Int_yytype_int16 Int_yyss_alloc;
  YYSTYPE Int_yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union Int_yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (Int_yytype_int16) + sizeof (YYSTYPE)) \
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
	YYSIZE_T Int_yynewbytes;						\
	YYCOPY (&Int_yyptr->Stack_alloc, Stack, Int_yysize);			\
	Stack = &Int_yyptr->Stack_alloc;					\
	Int_yynewbytes = Int_yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	Int_yyptr += Int_yynewbytes / sizeof (*Int_yyptr);				\
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
	  YYSIZE_T Int_yyi;				\
	  for (Int_yyi = 0; Int_yyi < (Count); Int_yyi++)	\
	    (To)[Int_yyi] = (From)[Int_yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  5
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  6
/* YYNRULES -- Number of rules.  */
#define YYNRULES  8
/* YYNRULES -- Number of states.  */
#define YYNSTATES  10

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   259

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? Int_yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const Int_yytype_uint8 Int_yytranslate[] =
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const Int_yytype_uint8 Int_yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    11,    13,    16
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const Int_yytype_int8 Int_yyrhs[] =
{
       6,     0,    -1,     7,    -1,    -1,     8,    -1,     7,     8,
      -1,     9,    -1,     4,    10,    -1,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const Int_yytype_uint8 Int_yyrline[] =
{
       0,    24,    24,    25,    29,    30,    34,    38,    46
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const Int_yytname[] =
{
  "$end", "error", "$undefined", "ID", "OPEN", "$accept", "TopLevel",
  "Queries", "Query", "OpenStmt", "ident", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const Int_yytype_uint16 Int_yytoknum[] =
{
       0,   256,   257,   258,   259
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const Int_yytype_uint8 Int_yyr1[] =
{
       0,     5,     6,     6,     7,     7,     8,     9,    10
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const Int_yytype_uint8 Int_yyr2[] =
{
       0,     2,     1,     0,     1,     2,     1,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const Int_yytype_uint8 Int_yydefact[] =
{
       3,     0,     0,     2,     4,     6,     8,     7,     1,     5
};

/* YYDEFGOTO[NTERM-NUM].  */
static const Int_yytype_int8 Int_yydefgoto[] =
{
      -1,     2,     3,     4,     5,     7
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -5
static const Int_yytype_int8 Int_yypact[] =
{
      -4,    -2,     2,    -4,    -5,    -5,    -5,    -5,    -5,    -5
};

/* YYPGOTO[NTERM-NUM].  */
static const Int_yytype_int8 Int_yypgoto[] =
{
      -5,    -5,    -5,     0,    -5,    -5
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const Int_yytype_uint8 Int_yytable[] =
{
       1,     6,     8,     9
};

#define Int_yypact_value_is_default(Int_yystate) \
  ((Int_yystate) == (-5))

#define Int_yytable_value_is_error(Int_yytable_value) \
  YYID (0)

static const Int_yytype_uint8 Int_yycheck[] =
{
       4,     3,     0,     3
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const Int_yytype_uint8 Int_yystos[] =
{
       0,     4,     6,     7,     8,     9,     3,    10,     0,     8
};

#define Int_yyerrok		(Int_yyerrstatus = 0)
#define Int_yyclearin	(Int_yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto Int_yyacceptlab
#define YYABORT		goto Int_yyabortlab
#define YYERROR		goto Int_yyerrorlab


/* Like YYERROR except do call Int_yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto Int_yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!Int_yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (Int_yychar == YYEMPTY && Int_yylen == 1)				\
    {								\
      Int_yychar = (Token);						\
      Int_yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto Int_yybackup;						\
    }								\
  else								\
    {								\
      Int_yyerror (YY_("syntax error: cannot back up")); \
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


/* YYLEX -- calling `Int_yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX Int_yylex (YYLEX_PARAM)
#else
# define YYLEX Int_yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (Int_yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (Int_yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      Int_yy_symbol_print (stderr,						  \
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
Int_yy_symbol_value_print (FILE *Int_yyoutput, int Int_yytype, YYSTYPE const * const Int_yyvaluep)
#else
static void
Int_yy_symbol_value_print (Int_yyoutput, Int_yytype, Int_yyvaluep)
    FILE *Int_yyoutput;
    int Int_yytype;
    YYSTYPE const * const Int_yyvaluep;
#endif
{
  if (!Int_yyvaluep)
    return;
# ifdef YYPRINT
  if (Int_yytype < YYNTOKENS)
    YYPRINT (Int_yyoutput, Int_yytoknum[Int_yytype], *Int_yyvaluep);
# else
  YYUSE (Int_yyoutput);
# endif
  switch (Int_yytype)
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
Int_yy_symbol_print (FILE *Int_yyoutput, int Int_yytype, YYSTYPE const * const Int_yyvaluep)
#else
static void
Int_yy_symbol_print (Int_yyoutput, Int_yytype, Int_yyvaluep)
    FILE *Int_yyoutput;
    int Int_yytype;
    YYSTYPE const * const Int_yyvaluep;
#endif
{
  if (Int_yytype < YYNTOKENS)
    YYFPRINTF (Int_yyoutput, "token %s (", Int_yytname[Int_yytype]);
  else
    YYFPRINTF (Int_yyoutput, "nterm %s (", Int_yytname[Int_yytype]);

  Int_yy_symbol_value_print (Int_yyoutput, Int_yytype, Int_yyvaluep);
  YYFPRINTF (Int_yyoutput, ")");
}

/*------------------------------------------------------------------.
| Int_yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
Int_yy_stack_print (Int_yytype_int16 *Int_yybottom, Int_yytype_int16 *Int_yytop)
#else
static void
Int_yy_stack_print (Int_yybottom, Int_yytop)
    Int_yytype_int16 *Int_yybottom;
    Int_yytype_int16 *Int_yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; Int_yybottom <= Int_yytop; Int_yybottom++)
    {
      int Int_yybot = *Int_yybottom;
      YYFPRINTF (stderr, " %d", Int_yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (Int_yydebug)							\
    Int_yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
Int_yy_reduce_print (YYSTYPE *Int_yyvsp, int Int_yyrule)
#else
static void
Int_yy_reduce_print (Int_yyvsp, Int_yyrule)
    YYSTYPE *Int_yyvsp;
    int Int_yyrule;
#endif
{
  int Int_yynrhs = Int_yyr2[Int_yyrule];
  int Int_yyi;
  unsigned long int Int_yylno = Int_yyrline[Int_yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     Int_yyrule - 1, Int_yylno);
  /* The symbols being reduced.  */
  for (Int_yyi = 0; Int_yyi < Int_yynrhs; Int_yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", Int_yyi + 1);
      Int_yy_symbol_print (stderr, Int_yyrhs[Int_yyprhs[Int_yyrule] + Int_yyi],
		       &(Int_yyvsp[(Int_yyi + 1) - (Int_yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (Int_yydebug)				\
    Int_yy_reduce_print (Int_yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int Int_yydebug;
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

# ifndef Int_yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define Int_yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
Int_yystrlen (const char *Int_yystr)
#else
static YYSIZE_T
Int_yystrlen (Int_yystr)
    const char *Int_yystr;
#endif
{
  YYSIZE_T Int_yylen;
  for (Int_yylen = 0; Int_yystr[Int_yylen]; Int_yylen++)
    continue;
  return Int_yylen;
}
#  endif
# endif

# ifndef Int_yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define Int_yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
Int_yystpcpy (char *Int_yydest, const char *Int_yysrc)
#else
static char *
Int_yystpcpy (Int_yydest, Int_yysrc)
    char *Int_yydest;
    const char *Int_yysrc;
#endif
{
  char *Int_yyd = Int_yydest;
  const char *Int_yys = Int_yysrc;

  while ((*Int_yyd++ = *Int_yys++) != '\0')
    continue;

  return Int_yyd - 1;
}
#  endif
# endif

# ifndef Int_yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for Int_yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from Int_yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
Int_yytnamerr (char *Int_yyres, const char *Int_yystr)
{
  if (*Int_yystr == '"')
    {
      YYSIZE_T Int_yyn = 0;
      char const *Int_yyp = Int_yystr;

      for (;;)
	switch (*++Int_yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++Int_yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (Int_yyres)
	      Int_yyres[Int_yyn] = *Int_yyp;
	    Int_yyn++;
	    break;

	  case '"':
	    if (Int_yyres)
	      Int_yyres[Int_yyn] = '\0';
	    return Int_yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! Int_yyres)
    return Int_yystrlen (Int_yystr);

  return Int_yystpcpy (Int_yyres, Int_yystr) - Int_yyres;
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
Int_yysyntax_error (YYSIZE_T *Int_yymsg_alloc, char **Int_yymsg,
                Int_yytype_int16 *Int_yyssp, int Int_yytoken)
{
  YYSIZE_T Int_yysize0 = Int_yytnamerr (0, Int_yytname[Int_yytoken]);
  YYSIZE_T Int_yysize = Int_yysize0;
  YYSIZE_T Int_yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *Int_yyformat = 0;
  /* Arguments of Int_yyformat. */
  char const *Int_yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int Int_yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in Int_yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated Int_yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (Int_yytoken != YYEMPTY)
    {
      int Int_yyn = Int_yypact[*Int_yyssp];
      Int_yyarg[Int_yycount++] = Int_yytname[Int_yytoken];
      if (!Int_yypact_value_is_default (Int_yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int Int_yyxbegin = Int_yyn < 0 ? -Int_yyn : 0;
          /* Stay within bounds of both Int_yycheck and Int_yytname.  */
          int Int_yychecklim = YYLAST - Int_yyn + 1;
          int Int_yyxend = Int_yychecklim < YYNTOKENS ? Int_yychecklim : YYNTOKENS;
          int Int_yyx;

          for (Int_yyx = Int_yyxbegin; Int_yyx < Int_yyxend; ++Int_yyx)
            if (Int_yycheck[Int_yyx + Int_yyn] == Int_yyx && Int_yyx != YYTERROR
                && !Int_yytable_value_is_error (Int_yytable[Int_yyx + Int_yyn]))
              {
                if (Int_yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    Int_yycount = 1;
                    Int_yysize = Int_yysize0;
                    break;
                  }
                Int_yyarg[Int_yycount++] = Int_yytname[Int_yyx];
                Int_yysize1 = Int_yysize + Int_yytnamerr (0, Int_yytname[Int_yyx]);
                if (! (Int_yysize <= Int_yysize1
                       && Int_yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                Int_yysize = Int_yysize1;
              }
        }
    }

  switch (Int_yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        Int_yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  Int_yysize1 = Int_yysize + Int_yystrlen (Int_yyformat);
  if (! (Int_yysize <= Int_yysize1 && Int_yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  Int_yysize = Int_yysize1;

  if (*Int_yymsg_alloc < Int_yysize)
    {
      *Int_yymsg_alloc = 2 * Int_yysize;
      if (! (Int_yysize <= *Int_yymsg_alloc
             && *Int_yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *Int_yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *Int_yyp = *Int_yymsg;
    int Int_yyi = 0;
    while ((*Int_yyp = *Int_yyformat) != '\0')
      if (*Int_yyp == '%' && Int_yyformat[1] == 's' && Int_yyi < Int_yycount)
        {
          Int_yyp += Int_yytnamerr (Int_yyp, Int_yyarg[Int_yyi++]);
          Int_yyformat += 2;
        }
      else
        {
          Int_yyp++;
          Int_yyformat++;
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
Int_yydestruct (const char *Int_yymsg, int Int_yytype, YYSTYPE *Int_yyvaluep)
#else
static void
Int_yydestruct (Int_yymsg, Int_yytype, Int_yyvaluep)
    const char *Int_yymsg;
    int Int_yytype;
    YYSTYPE *Int_yyvaluep;
#endif
{
  YYUSE (Int_yyvaluep);

  if (!Int_yymsg)
    Int_yymsg = "Deleting";
  YY_SYMBOL_PRINT (Int_yymsg, Int_yytype, Int_yyvaluep, Int_yylocationp);

  switch (Int_yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int Int_yyparse (void *YYPARSE_PARAM);
#else
int Int_yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int Int_yyparse (void);
#else
int Int_yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int Int_yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE Int_yylval;

/* Number of syntax errors so far.  */
int Int_yynerrs;


/*----------.
| Int_yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
Int_yyparse (void *YYPARSE_PARAM)
#else
int
Int_yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
Int_yyparse (void)
#else
int
Int_yyparse ()

#endif
#endif
{
    int Int_yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int Int_yyerrstatus;

    /* The stacks and their tools:
       `Int_yyss': related to states.
       `Int_yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow Int_yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    Int_yytype_int16 Int_yyssa[YYINITDEPTH];
    Int_yytype_int16 *Int_yyss;
    Int_yytype_int16 *Int_yyssp;

    /* The semantic value stack.  */
    YYSTYPE Int_yyvsa[YYINITDEPTH];
    YYSTYPE *Int_yyvs;
    YYSTYPE *Int_yyvsp;

    YYSIZE_T Int_yystacksize;

  int Int_yyn;
  int Int_yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int Int_yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE Int_yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char Int_yymsgbuf[128];
  char *Int_yymsg = Int_yymsgbuf;
  YYSIZE_T Int_yymsg_alloc = sizeof Int_yymsgbuf;
#endif

#define YYPOPSTACK(N)   (Int_yyvsp -= (N), Int_yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int Int_yylen = 0;

  Int_yytoken = 0;
  Int_yyss = Int_yyssa;
  Int_yyvs = Int_yyvsa;
  Int_yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  Int_yystate = 0;
  Int_yyerrstatus = 0;
  Int_yynerrs = 0;
  Int_yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  Int_yyssp = Int_yyss;
  Int_yyvsp = Int_yyvs;

  goto Int_yysetstate;

/*------------------------------------------------------------.
| Int_yynewstate -- Push a new state, which is found in Int_yystate.  |
`------------------------------------------------------------*/
 Int_yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  Int_yyssp++;

 Int_yysetstate:
  *Int_yyssp = Int_yystate;

  if (Int_yyss + Int_yystacksize - 1 <= Int_yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T Int_yysize = Int_yyssp - Int_yyss + 1;

#ifdef Int_yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *Int_yyvs1 = Int_yyvs;
	Int_yytype_int16 *Int_yyss1 = Int_yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if Int_yyoverflow is a macro.  */
	Int_yyoverflow (YY_("memory exhausted"),
		    &Int_yyss1, Int_yysize * sizeof (*Int_yyssp),
		    &Int_yyvs1, Int_yysize * sizeof (*Int_yyvsp),
		    &Int_yystacksize);

	Int_yyss = Int_yyss1;
	Int_yyvs = Int_yyvs1;
      }
#else /* no Int_yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto Int_yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= Int_yystacksize)
	goto Int_yyexhaustedlab;
      Int_yystacksize *= 2;
      if (YYMAXDEPTH < Int_yystacksize)
	Int_yystacksize = YYMAXDEPTH;

      {
	Int_yytype_int16 *Int_yyss1 = Int_yyss;
	union Int_yyalloc *Int_yyptr =
	  (union Int_yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (Int_yystacksize));
	if (! Int_yyptr)
	  goto Int_yyexhaustedlab;
	YYSTACK_RELOCATE (Int_yyss_alloc, Int_yyss);
	YYSTACK_RELOCATE (Int_yyvs_alloc, Int_yyvs);
#  undef YYSTACK_RELOCATE
	if (Int_yyss1 != Int_yyssa)
	  YYSTACK_FREE (Int_yyss1);
      }
# endif
#endif /* no Int_yyoverflow */

      Int_yyssp = Int_yyss + Int_yysize - 1;
      Int_yyvsp = Int_yyvs + Int_yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) Int_yystacksize));

      if (Int_yyss + Int_yystacksize - 1 <= Int_yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", Int_yystate));

  if (Int_yystate == YYFINAL)
    YYACCEPT;

  goto Int_yybackup;

/*-----------.
| Int_yybackup.  |
`-----------*/
Int_yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  Int_yyn = Int_yypact[Int_yystate];
  if (Int_yypact_value_is_default (Int_yyn))
    goto Int_yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (Int_yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      Int_yychar = YYLEX;
    }

  if (Int_yychar <= YYEOF)
    {
      Int_yychar = Int_yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      Int_yytoken = YYTRANSLATE (Int_yychar);
      YY_SYMBOL_PRINT ("Next token is", Int_yytoken, &Int_yylval, &Int_yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  Int_yyn += Int_yytoken;
  if (Int_yyn < 0 || YYLAST < Int_yyn || Int_yycheck[Int_yyn] != Int_yytoken)
    goto Int_yydefault;
  Int_yyn = Int_yytable[Int_yyn];
  if (Int_yyn <= 0)
    {
      if (Int_yytable_value_is_error (Int_yyn))
        goto Int_yyerrlab;
      Int_yyn = -Int_yyn;
      goto Int_yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (Int_yyerrstatus)
    Int_yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", Int_yytoken, &Int_yylval, &Int_yylloc);

  /* Discard the shifted token.  */
  Int_yychar = YYEMPTY;

  Int_yystate = Int_yyn;
  *++Int_yyvsp = Int_yylval;

  goto Int_yynewstate;


/*-----------------------------------------------------------.
| Int_yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
Int_yydefault:
  Int_yyn = Int_yydefact[Int_yystate];
  if (Int_yyn == 0)
    goto Int_yyerrlab;
  goto Int_yyreduce;


/*-----------------------------.
| Int_yyreduce -- Do a reduction.  |
`-----------------------------*/
Int_yyreduce:
  /* Int_yyn is the number of a rule to reduce with.  */
  Int_yylen = Int_yyr2[Int_yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  Int_yyval = Int_yyvsp[1-Int_yylen];


  YY_REDUCE_PRINT (Int_yyn);
  switch (Int_yyn)
    {
        case 7:

/* Line 1806 of yacc.c  */
#line 39 "/home/jim/source_code/my_postgres95/src/backend/bootstrap/bootparse.y"
    {
  DO_START;
  boot_openrel(LexIDStr((Int_yyvsp[(2) - (2)].ival)));
  DO_END;
}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 46 "/home/jim/source_code/my_postgres95/src/backend/bootstrap/bootparse.y"
    {(Int_yyval.ival)=Int_yylval.ival;}
    break;



/* Line 1806 of yacc.c  */
#line 1375 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter Int_yychar, and that requires
     that Int_yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of Int_yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering Int_yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", Int_yyr1[Int_yyn], &Int_yyval, &Int_yyloc);

  YYPOPSTACK (Int_yylen);
  Int_yylen = 0;
  YY_STACK_PRINT (Int_yyss, Int_yyssp);

  *++Int_yyvsp = Int_yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  Int_yyn = Int_yyr1[Int_yyn];

  Int_yystate = Int_yypgoto[Int_yyn - YYNTOKENS] + *Int_yyssp;
  if (0 <= Int_yystate && Int_yystate <= YYLAST && Int_yycheck[Int_yystate] == *Int_yyssp)
    Int_yystate = Int_yytable[Int_yystate];
  else
    Int_yystate = Int_yydefgoto[Int_yyn - YYNTOKENS];

  goto Int_yynewstate;


/*------------------------------------.
| Int_yyerrlab -- here on detecting error |
`------------------------------------*/
Int_yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  Int_yytoken = Int_yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (Int_yychar);

  /* If not already recovering from an error, report this error.  */
  if (!Int_yyerrstatus)
    {
      ++Int_yynerrs;
#if ! YYERROR_VERBOSE
      Int_yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR Int_yysyntax_error (&Int_yymsg_alloc, &Int_yymsg, \
                                        Int_yyssp, Int_yytoken)
      {
        char const *Int_yymsgp = YY_("syntax error");
        int Int_yysyntax_error_status;
        Int_yysyntax_error_status = YYSYNTAX_ERROR;
        if (Int_yysyntax_error_status == 0)
          Int_yymsgp = Int_yymsg;
        else if (Int_yysyntax_error_status == 1)
          {
            if (Int_yymsg != Int_yymsgbuf)
              YYSTACK_FREE (Int_yymsg);
            Int_yymsg = (char *) YYSTACK_ALLOC (Int_yymsg_alloc);
            if (!Int_yymsg)
              {
                Int_yymsg = Int_yymsgbuf;
                Int_yymsg_alloc = sizeof Int_yymsgbuf;
                Int_yysyntax_error_status = 2;
              }
            else
              {
                Int_yysyntax_error_status = YYSYNTAX_ERROR;
                Int_yymsgp = Int_yymsg;
              }
          }
        Int_yyerror (Int_yymsgp);
        if (Int_yysyntax_error_status == 2)
          goto Int_yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (Int_yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (Int_yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (Int_yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  Int_yydestruct ("Error: discarding",
		      Int_yytoken, &Int_yylval);
	  Int_yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto Int_yyerrlab1;


/*---------------------------------------------------.
| Int_yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
Int_yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label Int_yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto Int_yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (Int_yylen);
  Int_yylen = 0;
  YY_STACK_PRINT (Int_yyss, Int_yyssp);
  Int_yystate = *Int_yyssp;
  goto Int_yyerrlab1;


/*-------------------------------------------------------------.
| Int_yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
Int_yyerrlab1:
  Int_yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      Int_yyn = Int_yypact[Int_yystate];
      if (!Int_yypact_value_is_default (Int_yyn))
	{
	  Int_yyn += YYTERROR;
	  if (0 <= Int_yyn && Int_yyn <= YYLAST && Int_yycheck[Int_yyn] == YYTERROR)
	    {
	      Int_yyn = Int_yytable[Int_yyn];
	      if (0 < Int_yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (Int_yyssp == Int_yyss)
	YYABORT;


      Int_yydestruct ("Error: popping",
		  Int_yystos[Int_yystate], Int_yyvsp);
      YYPOPSTACK (1);
      Int_yystate = *Int_yyssp;
      YY_STACK_PRINT (Int_yyss, Int_yyssp);
    }

  *++Int_yyvsp = Int_yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", Int_yystos[Int_yyn], Int_yyvsp, Int_yylsp);

  Int_yystate = Int_yyn;
  goto Int_yynewstate;


/*-------------------------------------.
| Int_yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
Int_yyacceptlab:
  Int_yyresult = 0;
  goto Int_yyreturn;

/*-----------------------------------.
| Int_yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
Int_yyabortlab:
  Int_yyresult = 1;
  goto Int_yyreturn;

#if !defined(Int_yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| Int_yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
Int_yyexhaustedlab:
  Int_yyerror (YY_("memory exhausted"));
  Int_yyresult = 2;
  /* Fall through.  */
#endif

Int_yyreturn:
  if (Int_yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      Int_yytoken = YYTRANSLATE (Int_yychar);
      Int_yydestruct ("Cleanup: discarding lookahead",
                  Int_yytoken, &Int_yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (Int_yylen);
  YY_STACK_PRINT (Int_yyss, Int_yyssp);
  while (Int_yyssp != Int_yyss)
    {
      Int_yydestruct ("Cleanup: popping",
		  Int_yystos[*Int_yyssp], Int_yyvsp);
      YYPOPSTACK (1);
    }
#ifndef Int_yyoverflow
  if (Int_yyss != Int_yyssa)
    YYSTACK_FREE (Int_yyss);
#endif
#if YYERROR_VERBOSE
  if (Int_yymsg != Int_yymsgbuf)
    YYSTACK_FREE (Int_yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (Int_yyresult);
}



/* Line 2067 of yacc.c  */
#line 50 "/home/jim/source_code/my_postgres95/src/backend/bootstrap/bootparse.y"


