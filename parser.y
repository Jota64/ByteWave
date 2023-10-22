%{
#include <stdio.h>
#include <stdlib.h>
%}

%union {
    int num;
    char *str;
    float real;
}

%token <num> NUMBER
%token <str> IDENTIFIER
%token VAR INT FLOAT BOOL STRING
%token METER KILOMETER SECOND MINUTE HOUR KILOGRAM
%token PLUS MINUS MULTIPLY DIVIDE EQUAL SEMICOLON
%token IF ELSE WHILE FOR
%token LPAREN RPAREN LBRACE RBRACE
%token CONVERTIR
%token REAL UNIDAD RELACIONAL LOGICO

%left '+' '-'
%left '*' '/'
%right '='
%%
programa: declaraciones
        ;

declaraciones: declaracion
            | declaracion declaraciones
            ;

declaracion: variable_declaracion
           | asignacion SEMICOLON
           | condicional
           | bucle
           ;

variable_declaracion: VAR IDENTIFIER tipo_de_dato unidad SEMICOLON
                   ;

tipo_de_dato: INT
           | FLOAT
           | BOOL
           | STRING
           ;

unidad: METER
     | KILOMETER
     | SECOND
     | MINUTE
     | HOUR
     | KILOGRAM
     ;

asignacion: IDENTIFIER EQUAL expresion SEMICOLON
          ;

expresion: expresion_aritmetica
         | conversion
         ;

expresion_aritmetica: termino
                   | expresion_aritmetica PLUS termino
                   | expresion_aritmetica MINUS termino
                   ;

termino: factor
       | termino MULTIPLY factor
       | termino DIVIDE factor
       ;

factor: IDENTIFIER
      | NUMBER
      | LPAREN expresion_aritmetica RPAREN
      ;

conversion: CONVERTIR LPAREN expresion_aritmetica ',' unidad RPAREN
          ;

condicional: IF LPAREN expresion RPAREN bloque ELSE bloque
           | IF LPAREN expresion RPAREN bloque
           ;

bloque: LBRACE declaraciones RBRACE
      ;

bucle: WHILE LPAREN expresion RPAREN bloque
     | FOR LPAREN asignacion SEMICOLON expresion SEMICOLON asignacion RPAREN bloque
     ;

%%
int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
