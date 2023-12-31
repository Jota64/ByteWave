
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


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void yyerror(const char *s);
int yylex(void);

std::map<std::string, std::vector<std::string>> units;
std::map<std::string, std::string> categories;
std::map<std::string, double> conversiones;

void inicializa(){

    units["Longitud"] = {"m", "km", "cm", "mm", "pm", "nm", "mi", "yd", "ft", "in"};
    units["Masa"] = {"kg", "g", "mg", "µg", "t", "lb", "oz"};
    units["Volumen"] = {"m3", "L", "mL", "gal", "qt", "pt", "floz"};
    units["Tiempo"] = {"s", "min", "h", " d", "wk", "mo", "yr"};
    units["Temperatura"] = {"gC", "gF", "K"};
    units["Area"] = {"m2", "km2", "ha", "ac", "mi2", "yd2", "ft2", "in2"};
    units["Velocidad"] = {"ms", "kmh", "mph", "kt"};

    // Creamos un nuevo map donde la clave es una string (la unidad de medida)
    // y el valor es una string (la categoría de la unidad de medida)

    for (auto &category : units){
        for (auto &unit : category.second){
            categories[unit] = category.first;
        }
    }

    conversiones = {
    {"m", 1.0},
    {"km", 1000.0},
    {"cm", 0.01},
    {"mm", 0.001},
    {"pm", 1e-6},
    {"nm", 1e-9},
    {"mi", 1609.34},
    {"yd", 0.9144},
    {"ft", 0.3048},
    {"in", 0.0254},
    {"s", 1.0},
    {"min", 60.0},
    {"h", 3600.0},
    {"d", 86400.0},
    {"wk", 604800.0},
    {"mo", 2628000.0},
    {"yr", 31536000.0},
    {"kg", 1.0},
    {"g", 0.001},
    {"mg", 1e-6},
    {"pg", 1e-9},
    {"t", 1000.0},
    {"lb", 0.453592},
    {"oz", 0.0283495}
    };
}

struct SymbolEntry {
    char *name;
    char *type;
    union {
        int valor_entero;
        float valor_real;
        char* str;
        int valor_bool;
    } value;
    string unit[2];
};

#define MAX_SYMBOLS 100
struct SymbolEntry symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

int findSymbol(char *name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return i; // La variable ya existe en la tabla de símbolos.
        }
    }
    return -1; // La variable no existe en la tabla de símbolos.
}

void convertUnit(char* nameVar, char* unitDest){
    int index = findSymbol(nameVar);
    
    if(index == -1){
        yyerror("La variable no se encuentra declarada");
        exit(1);
    }else{
        string type = symbolTable[index].type;
        string unidadOrigen = symbolTable[index].unit[1];
        if(categories[unidadOrigen] == categories[unitDest] ){
            float value;
            if(type == "int"){
                value = symbolTable[index].value.valor_entero;
            }else if(type == "float"){
                value = symbolTable[index].value.valor_real;
            }

            double valorEnBase = value * conversiones[unidadOrigen];
            double valorConvertido = valorEnBase / conversiones[unitDest];
            symbolTable[index].unit[1]=unitDest;
            if(type == "int"){
                symbolTable[index].value.valor_entero = static_cast<int>(valorConvertido);
            }else if(type == "float"){
                symbolTable[index].value.valor_real = valorConvertido;
            }
        }else{
            yyerror("Las unidades no son consistentes.");
            exit(1);
        }

    }

}

int compareUnits(char* name1, char* name2){
    int index1 = findSymbol(name1);
    int index2 = findSymbol(name2);

    if(symbolTable[index1].unit[1] == symbolTable[index2].unit[1]){
        return 1;
    }else{
        return -1;
    }
}



