
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 152 "parser.y"

  int valor_entero;
  float valor_real;
  char *str;
  int valor_bool;
  



/* Line 1676 of yacc.c  */
#line 101 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


