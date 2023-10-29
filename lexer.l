%{

#include "parser.tab.h" // Archivo de encabezado generado por Bison
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

%}

%option noyywrap

%%

[0-9]+          {yylval = atoi(yytext); printf("NUMBER (%s)\n",yytext); return(NUMBER);}
[0-9]+\.[0-9]+  {yylval = atof(yytext); printf("REAL (%s)\n",yytext);return(REAL);}

"+"     { printf("PLUS (%s)\n",yytext); return(PLUS); }
"-"     { printf("MINUS (%s)\n",yytext); return(MINUS); }
"*"     { printf("MULTIPLY (%s)\n",yytext); return(MULTIPLY); }
"/"     { printf("DIVIDE (%s)\n",yytext); return(DIVIDE); }
";"     { printf("SEMICOLON (%s)\n",yytext); return(SEMICOLON); }

"//"(.)*\n { /*Descarta comentario de una sola linea*/}
"\/\*".*"\*\/" { /*Descarta comentario de varias lineas*/}

[ \t\n] { /*Ignorar espacios en blanco y saltos de línea*/}

.                   { fprintf(stderr, "Error: Carácter no válido: %s\n", yytext); }

%%