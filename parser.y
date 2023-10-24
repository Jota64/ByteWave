/*
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
%token REAL UNIDAD RELACIONAL LOGICO PARA MIENTRAS SI SINO

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
*/
%{

#include "tokens.h" // Archivo de encabezado generado por flex
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);

%}

%union {
  int num;
  float real;
  char *str;
}

%token <num> NUMBER
%token <real> REAL
%token <str> STRING IDENTIFIER

%token VAR INT FLOAT BOOL UNIDAD
%token PLUS MINUS MULTIPLY DIVIDE
%token RELACIONAL LOGICO
%token CONVERTIR ASIGNACION
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON
%token PARA SI SINO MIENTRAS PRINT
%token LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL NOT_EQUAL LOGICAL_AND LOGICAL_OR LOGICAL_NOT EQUAL


%type <num> expr_int
%type <real> expr_real
%type <str> expr_str expr_id

%%

program: /* empty */
       | program statement SEMICOLON
       ;

statement: var_decl
         | assign_stmt
         | print_stmt
         | if_stmt
         | while_stmt
         | for_stmt
         | convert_stmt
         ;

var_decl: VAR IDENTIFIER type
        ;

type: INT
    | FLOAT
    | BOOL
    | STRING
    ;

assign_stmt: IDENTIFIER '=' expr
           ;

expr: expr_int 
    | expr_real 
    | expr_str 
    | expr_id 
    ;

expr_int: NUMBER 
        | expr_int PLUS expr_int 
        | expr_int MINUS expr_int 
        | expr_int MULTIPLY expr_int 
        | expr_int DIVIDE expr_int 
        ;

expr_real: REAL 
         | expr_real PLUS expr_real 
         | expr_real MINUS expr_real 
         | expr_real MULTIPLY expr_real 
         | expr_real DIVIDE expr_real 
         ;

expr_str: STRING 
       | expr_str PLUS expr_str 
       ;

expr_id: IDENTIFIER 
       ;

print_stmt: PRINT LPAREN expr RPAREN
          ;

if_stmt: SI LPAREN cond RPAREN LBRACE program RBRACE SINO LBRACE program RBRACE
       ;

while_stmt: MIENTRAS LPAREN cond RPAREN LBRACE program RBRACE
          ;

for_stmt: PARA LPAREN assign_stmt SEMICOLON cond SEMICOLON assign_stmt RPAREN LBRACE program RBRACE
        ;

convert_stmt: CONVERTIR LPAREN IDENTIFIER ',' UNIDAD ',' UNIDAD RPAREN
            ;

cond: expr RELACIONAL expr 
    | cond LOGICO cond 
    | LOGICO cond 
    ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "Error sintáctico: %s\n", s);
}

int main(int argc, char **argv) {
  yyparse();
  return 0;
}
