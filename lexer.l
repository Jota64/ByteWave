%{

#include "parser.tab.h" // Archivo de encabezado generado por Bison
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

%}

%option noyywrap

%%

"var"               { printf("\n VAR (%s)", yytext); return VAR; }
"int"               { yylval.str = strdup(yytext); printf("\n INT (%s)", yytext);return INT; }
"float"             { yylval.str = strdup(yytext); printf("\n FLOAT (%s)", yytext);return FLOAT; }
"bool"              { yylval.str = strdup(yytext); printf("\n BOOL (%s)", yytext);return BOOL; }
"string"            { yylval.str = strdup(yytext); printf("\n STRING (%s)", yytext);return STRING;}
(m|km|cm|s|min|h|kg|unit) { printf("\n UNIDAD (%s)", yytext); yylval.str = strdup(yytext); return UNIDAD; }

"+"  { printf("\n PLUS (%s)", yytext); return PLUS; }
"-"  { printf("\n MINUS (%s)", yytext); return MINUS; }
"*"  { printf("\n MULTIPLY (%s)", yytext); return MULTIPLY; }
"/"  { printf("\n DIVIDE (%s)", yytext); return DIVIDE;}
"<"  { printf("\n LESS_THAN (%s)", yytext); return LESS_THAN; }
">"  { printf("\n GREATER_THAN (%s)", yytext);  return GREATER_THAN; }
"<=" { printf("\n LESS_THAN_OR_EQUAL (%s)", yytext);  return LESS_THAN_OR_EQUAL;}
">=" { printf("\n GREATER_THAN_OR_EQUAL (%s)", yytext); return GREATER_THAN_OR_EQUAL;}
"==" { printf("\n EQUAL (%s)", yytext); return EQUAL; }
"=" { printf("\n ASIGNACION (%s)", yytext);  return ASIGNACION;}
"!=" { printf("\n NOT_EQUAL (%s)", yytext);  return NOT_EQUAL; }
"&&" { printf("\n LOGICAL_AND (%s)", yytext);  return LOGICAL_AND; }
"||" { printf("\n LOGICAL_OR (%s)", yytext);  return LOGICAL_OR; }
"!"  { printf("\n LOGICAL_NOT (%s)", yytext);  return LOGICAL_NOT; }

\"([^\\\"]|\\\\.)*\"       {  yylval.str = strdup(yytext); return V_STRING; }

"CONVERTIR"         { printf("\n CONVERTIR (%s)", yytext);  return CONVERTIR;}

"(" { printf("\n LPARENT (%s)", yytext); return LPAREN;} 
")" { printf("\n RPARENT (%s)", yytext); return RPAREN;}
";" { printf("\n SEMICOLON (%s) \n", yytext); return SEMICOLON; }
"," { printf("\n COMMA (%s)", yytext); return COMMA; }
"{" { printf("\n LCURLYBR (%s)", yytext); return LCURLYBR; }
"}" { printf("\n RCURLYBR (%s)", yytext); return RCURLYBR; }

"para"  { printf("\n PARA (%s)", yytext);  return PARA;}
"si" { printf("\n SI (%s)", yytext); return SI;}
"sino" { printf("\n SINO (%s)", yytext);  return SINO;}
"mientras" { printf("\n MIENTRAS (%s)", yytext); return MIENTRAS;}
"print" { printf("\n PRINT (%s)", yytext);  return PRINT;}

[0-9]+\.[0-9]+      {  yylval.valor_real = atof(yytext); printf("\n REAL (%s)", yytext);return REAL; } // Números reales
[0-9]+              {  yylval.valor_entero = atoi(yytext); printf("\n NUMBER (%s)", yytext);return NUMBER; } // Números enteros

"true" { yylval.valor_bool = 1; printf("\n V_BOOL (%s)", yytext);return V_BOOL; } // Reconoce el valor verdadero
"false" { yylval.valor_bool = 0; printf("\n V_BOOL (%s)", yytext);return V_BOOL; } // Reconoce el valor falso


[a-zA-Z][a-zA-Z0-9]* { printf("\n IDENTIFIER (%s)", yytext); yylval.str = strdup(yytext); return IDENTIFIER; }

"//".*              ; // Comentario de una línea
"\/\*".*"\*\/"      ; // Comentario multilínea

[ \t\n]             ; // Ignorar espacios en blanco y saltos de línea
.                   { fprintf(stderr, "Error: Carácter no válido: %s\n", yytext); }

%%
/*
int main() {
    // Inicializa el analizador léxico
    yylex();

    return 0;
}*/