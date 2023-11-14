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
        char* str;
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
    | plus_statement
    | minus_statement
    | multiply_statement
    | divide_statement
    ;

var_declaration:
    VAR IDENTIFIER type UNIDAD SEMICOLON 
    { 
        int index = findSymbol($2);
        printf("index: %i\n",index);
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
        printf("index: %i\n",index);
        if(index == -1){
            if(symbolCount<MAX_SYMBOLS){
                symbolTable[symbolCount].name = strdup($1);
                symbolTable[symbolCount].type = "int";
                symbolTable[symbolCount].value.valor_entero = $3;
                symbolCount++;
            } else {
                yyerror("La tabla de simbolos esta llena");
                exit(1);
            }
        } else {
            symbolTable[index].value.valor_entero = $3;
        }
        printf("Asignacion de variable: %s igual %i \n", $1, $3); 
    }
    
    | IDENTIFIER ASIGNACION expr_float SEMICOLON
        { 
            int index = findSymbol($1);
            printf("index: %i\n",index);
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup($1);
                    symbolTable[symbolCount].type = "float";
                    symbolTable[symbolCount].value.valor_real = $3;
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[index].value.valor_real = $3;
            }
            printf("Asignacion de variable: %s igual %f \n", $1, $3); 
        }

    | IDENTIFIER ASIGNACION expr_string SEMICOLON
        { 
            int index = findSymbol($1);
            printf("index: %i\n",index);
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup($1);
                    symbolTable[symbolCount].type = "string";
                    symbolTable[symbolCount].value.str = $3;
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[index].value.str = $3;
            }
            printf("Asignacion de variable: %s igual %s \n", $1, $3); 
        }

    | IDENTIFIER ASIGNACION expr_bool SEMICOLON
        { 
            int index = findSymbol($1);
            printf("index: %i\n",index);
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup($1);
                    symbolTable[symbolCount].type = "bool";
                    symbolTable[symbolCount].value.valor_bool = $3;
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[index].value.valor_bool = $3;
            }
            printf("Asignacion de variable: %s igual %i \n", $1, $3);
        }
    | IDENTIFIER ASIGNACION CONVERTIR LPAREN IDENTIFIER COMMA UNIDAD RPAREN SEMICOLON
    {
        int index = findSymbol($1);
        printf("index: %i\n",index);
        if(index > -1){
            char* tipo = symbolTable[index].type;
            printf("Tipo variable: %s\n", tipo);
            if(strcmp(tipo,"int") == 0){
                int value = symbolTable[index].value.valor_entero;
                printf("Valor variable: %i\n", value);
            }
        }
        int index2 = findSymbol($5);
        printf("index: %i\n",index2);
        if(index2 > -1){
            char* tipo = symbolTable[index2].type;
            printf("Tipo variable: %s\n", tipo);
            if(strcmp(tipo,"int") == 0){
                int value = symbolTable[index2].value.valor_entero;
                printf("Valor variable: %i\n", value);
            }
        }
        printf("Conversión de unidad: %s a %s\n", $1, $7); 
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

print_statement:
    PRINT LPAREN IDENTIFIER RPAREN SEMICOLON
    {
        int index = findSymbol($3);
        printf("index: %i\n",index);
        if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            char* tipo = symbolTable[index].type;
            printf("Tipo variable: %s\n", tipo);
            if(strcmp(tipo,"int") == 0){
                int value = symbolTable[index].value.valor_entero;
                printf("Valor variable: %i\n", value);
            }
            if(strcmp(tipo,"float") == 0){
                float value = symbolTable[index].value.valor_real;
                printf("Valor variable: %f\n", value);
            }
            if(strcmp(tipo,"bool") == 0){
                int value = symbolTable[index].value.valor_bool;
                printf("Valor variable: %s\n", value ? "true" : "false");
            }
            if(strcmp(tipo,"string") == 0){
                char* value = symbolTable[index].value.str;
                printf("Valor variable: %s\n", value);
            }
        }
        printf("Instrucción de impresión\n");
    }
    | PRINT LPAREN expr_string RPAREN SEMICOLON
    {
        printf("Instrucción de impresión: %s\n",$3);
    }
    ;

if_statement:
    SI LPAREN expr RPAREN LCURLYBR statements RCURLYBR
    | SI LPAREN expr RPAREN LCURLYBR statements RCURLYBR SINO LCURLYBR statements RCURLYBR
    ;

while_statement:
    MIENTRAS LPAREN expr RPAREN LCURLYBR statements RCURLYBR
    ;

//PENDIENTE VALIDACION QUE LA VARIABLE TENGA EL TIPO CORRECTO
plus_statement:
    IDENTIFIER ASIGNACION expr_int PLUS expr_int SEMICOLON {
        int index = findSymbol($1);
        printf("index: %i\n",index);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_entero = $3+$5;
        }
        printf("suma: %i\n", $3+$5);
    }
    | IDENTIFIER ASIGNACION expr_int PLUS expr_float SEMICOLON {
        int index = findSymbol($1);
        printf("index: %i\n",index);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3+$5;
        }
        printf("suma: %f\n", $3+$5);
    }
    | IDENTIFIER ASIGNACION expr_float PLUS expr_int SEMICOLON {
        int index = findSymbol($1);
        printf("index: %i\n",index);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3+$5;
        }
        printf("suma: %f\n", $3+$5);
    }
    | IDENTIFIER ASIGNACION expr_float PLUS expr_float SEMICOLON {
        int index = findSymbol($1);
        printf("index: %i\n",index);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3+$5;
        }
        printf("suma: %f\n", $3+$5);
    }

minus_statement:
    IDENTIFIER ASIGNACION expr_int MINUS expr_int SEMICOLON {
        printf("resta: %i\n", $3-$5);
    }
    | IDENTIFIER ASIGNACION expr_int MINUS expr_float SEMICOLON {
        printf("resta: %f\n", $3-$5);
    }
    | IDENTIFIER ASIGNACION expr_float MINUS expr_int SEMICOLON {
        printf("resta: %f\n", $3-$5);
    }
    | IDENTIFIER ASIGNACION expr_float MINUS expr_float SEMICOLON {
        printf("resta: %f\n", $3-$5);
    }

multiply_statement:
    IDENTIFIER ASIGNACION expr_int MULTIPLY expr_int SEMICOLON {
        printf("multiplicacion: %i\n", $3*$5);
    }
    | IDENTIFIER ASIGNACION expr_int MULTIPLY expr_float SEMICOLON {
        printf("multiplicacion: %f\n", $3*$5);
    }
    | IDENTIFIER ASIGNACION expr_float MULTIPLY expr_int SEMICOLON {
        printf("multiplicacion: %f\n", $3*$5);
    }
    | IDENTIFIER ASIGNACION expr_float MULTIPLY expr_float SEMICOLON {
        printf("multiplicacion: %f\n", $3*$5);
    }   

divide_statement:
    IDENTIFIER ASIGNACION expr_int DIVIDE expr_int SEMICOLON {
        printf("division: %i\n", $3/$5);
    }
    | IDENTIFIER ASIGNACION expr_int DIVIDE expr_float SEMICOLON {
        printf("division: %f\n", $3/$5);
    }
    | IDENTIFIER ASIGNACION expr_float DIVIDE expr_int SEMICOLON {
        printf("division: %f\n", $3/$5);
    }
    | IDENTIFIER ASIGNACION expr_float DIVIDE expr_float SEMICOLON {
        printf("division: %f\n", $3/$5);
    }

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