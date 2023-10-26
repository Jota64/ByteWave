%{

//#include "y.tab.h" // Archivo de encabezado generado por Bison
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

%}

%option noyywrap

%{
int in_comment = 0;
%}

%%

"var"           {yylval = yytext; return(VAR);}
"int"           {yylval = yytext; return(INT);}
"float"         {yylval = yytext; return(FLOAT);} 
"bool"          {yylval = yytext; return(BOOL);}
"string"        {yylval = yytext; return(STRING);}
"CONVERTIR"     {yylval = yytext; return(CONVERTIR);}
"para"          {yylval = yytext; return(PARA);}
"si"            {yylval = yytext; return(SI);}
"sino"          {yylval = yytext; return(SINO);}
"mientras"      {yylval = yytext; return(MIENTRAS);}
"print"         {yylval = yytext; return(PRINT);}

[0-9]+          {yylval = atoi(yytext); return(NUMBER);}
[0-9]+\.[0-9]+  {yylval = atof(yytext); return(REAL);}

[a-zA-Z][a-zA-Z0-9]*    {yylval = strdup(yytext); return(IDENTIFIER);}

"+"     { return(PLUS); }
"-"     { return(MINUS); }
"*"     { return(MULTIPLY); }
"/"     { return(DIVIDE); }
"<"     { return(ESS_THAN); }
">"     { return(GREATER_THAN); }
"<="    { return(LESS_THAN_OR_EQUAL); }
">="    { return(GREATER_THAN_OR_EQUAL); }
"=="    { return(EQUAL); }
"="     { return(ASIGNACION); }
"!="    { return(NOT_EQUAL); }
"&&"    { return(LOGICAL_AND); }
"||"    { return(LOGICAL_OR); }
"!"     { return(LOGICAL_NOT); }

"("     { return(LPARENT); }
")"     { return(RPARENT); }
"["     { return(LBRACE); }
"]"     { return(RBRACE); }
";"     { return(SEMICOLON); }
","     { return(COMMA); }
"{"     { return(LCURLYBR); }
"}"     { return(RCURLYBR); }

"//"(.)*\n { /*Descarta comentario de una sola linea*/}


"/*"     { in_comment = 1; }
<IN_COMMENT>{
  "*/"   { in_comment = 0; }
  .     /* Continuar consumiendo caracteres dentro del comentario */
}


(m|km|cm|s|min|h|kg) { return(UNIDAD); }


[ \t\n]             ; // Ignorar espacios en blanco y saltos de línea
.                   { fprintf(stderr, "Error: Carácter no válido: %s\n", yytext); }

%%