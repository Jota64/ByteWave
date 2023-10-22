%{

#include "parser.tab.h" // Archivo de encabezado generado por Bison
%}

%option noyywrap

%%

"var"               { return VAR; }
"int"               { return INT; }
"float"             { return FLOAT; }
"bool"              { return BOOL; }
"string"            { return STRING; }
(m|km|cm|s|min|h|kg) { return UNIDAD; }
"+"  {return PLUS; }
"-"  {return MINUS; }
"*"  {return MULTIPLY; }
"/"  {return DIVIDE; }
(<|>|<=|>=|==|!=)        { return RELACIONAL; }
&&|\|\||!            { return LOGICO; }
\"([^\\\"]|\\\\.)*\"       { yylval.str = strdup(yytext); return STRING; }

"CONVERTIR"         { return CONVERTIR; }

"(" { return LPAREN; } // Reconoce el paréntesis izquierdo
")" { return RPAREN; } // Reconoce el paréntesis derecho
"[" { return LBRACE; }
"]" { return RBRACE; }
";" {return SEMICOLON; }

"para"  {return PARA; }
"si" {return SI; }
"sino" {return SINO;}
"mientras" {return MIENTRAS;}
"print" {return PRINT; }

[0-9]+\.[0-9]+      { yylval.real = atof(yytext); return REAL; } // Números reales
[0-9]+              { yylval.num = atoi(yytext); return NUMBER; } // Números enteros

[a-zA-Z][a-zA-Z0-9]* { yylval.str = strdup(yytext); return IDENTIFIER; }

"//".*              ; // Comentario de una línea
"\/\*".*"\*\/"      ; // Comentario multilínea

[ \t\n]             ; // Ignorar espacios en blanco y saltos de línea
.                   { fprintf(stderr, "Carácter no válido: %s\n", yytext); }

%%