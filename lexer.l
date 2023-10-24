%{

#include "parser.tab.h" // Archivo de encabezado generado por Bison
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

%}

%option noyywrap

%%

"var"               { printf("\n VAR (%s)", yytext); }
"int"               { printf("\n INT (%s)", yytext); }
"float"             { printf("\n FLOAT (%s)", yytext); }
"bool"              { printf("\n BOOL (%s)", yytext); }
"string"            { printf("\n STRING (%s)", yytext); }
(m|km|cm|s|min|h|kg) {  printf("\n UNIDAD (%s)", yytext); }
"+"  { printf("\n PLUS (%s)", yytext); }
"-"  { printf("\n MINUS (%s)", yytext); }
"*"  { printf("\n MULTIPLY (%s)", yytext); }
"/"  { printf("\n DIVIDE (%s)", yytext); }
"<"  { printf("\n LESS_THAN (%s)", yytext); }
">"  { printf("\n GREATER_THAN (%s)", yytext); }
"<=" { printf("\n LESS_THAN_OR_EQUAL (%s)", yytext); }
">=" { printf("\n GREATER_THAN_OR_EQUAL (%s)", yytext);  }
"==" { printf("\n EQUAL (%s)", yytext);  }
"=" { printf("\n ASIGNACION (%s)", yytext);  }
"!=" { printf("\n NOT_EQUAL (%s)", yytext);  }
"&&" { printf("\n LOGICAL_AND (%s)", yytext);  }
"||" { printf("\n LOGICAL_OR (%s)", yytext);  }
"!"  { printf("\n LOGICAL_NOT (%s)", yytext);  }

\"([^\\\"]|\\\\.)*\"       {  printf("\n STRING (%s)", yytext); }

"CONVERTIR"         { printf("\n CONVERTIR (%s)", yytext); }

"(" { printf("\n LPARENT (%s)", yytext); } // Reconoce el paréntesis izquierdo
")" { printf("\n RPARENT (%s)", yytext); } // Reconoce el paréntesis derecho
"[" { printf("\n LBRACE (%s)", yytext); }
"]" { printf("\n RBRACE (%s)", yytext); }
";" { printf("\n SEMICOLON (%s)", yytext); }

"para"  { printf("\n PARA (%s)", yytext); }
"si" { printf("\n SI (%s)", yytext); }
"sino" { printf("\n SINO (%s)", yytext); }
"mientras" { printf("\n MIENTRAS (%s)", yytext);}
"print" { printf("\n PRINT (%s)", yytext); }

[0-9]+\.[0-9]+      {  printf("\n REAL (%s)", yytext); } // Números reales
[0-9]+              {  printf("\n NUMBER (%s)", yytext); } // Números enteros

[a-zA-Z][a-zA-Z0-9]* { printf("\n IDENTIFIER (%s)", yytext); }

"//".*              ; // Comentario de una línea
"\/\*".*"\*\/"      ; // Comentario multilínea

[ \t\n]             ; // Ignorar espacios en blanco y saltos de línea
.                   { fprintf(stderr, "Error: Carácter no válido: %s\n", yytext); }

%%

int main() {
    // Inicializa el analizador léxico
    yylex();

    return 0;
}