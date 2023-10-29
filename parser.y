%{
#include <stdio.h>
#include "parser.tab.h"

void yyerror(const char *s);

int isinteger(double value) {
    return (value == (int)value);
}

int isreal(double value) {
    return (value != (int)value);
}

typedef struct {
    char* name;  // Nombre de la variable
    int value;  // Valor de la variable
    char* unit; // Valor de unidad de la variable
} Variable;

Variable* symbol_table = NULL; // Tabla de símbolos para las variables
int symbol_count = 0;          // Contador de variables en la tabla

%}

%token NUMBER REAL PLUS MINUS MULTIPLY DIVIDE SEMICOLON

%%


program: /* Vacío */
    | program expr SEMICOLON{ printf("Resultado: %d\n", $2); }
    ;

expr: 
       NUMBER {$$ = $1;}
    |   REAL {$$ = $1;}
    | expr PLUS expr { 
              if(isinteger($1) && isreal($3)){
                     $$ = (double)$1 + $3;
              } else if(isreal($1) && isinteger($3)){
                     $$ = $1 + (double)$3;
              }else {
                     $$ = $1 + $3; 
              }
       }
    | expr MINUS expr { $$ = $1 - $3; }
    | expr MULTIPLY expr { $$ = $1 * $3; }
    | expr DIVIDE expr { $$ = $1 / $3; }
    ;

%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
  fprintf(stderr, "Error sintáctico: %s\n", s);
}