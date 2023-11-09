%{

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);


%}

%left PLUS MINUS
%left MULTIPLY DIVIDE
%right ASIGNACION
%nonassoc LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%nonassoc NOT_EQUAL
%left LOGICAL_AND
%left LOGICAL_OR
%right LOGICAL_NOT
%nonassoc EQUAL

%union {
  int valor_entero;
  float valor_real;
  char *str;
  int valor_bool;
  
}

//para valores
%token <valor_entero> NUMBER
%token <valor_real> REAL
%token <valor_bool> V_BOOL
%token <str> V_STRING IDENTIFIER

%token VAR 
%token LPAREN RPAREN LCURLYBR RCURLYBR SEMICOLON
%token PARA SI SINO MIENTRAS PRINT
%token COMMA CONVERTIR
%token<str> UNIDAD INT FLOAT BOOL STRING


%type <valor_entero> expr_int
%type <valor_real> expr_float
%type <valor_bool> expr_bool
%type <str> expr_string expr_id type 


%%

program:
    statements
    ;

statements:
    statement
    | statements statement
    | statements increment_statement
    | statements for_statement
    ;

statement:
    var_declaration
    | assignment_statement
    | print_statement
    | if_statement
    | while_statement
    ;

var_declaration:
    VAR IDENTIFIER type UNIDAD SEMICOLON 
    { printf("Declaración de variable: %s - tipo  %s - unidad %s\n", $2, $3, $4 ? $4: "sin unidad"); }
    
    ;

type:
    INT
    | FLOAT
    | BOOL
    | STRING
    ;

assignment_statement:
    IDENTIFIER ASIGNACION expr_int SEMICOLON 
    { printf("Asignacion de variable: %s igual %i \n", $1, $3); }
    
    | IDENTIFIER ASIGNACION expr_float SEMICOLON
        { printf("Asignacion de variable: %s igual %f \n", $1, $3); }

    | IDENTIFIER ASIGNACION expr_string SEMICOLON
        { printf("Asignacion de variable: %s igual %s \n", $1, $3); }

    | IDENTIFIER ASIGNACION expr_bool SEMICOLON
        { printf("Asignacion de variable: %s igual %i \n", $1, $3); }
    | IDENTIFIER ASIGNACION CONVERTIR LPAREN expr COMMA UNIDAD RPAREN SEMICOLON
    { printf("Conversión de unidad: %s a %s\n", $1, $7); } ;

    

    ;
expr_int:
    NUMBER
    ;
expr_float :
    REAL
    ;
expr_string :
    V_STRING
    ;
expr_bool :
    V_BOOL
    ;

printable:
    expr
    | V_STRING
   
    ;

print_statement:
    PRINT LPAREN printable RPAREN SEMICOLON
    {
        printf("Instrucción de impresión\n");
    }
    ;

if_statement:
    SI LPAREN expr RPAREN LCURLYBR statements RCURLYBR
    | SI LPAREN expr RPAREN LCURLYBR statements RCURLYBR SINO LCURLYBR statements RCURLYBR
    ;

while_statement:
    MIENTRAS LPAREN expr RPAREN LCURLYBR statements RCURLYBR
    ;

//conversion_statement:
 



//hasta aqui bien. | expr CONVERTIR type 
expr:
     expr_int PLUS expr_int SEMICOLON { printf("suma\n"); }
    | expr MINUS expr { printf("resta\n"); }
    | expr MULTIPLY expr { printf("multiplicacion\n"); }
    | expr DIVIDE expr { printf("division\n"); }
    | expr ASIGNACION expr  { printf("asignacion\n"); }
    | expr LESS_THAN expr { printf("menor-que\n"); }
    | expr GREATER_THAN expr { printf("expresion (mayor-que)\n"); }
    | expr LESS_THAN_OR_EQUAL expr { printf("menor_igual\n"); }
    | expr GREATER_THAN_OR_EQUAL expr { printf("mayor_igual\n"); }
    | expr NOT_EQUAL expr { printf("diferente_a\n"); }
    | expr LOGICAL_AND expr { printf("and\n"); }
    | expr LOGICAL_OR expr { printf("or\n"); }
    | expr LOGICAL_NOT { printf("not\n"); }
 
    | LPAREN expr RPAREN
    | expr_id
    | NUMBER
    | REAL
    | STRING
    | PRINT LPAREN expr RPAREN { printf("Instrucción de impresión\n"); }
    ;

expr_id:
    IDENTIFIER
    ;
increment_statement:
    IDENTIFIER PLUS PLUS SEMICOLON
    {
        printf("Instrucción de incremento: %s\n", $1);
    }
    ;

for_statement:
    PARA LPAREN for_init SEMICOLON for_condition SEMICOLON for_update RPAREN LCURLYBR statements RCURLYBR
    {
        printf("Instrucción PARA con inicialización, condición y actualización\n");
    }
    ;

for_init:
    assignment_statement
    ;

for_condition:
    expr
    ;

for_update:
    increment_statement
    ;


%%

void yyerror(const char *s) {
  fprintf(stderr, "Error sintáctico: %s\n", s);
}

int main(int argc, char **argv) {
  
  yyparse();
  return 0;
}
