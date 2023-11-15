%{

#include "parser.tab.h" // Archivo de encabezado generado por Bison
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

%}

%option noyywrap

%%

"var"               { return VAR; }
"int"               { yylval.str = strdup(yytext); return INT; }
"float"             { yylval.str = strdup(yytext); return FLOAT; }
"bool"              { yylval.str = strdup(yytext); return BOOL; }
"string"            { yylval.str = strdup(yytext); return STRING;}
(m|pm|km|cm|s|min|h|kg|mg|unit) { yylval.str = strdup(yytext); return UNIDAD; }

"+"  { return PLUS; }
"-"  { return MINUS; }
"*"  { return MULTIPLY; }
"/"  { return DIVIDE;}
"<"  { return LESS_THAN; }
">"  { return GREATER_THAN; }
"<=" { return LESS_THAN_OR_EQUAL;}
">=" { return GREATER_THAN_OR_EQUAL;}
"==" { return EQUAL; }
"=" { return ASIGNACION;}
"!=" { return NOT_EQUAL; }
"&&" { return LOGICAL_AND; }
"||" { return LOGICAL_OR; }
"!"  { return LOGICAL_NOT; }

\"([^\\\"]|\\\\.)*\"       {  yylval.str = strdup(yytext); return V_STRING; }

"CONVERTIR"         { return CONVERTIR;}

"(" { return LPAREN;} 
")" { return RPAREN;}
";" { return SEMICOLON; }
"," { return COMMA; }
"{" { return LCURLYBR; }
"}" { return RCURLYBR; }

"para"  { return PARA;}
"si" { return SI;}
"sino" { return SINO;}
"mientras" { return MIENTRAS;}
"print" { return PRINT;}

[0-9]+\.[0-9]+      {  yylval.valor_real = atof(yytext); return REAL; } // Números reales
[0-9]+              {  yylval.valor_entero = atoi(yytext); return NUMBER; } // Números enteros

"true" { yylval.valor_bool = 1; return V_BOOL; } // Reconoce el valor verdadero
"false" { yylval.valor_bool = 0; return V_BOOL; } // Reconoce el valor falso


[a-zA-Z][a-zA-Z0-9]* { yylval.str = strdup(yytext); return IDENTIFIER; }

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