/* Line 189 of yacc.c  */
#line 214 "parser.tab.c"

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
     MINUS = 258,
     PLUS = 259,
     DIVIDE = 260,
     MULTIPLY = 261,
     ASIGNACION = 262,
     GREATER_THAN_OR_EQUAL = 263,
     LESS_THAN_OR_EQUAL = 264,
     GREATER_THAN = 265,
     LESS_THAN = 266,
     NOT_EQUAL = 267,
     LOGICAL_AND = 268,
     LOGICAL_OR = 269,
     LOGICAL_NOT = 270,
     EQUAL = 271,
     NUMBER = 272,
     REAL = 273,
     V_BOOL = 274,
     V_STRING = 275,
     IDENTIFIER = 276,
     VAR = 277,
     LPAREN = 278,
     RPAREN = 279,
     LCURLYBR = 280,
     RCURLYBR = 281,
     SEMICOLON = 282,
     PARA = 283,
     SI = 284,
     SINO = 285,
     MIENTRAS = 286,
     PRINT = 287,
     COMMA = 288,
     CONVERTIR = 289,
     UNIDAD = 290,
     INT = 291,
     FLOAT = 292,
     BOOL = 293,
     STRING = 294
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 151 "parser.y"

  int valor_entero;
  float valor_real;
  char *str;
  int valor_bool;
  



