%{

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

struct SymbolEntry {
    char *name;
    char *type;
    union {
        int valor_entero;
        float valor_real;
        char *str;
        int valor_bool;
    } value;
    char *unit;
};


#define MAX_SYMBOLS 100
struct SymbolEntry symbolTable[MAX_SYMBOLS];
int symbolCount = 0;

int findSymbol(char *name) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return i; // La variable ya existe en la tabla de símbolos.
        }
    }
    return -1; // La variable no existe en la tabla de símbolos.
}

%}

%left PLUS
%left MINUS
%left DIVIDE
%left MULTIPLY 
%right ASIGNACION

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
%token LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%token NOT_EQUAL LOGICAL_AND LOGICAL_OR LOGICAL_NOT EQUAL
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
    { 
        int index = findSymbol($2);
        if(index == -1){
            if(symbolCount<MAX_SYMBOLS){
                symbolTable[symbolCount].name = strdup($2);
                symbolTable[symbolCount].type = strdup($3);
                symbolTable[symbolCount].unit = strdup($4);
                symbolCount++;
            } else {
                yyerror("La tabla de simbolos esta llena");
                exit(1);
            }
        } else {
            yyerror("La variable ya existe");
            exit(1);
        }
        printf("Declaración de variable: %s - tipo  %s - unidad %s\n", $2, $3, $4 ? $4: "sin unidad"); 

    }
    
    ;

type:
    INT
    | FLOAT
    | BOOL
    | STRING
    ;

assignment_statement:
    IDENTIFIER ASIGNACION expr_int SEMICOLON 
    { 
        int index = findSymbol($1);
        printf("index: %i",index);
        if(index == -1){
            if(symbolCount<MAX_SYMBOLS){
                symbolTable[symbolCount].name = strdup($1);
                symbolTable[symbolCount].type = "INT";
                symbolTable[symbolCount].value.valor_entero = $3;
                symbolCount++;
            } else {
                yyerror("La tabla de simbolos esta llena");
                exit(1);
            }
        } else {
            symbolTable[symbolCount].value.valor_entero = $3;
        }
        printf("Asignacion de variable: %s igual %i \n", $1, $3); 
    }
    
    | IDENTIFIER ASIGNACION expr_float SEMICOLON
        { 
            int index = findSymbol($1);
            printf("index: %i",index);
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup($1);
                    symbolTable[symbolCount].type = "FLOAT";
                    symbolTable[symbolCount].value.valor_real = $3;
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[symbolCount].value.valor_real = $3;
            }
            printf("Asignacion de variable: %s igual %f \n", $1, $3); 
        }

    | IDENTIFIER ASIGNACION expr_string SEMICOLON
        { 
            int index = findSymbol($1);
            printf("index: %i",index);
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup($1);
                    symbolTable[symbolCount].type = "STRING";
                    symbolTable[symbolCount].value.str = $3;
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[symbolCount].value.str = $3;
            }
            printf("Asignacion de variable: %s igual %s \n", $1, $3); 
        }

    | IDENTIFIER ASIGNACION expr_bool SEMICOLON
        { 
            int index = findSymbol($1);
                    printf("index: %i",index);
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup($1);
                    symbolTable[symbolCount].type = "BOOL";
                    symbolTable[symbolCount].value.valor_bool = $3;
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[symbolCount].value.valor_bool = $3;
            }
            printf("Asignacion de variable: %s igual %i \n", $1, $3);
        }
    ;
expr_int:
    NUMBER {$$ = $1}
    ;
expr_float :
    REAL {$$ = $1}
    ;
expr_string :
    V_STRING {$$ = $1}
    ;
expr_bool :
    V_BOOL {$$ = $1}
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

//hasta aqui bien. | expr CONVERTIR type 
expr:
    expr_int PLUS expr_int { printf("suma: %f\n", $1+$3); }
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
    | CONVERTIR LPAREN expr_id COMMA UNIDAD RPAREN 
    { printf("Conversión de unidad: %s a %s\n", $3, $5); }
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
    PARA LPAREN assignment_statement SEMICOLON expr SEMICOLON increment_statement RPAREN LCURLYBR statements RCURLYBR
    {
        printf("Instrucción PARA con inicialización, condición y actualización\n");
    }
    ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "Error sintáctico: %s\n", s);
}

int main(int argc, char **argv) {
  yyparse();
  return 0;
}