/* Line 214 of yacc.c  */
#line 299 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 311 "parser.tab.c"

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
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   292

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNRULES -- Number of states.  */
#define YYNSTATES  182

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    13,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    40,    42,    44,
      46,    48,    53,    58,    63,    68,    78,    80,    82,    84,
      86,    92,    98,   106,   120,   128,   135,   142,   149,   156,
     163,   170,   177,   184,   191,   198,   205,   212,   219,   226,
     233,   240,   245,   249,   253,   257,   261,   265,   269,   273,
     277,   281,   285,   289,   292,   296,   298,   300,   302,   304,
     309,   311,   316,   328,   330,   332
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    -1,    43,    -1,    42,    43,    -1,
      42,    60,    -1,    42,    61,    -1,    44,    -1,    46,    -1,
      51,    -1,    52,    -1,    53,    -1,    54,    -1,    55,    -1,
      56,    -1,    57,    -1,    22,    21,    45,    35,    27,    -1,
      36,    -1,    37,    -1,    38,    -1,    39,    -1,    21,     7,
      47,    27,    -1,    21,     7,    48,    27,    -1,    21,     7,
      49,    27,    -1,    21,     7,    50,    27,    -1,    21,     7,
      34,    23,    21,    33,    35,    24,    27,    -1,    17,    -1,
      18,    -1,    20,    -1,    19,    -1,    32,    23,    21,    24,
      27,    -1,    32,    23,    49,    24,    27,    -1,    29,    23,
      58,    24,    25,    42,    26,    -1,    29,    23,    21,    10,
      47,    24,    25,    42,    26,    30,    25,    42,    26,    -1,
      31,    23,    58,    24,    25,    42,    26,    -1,    21,     7,
      47,     4,    47,    27,    -1,    21,     7,    47,     4,    48,
      27,    -1,    21,     7,    48,     4,    47,    27,    -1,    21,
       7,    48,     4,    48,    27,    -1,    21,     7,    47,     3,
      47,    27,    -1,    21,     7,    47,     3,    48,    27,    -1,
      21,     7,    48,     3,    47,    27,    -1,    21,     7,    48,
       3,    48,    27,    -1,    21,     7,    47,     6,    47,    27,
      -1,    21,     7,    47,     6,    48,    27,    -1,    21,     7,
      48,     6,    47,    27,    -1,    21,     7,    48,     6,    48,
      27,    -1,    21,     7,    47,     5,    47,    27,    -1,    21,
       7,    47,     5,    48,    27,    -1,    21,     7,    48,     5,
      47,    27,    -1,    21,     7,    48,     5,    48,    27,    -1,
      47,     4,    47,    27,    -1,    58,     3,    58,    -1,    58,
       6,    58,    -1,    58,     5,    58,    -1,    58,     7,    58,
      -1,    58,    11,    58,    -1,    21,    10,    47,    -1,    58,
       9,    58,    -1,    58,     8,    58,    -1,    58,    12,    58,
      -1,    58,    13,    58,    -1,    58,    14,    58,    -1,    58,
      15,    -1,    23,    58,    24,    -1,    59,    -1,    17,    -1,
      18,    -1,    39,    -1,    32,    23,    58,    24,    -1,    21,
      -1,    21,     4,     4,    27,    -1,    28,    23,    62,    27,
      63,    27,    64,    24,    25,    42,    26,    -1,    46,    -1,
      58,    -1,    60,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   181,   181,   185,   186,   187,   188,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   204,   234,   235,   236,
     237,   242,   262,   282,   302,   322,   329,   332,   335,   338,
     342,   376,   385,   388,   394,   399,   408,   417,   426,   437,
     446,   455,   464,   475,   484,   493,   502,   513,   522,   531,
     540,   557,   558,   559,   560,   561,   562,   563,   566,   567,
     568,   569,   570,   571,   573,   574,   575,   576,   577,   578,
     582,   586,   604,   611,   615,   619
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MINUS", "PLUS", "DIVIDE", "MULTIPLY",
  "ASIGNACION", "GREATER_THAN_OR_EQUAL", "LESS_THAN_OR_EQUAL",
  "GREATER_THAN", "LESS_THAN", "NOT_EQUAL", "LOGICAL_AND", "LOGICAL_OR",
  "LOGICAL_NOT", "EQUAL", "NUMBER", "REAL", "V_BOOL", "V_STRING",
  "IDENTIFIER", "VAR", "LPAREN", "RPAREN", "LCURLYBR", "RCURLYBR",
  "SEMICOLON", "PARA", "SI", "SINO", "MIENTRAS", "PRINT", "COMMA",
  "CONVERTIR", "UNIDAD", "INT", "FLOAT", "BOOL", "STRING", "$accept",
  "program", "statements", "statement", "var_declaration", "type",
  "assignment_statement", "expr_int", "expr_float", "expr_string",
  "expr_bool", "print_statement", "if_statement", "while_statement",
  "plus_statement", "minus_statement", "multiply_statement",
  "divide_statement", "expr", "expr_id", "increment_statement",
  "for_statement", "for_init", "for_condition", "for_update", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    42,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    45,    45,    45,
      45,    46,    46,    46,    46,    46,    47,    48,    49,    50,
      51,    51,    52,    52,    53,    54,    54,    54,    54,    55,
      55,    55,    55,    56,    56,    56,    56,    57,    57,    57,
      57,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      59,    60,    61,    62,    63,    64
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     1,     1,     1,
       1,     4,     4,     4,     4,     9,     1,     1,     1,     1,
       5,     5,     7,    13,     7,     6,     6,     6,     6,     6,
       6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
       6,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     1,     1,     1,     1,     4,
       1,     4,    11,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     2,     3,     7,
       8,     9,    10,    11,    12,    13,    14,    15,     0,     0,
       0,     0,     0,     1,     0,     0,     4,     5,     6,    26,
      27,    29,    28,     0,     0,     0,     0,     0,    17,    18,
      19,    20,     0,    66,    67,    70,     0,     0,    68,     0,
       0,    65,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,     0,    22,    23,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,     0,     0,     0,
       0,     0,     0,     0,    73,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    16,    57,    64,     0,     0,    52,    54,
      53,    55,    59,    58,    56,    60,    61,    62,     0,    57,
       0,    30,    31,    71,     0,     0,     0,    39,    40,    35,
      36,    47,    48,    43,    44,    41,    42,    37,    38,    49,
      50,    45,    46,     0,    69,    51,     0,     0,     0,     0,
      74,     0,     0,     0,    32,    34,     0,     0,     0,     0,
      75,     0,    25,     0,     0,     0,     0,     0,     0,     0,
      72,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    42,    10,    49,    35,    36,
      37,    11,    12,    13,    14,    15,    16,    17,    50,    51,
      27,    28,    95,   161,   171
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -104
static const yytype_int16 yypact[] =
{
     240,    17,     7,    18,    33,    34,    32,    64,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,     2,    15,
      58,    66,     9,  -104,    19,    49,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,    55,     8,    12,    13,    53,  -104,  -104,
    -104,  -104,    11,    78,  -104,    81,    66,    65,  -104,    90,
     101,  -104,    93,   121,    94,    95,   107,   100,   102,    16,
      16,    16,    16,  -104,    16,    16,    16,    16,  -104,  -104,
    -104,   104,   105,   151,    66,   105,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,  -104,   114,   105,   122,
     119,   124,   125,   141,  -104,   126,   134,   128,   142,   143,
     146,   154,   160,   162,   176,   177,   178,   183,   188,   189,
     190,   195,   200,  -104,   144,  -104,   171,   201,   268,   277,
     277,   277,   129,   129,   129,    87,    23,   214,   240,  -104,
     240,  -104,  -104,  -104,     2,    66,   172,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,   194,  -104,  -104,   180,   192,   207,   212,
     185,   213,   217,   240,  -104,  -104,   210,   219,   204,   239,
    -104,   227,  -104,   222,   230,   233,   240,   240,   216,   228,
    -104,  -104
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -104,  -104,  -103,    -7,  -104,  -104,   196,   -17,   -57,   241,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,   -15,  -104,
      98,  -104,  -104,  -104,  -104
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -27
static const yytype_int16 yytable[] =
{
      26,    34,    98,   100,   102,   104,    53,   106,   108,   110,
     112,    59,    60,    61,    62,    64,    65,    66,    67,    29,
      30,    31,    32,    56,    18,   156,    18,   157,    19,    32,
      54,    73,    23,    29,    30,    63,    33,    85,    86,    68,
      69,    20,    97,    99,   101,   103,    71,   105,   107,   109,
     111,    38,    39,    40,    41,   114,    21,    22,   117,   116,
     168,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   129,    57,   178,   179,    43,    44,   159,    58,    45,
      70,    46,   -26,    43,    44,    24,     2,    52,    74,    46,
      47,    72,    25,     3,    75,     4,     5,    48,    47,   -27,
      84,    85,    86,    88,    76,    48,    77,    78,    79,    80,
      81,    92,    82,    83,    84,    85,    86,   158,    90,    91,
     160,    93,    29,    96,    76,    87,    77,    78,    79,    80,
      81,   113,    82,    83,    84,    85,    86,   -27,   -27,   128,
     -27,    83,    84,    85,    86,    89,   131,   130,   134,    26,
      26,   132,   133,   135,    76,   137,    77,    78,    79,    80,
      81,    26,    82,    83,    84,    85,    86,   136,   153,   138,
     139,    26,    26,   140,    76,   115,    77,    78,    79,    80,
      81,   141,    82,    83,    84,    85,    86,   142,    76,   143,
      77,    78,    79,    80,    81,   154,    82,    83,    84,    85,
      86,    24,     2,   144,   145,   146,   164,   162,    25,     3,
     147,     4,     5,    24,     2,   148,   149,   150,   165,   163,
      25,     3,   151,     4,     5,    24,     2,   152,   155,    86,
     173,   169,    25,     3,    63,     4,     5,    24,     2,    68,
     166,   167,   180,    56,    25,     3,   172,     4,     5,    24,
       2,   174,   175,    94,   181,   176,    25,     3,   177,     4,
       5,     1,     2,    55,   170,     0,     0,     0,     0,     3,
       0,     4,     5,    77,    78,    79,    80,    81,     0,    82,
      83,    84,    85,    86,    79,    80,    81,     0,    82,    83,
      84,    85,    86
};

static const yytype_int16 yycheck[] =
{
       7,    18,    59,    60,    61,    62,    21,    64,    65,    66,
      67,     3,     4,     5,     6,     3,     4,     5,     6,    17,
      18,    19,    20,     4,     7,   128,     7,   130,    21,    20,
      21,    46,     0,    17,    18,    27,    34,    14,    15,    27,
      27,    23,    59,    60,    61,    62,    35,    64,    65,    66,
      67,    36,    37,    38,    39,    72,    23,    23,    75,    74,
     163,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    88,    23,   176,   177,    17,    18,   134,    23,    21,
      27,    23,     4,    17,    18,    21,    22,    21,    23,    23,
      32,    10,    28,    29,     4,    31,    32,    39,    32,    12,
      13,    14,    15,    10,     3,    39,     5,     6,     7,     8,
       9,     4,    11,    12,    13,    14,    15,   134,    24,    24,
     135,    21,    17,    21,     3,    24,     5,     6,     7,     8,
       9,    27,    11,    12,    13,    14,    15,     8,     9,    25,
      11,    12,    13,    14,    15,    24,    27,    25,     7,   156,
     157,    27,    27,    27,     3,    27,     5,     6,     7,     8,
       9,   168,    11,    12,    13,    14,    15,    33,    24,    27,
      27,   178,   179,    27,     3,    24,     5,     6,     7,     8,
       9,    27,    11,    12,    13,    14,    15,    27,     3,    27,
       5,     6,     7,     8,     9,    24,    11,    12,    13,    14,
      15,    21,    22,    27,    27,    27,    26,    35,    28,    29,
      27,    31,    32,    21,    22,    27,    27,    27,    26,    25,
      28,    29,    27,    31,    32,    21,    22,    27,    27,    15,
      26,    21,    28,    29,    27,    31,    32,    21,    22,    27,
      27,    24,    26,     4,    28,    29,    27,    31,    32,    21,
      22,    24,    30,    57,    26,    25,    28,    29,    25,    31,
      32,    21,    22,    22,   166,    -1,    -1,    -1,    -1,    29,
      -1,    31,    32,     5,     6,     7,     8,     9,    -1,    11,
      12,    13,    14,    15,     7,     8,     9,    -1,    11,    12,
      13,    14,    15
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    22,    29,    31,    32,    41,    42,    43,    44,
      46,    51,    52,    53,    54,    55,    56,    57,     7,    21,
      23,    23,    23,     0,    21,    28,    43,    60,    61,    17,
      18,    19,    20,    34,    47,    48,    49,    50,    36,    37,
      38,    39,    45,    17,    18,    21,    23,    32,    39,    47,
      58,    59,    21,    58,    21,    49,     4,    23,    23,     3,
       4,     5,     6,    27,     3,     4,     5,     6,    27,    27,
      27,    35,    10,    58,    23,     4,     3,     5,     6,     7,
       8,     9,    11,    12,    13,    14,    15,    24,    10,    24,
      24,    24,     4,    21,    46,    62,    21,    47,    48,    47,
      48,    47,    48,    47,    48,    47,    48,    47,    48,    47,
      48,    47,    48,    27,    47,    24,    58,    47,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    25,    47,
      25,    27,    27,    27,     7,    27,    33,    27,    27,    27,
      27,    27,    27,    27,    27,    27,    27,    27,    27,    27,
      27,    27,    27,    24,    24,    27,    42,    42,    47,    48,
      58,    63,    35,    25,    26,    26,    27,    24,    42,    21,
      60,    64,    27,    26,    24,    30,    25,    25,    42,    42,
      26,    26
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
        case 16:

/* Line 1455 of yacc.c  */
#line 205 "parser.y"
    { 
        int index = findSymbol((yyvsp[(2) - (5)].str));
        if(index == -1){
            if(symbolCount<MAX_SYMBOLS){
                symbolTable[symbolCount].name = strdup((yyvsp[(2) - (5)].str));
                symbolTable[symbolCount].type = strdup((yyvsp[(3) - (5)].str));
                string unidad = (yyvsp[(4) - (5)].str);
                if(categories.count((yyvsp[(4) - (5)].str))>0){
                    string categorySet = categories[(yyvsp[(4) - (5)].str)];

                    symbolTable[symbolCount].unit[0] = categorySet;
                    symbolTable[symbolCount].unit[1] = strdup((yyvsp[(4) - (5)].str));
                }else{
                    symbolTable[symbolCount].unit[0] = "unit";
                    symbolTable[symbolCount].unit[1] = "unit";
                }
                symbolCount++;
            } else {
                yyerror("La tabla de simbolos esta llena");
                exit(1);
            }
        } else {
            yyerror("La variable ya existe");
            exit(1);
        }
    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 243 "parser.y"
    { 
        int index = findSymbol((yyvsp[(1) - (4)].str));
        if(index == -1){
            if(symbolCount<MAX_SYMBOLS){
                symbolTable[symbolCount].name = strdup((yyvsp[(1) - (4)].str));
                symbolTable[symbolCount].type = "int";
                symbolTable[symbolCount].value.valor_entero = (yyvsp[(3) - (4)].valor_entero);
                symbolTable[symbolCount].unit[0] = "unit";
                symbolTable[symbolCount].unit[1] = "unit";
                symbolCount++;
            } else {
                yyerror("La tabla de simbolos esta llena");
                exit(1);
            }
        } else {
            symbolTable[index].value.valor_entero = (yyvsp[(3) - (4)].valor_entero);
        }
    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 263 "parser.y"
    { 
            int index = findSymbol((yyvsp[(1) - (4)].str));
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup((yyvsp[(1) - (4)].str));
                    symbolTable[symbolCount].type = "float";
                    symbolTable[symbolCount].value.valor_real = (yyvsp[(3) - (4)].valor_real);
                    symbolTable[symbolCount].unit[0] = "unit";
                    symbolTable[symbolCount].unit[1] = "unit";
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[index].value.valor_real = (yyvsp[(3) - (4)].valor_real);
            }
        ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 283 "parser.y"
    { 
            int index = findSymbol((yyvsp[(1) - (4)].str));
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup((yyvsp[(1) - (4)].str));
                    symbolTable[symbolCount].type = "string";
                    symbolTable[symbolCount].value.str = (yyvsp[(3) - (4)].str);
                    symbolTable[symbolCount].unit[0] = "unit";
                    symbolTable[symbolCount].unit[1] = "unit";
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[index].value.str = (yyvsp[(3) - (4)].str);
            }
        ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 303 "parser.y"
    { 
            int index = findSymbol((yyvsp[(1) - (4)].str));
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup((yyvsp[(1) - (4)].str));
                    symbolTable[symbolCount].type = "bool";
                    symbolTable[symbolCount].value.valor_bool = (yyvsp[(3) - (4)].valor_bool);
                    symbolTable[symbolCount].unit[0] = "unit";
                    symbolTable[symbolCount].unit[1] = "unit";
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[index].value.valor_bool = (yyvsp[(3) - (4)].valor_bool);
            }
        ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 323 "parser.y"
    {
        convertUnit((yyvsp[(5) - (9)].str),(yyvsp[(7) - (9)].str));
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 329 "parser.y"
    {(yyval.valor_entero) = (yyvsp[(1) - (1)].valor_entero);}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 332 "parser.y"
    {(yyval.valor_real) = (yyvsp[(1) - (1)].valor_real);}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 335 "parser.y"
    {(yyval.str) = (yyvsp[(1) - (1)].str);}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 338 "parser.y"
    {(yyval.valor_bool) = (yyvsp[(1) - (1)].valor_bool);}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 343 "parser.y"
    {
        int index = findSymbol((yyvsp[(3) - (5)].str));
        if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            char* tipo = symbolTable[index].type;
            if(strcmp(tipo,"int") == 0){
                int value = symbolTable[index].value.valor_entero;
                string categoryUnit = symbolTable[index].unit[0];
                string unitCategory = symbolTable[index].unit[1];
                cout << categoryUnit << " " << (yyvsp[(3) - (5)].str) << ": " << value << unitCategory << endl;
            }
            if(strcmp(tipo,"float") == 0){
                float value = symbolTable[index].value.valor_real;
                string categoryUnit = symbolTable[index].unit[0];
                string unitCategory = symbolTable[index].unit[1];
                cout << categoryUnit << " " << (yyvsp[(3) - (5)].str) << ": " << value << unitCategory << endl;
            }
            if(strcmp(tipo,"bool") == 0){
                int value = symbolTable[index].value.valor_bool;
                string categoryUnit = symbolTable[index].unit[0];
                string unitCategory = symbolTable[index].unit[1];
                cout << categoryUnit << " " << (yyvsp[(3) - (5)].str) << ": " << (value ? "false" : "true") << unitCategory << endl;
            }
            if(strcmp(tipo,"string") == 0){
                char* value = symbolTable[index].value.str;
                string categoryUnit = symbolTable[index].unit[0];
                string unitCategory = symbolTable[index].unit[1];
                cout << categoryUnit << " " << (yyvsp[(3) - (5)].str) << ": " << value << endl;
            }
        }
    ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 377 "parser.y"
    {
        string printText = (yyvsp[(3) - (5)].str);
        replace(printText.begin(), printText.end(), '"', ' ');
        cout << printText << endl;
    ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 385 "parser.y"
    {
        cout << "hola 1" << endl;
    ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 388 "parser.y"
    {
        cout << "hola 2" << endl;
    ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 399 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_entero = (yyvsp[(3) - (6)].valor_entero)+(yyvsp[(5) - (6)].valor_entero);
        }
    ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 408 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_entero)+(yyvsp[(5) - (6)].valor_real);
        }
    ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 417 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_real)+(yyvsp[(5) - (6)].valor_entero);
        }
    ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 426 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_real)+(yyvsp[(5) - (6)].valor_real);
        }
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 437 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_entero = (yyvsp[(3) - (6)].valor_entero)-(yyvsp[(5) - (6)].valor_entero);
        }
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 446 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_entero)-(yyvsp[(5) - (6)].valor_real);
        }
    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 455 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_real)-(yyvsp[(5) - (6)].valor_entero);
        }
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 464 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_real)-(yyvsp[(5) - (6)].valor_real);
        }
    ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 475 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_entero = (yyvsp[(3) - (6)].valor_entero)*(yyvsp[(5) - (6)].valor_entero);
        }
    ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 484 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_entero)*(yyvsp[(5) - (6)].valor_real);
        }
    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 493 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_real)*(yyvsp[(5) - (6)].valor_entero);
        }
    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 502 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_real)*(yyvsp[(5) - (6)].valor_real);
        }
    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 513 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_entero)/(yyvsp[(5) - (6)].valor_entero);
        }
    ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 522 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_entero)/(yyvsp[(5) - (6)].valor_real);
        }
    ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 531 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_real)/(yyvsp[(5) - (6)].valor_entero);
        }
    ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 540 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (6)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = (yyvsp[(3) - (6)].valor_real)/(yyvsp[(5) - (6)].valor_real);
        }
    ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 557 "parser.y"
    { printf("suma\n"); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 558 "parser.y"
    { printf("resta\n"); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 559 "parser.y"
    { printf("multiplicacion\n"); ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 560 "parser.y"
    { printf("division\n"); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 561 "parser.y"
    { printf("asignacion\n"); ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 562 "parser.y"
    { printf("menor-que\n"); ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 563 "parser.y"
    { 
        
        printf("expresion (mayor-que), %s, %i\n", (yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].valor_entero)); ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 566 "parser.y"
    { printf("menor_igual\n"); ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 567 "parser.y"
    { printf("mayor_igual\n"); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 568 "parser.y"
    { printf("diferente_a\n"); ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 569 "parser.y"
    { printf("and\n"); ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 570 "parser.y"
    { printf("or\n"); ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 571 "parser.y"
    { printf("not\n"); ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 578 "parser.y"
    { printf("Instrucción de impresión\n"); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 586 "parser.y"
    {
        int index = findSymbol((yyvsp[(1) - (4)].str));
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            char* tipo = symbolTable[index].type;
            if(strcmp(tipo,"int") == 0){
                symbolTable[index].value.valor_entero = symbolTable[index].value.valor_entero+1;
            }
            if(strcmp(tipo,"float") == 0){
                symbolTable[index].value.valor_real = symbolTable[index].value.valor_real+1;
            }
        }
    ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 605 "parser.y"
    {
        printf("Instrucción PARA con inicialización, condición y actualización\n");
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2286 "parser.tab.c"
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
#line 623 "parser.y"


void yyerror(const char *s) {
  fprintf(stderr, "Error sintáctico: %s\n", s);
}

int main(int argc, char **argv) {
  inicializa();
  yyparse();
  return 0;
}
