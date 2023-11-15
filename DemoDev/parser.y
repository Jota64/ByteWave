%{

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

void yyerror(const char *s);
int yylex(void);

std::map<std::string, std::vector<std::string>> units;
std::map<std::string, std::string> categories;
std::map<std::string, double> conversiones;

void inicializa(){

    units["Longitud"] = {"m", "km", "cm", "mm", "pm", "nm", "mi", "yd", "ft", "in"};
    units["Masa"] = {"kg", "g", "mg", "µg", "t", "lb", "oz"};
    units["Volumen"] = {"m3", "L", "mL", "gal", "qt", "pt", "floz"};
    units["Tiempo"] = {"s", "min", "h", " d", "wk", "mo", "yr"};
    units["Temperatura"] = {"gC", "gF", "K"};
    units["Area"] = {"m2", "km2", "ha", "ac", "mi2", "yd2", "ft2", "in2"};
    units["Velocidad"] = {"ms", "kmh", "mph", "kt"};

    // Creamos un nuevo map donde la clave es una string (la unidad de medida)
    // y el valor es una string (la categoría de la unidad de medida)

    for (auto &category : units){
        for (auto &unit : category.second){
            categories[unit] = category.first;
        }
    }

    conversiones = {
    {"m", 1.0},
    {"km", 1000.0},
    {"cm", 0.01},
    {"mm", 0.001},
    {"pm", 1e-6},
    {"nm", 1e-9},
    {"mi", 1609.34},
    {"yd", 0.9144},
    {"ft", 0.3048},
    {"in", 0.0254},
    {"s", 1.0},
    {"min", 60.0},
    {"h", 3600.0},
    {"d", 86400.0},
    {"wk", 604800.0},
    {"mo", 2628000.0},
    {"yr", 31536000.0},
    {"kg", 1.0},
    {"g", 0.001},
    {"mg", 1e-6},
    {"pg", 1e-9},
    {"t", 1000.0},
    {"lb", 0.453592},
    {"oz", 0.0283495}
    };
}

struct SymbolEntry {
    char *name;
    char *type;
    union {
        int valor_entero;
        float valor_real;
        char* str;
        int valor_bool;
    } value;
    string unit[2];
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

void convertUnit(char* nameVar, char* unitDest){
    int index = findSymbol(nameVar);
    
    if(index == -1){
        yyerror("La variable no se encuentra declarada");
        exit(1);
    }else{
        string type = symbolTable[index].type;
        string unidadOrigen = symbolTable[index].unit[1];
        if(categories[unidadOrigen] == categories[unitDest] ){
            float value;
            if(type == "int"){
                value = symbolTable[index].value.valor_entero;
            }else if(type == "float"){
                value = symbolTable[index].value.valor_real;
            }

            double valorEnBase = value * conversiones[unidadOrigen];
            double valorConvertido = valorEnBase / conversiones[unitDest];
            symbolTable[index].unit[1]=unitDest;
            if(type == "int"){
                symbolTable[index].value.valor_entero = static_cast<int>(valorConvertido);
            }else if(type == "float"){
                symbolTable[index].value.valor_real = valorConvertido;
            }
        }else{
            cout << "Unidad Origen: " << categories[unidadOrigen] << "; Unidad Destino: " << categories[unitDest] << endl;
            yyerror("Las unidades no son consistentes.");
            exit(1);
        }

    }

}

int compareUnits(char* name1, char* name2){
    int index1 = findSymbol(name1);
    int index2 = findSymbol(name2);

    if(symbolTable[index1].unit[1] == symbolTable[index2].unit[1]){
        return 1;
    }else{
        return -1;
    }
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
        if(index == -1){
            if(symbolCount<MAX_SYMBOLS){
                symbolTable[symbolCount].name = strdup($2);
                symbolTable[symbolCount].type = strdup($3);
                string unidad = $4;
                if(categories.count($4)>0){
                    string categorySet = categories[$4];

                    symbolTable[symbolCount].unit[0] = categorySet;
                    symbolTable[symbolCount].unit[1] = strdup($4);
                }else{
                    symbolTable[symbolCount].unit[0] = "unit";
                    symbolTable[symbolCount].unit[1] = "unit";
                }
                symbolCount++;
            } else {
                yyerror("La tabla de simbolos esta llena");
                exit(1);
            }
        } else {
            yyerror("La variable ya existe");
            exit(1);
        }
        cout << "Declaracion de variable: " << $2 << "; Tipo: " << $3 << "; Unidad: " << $4 << endl;
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
        if(index == -1){
            if(symbolCount<MAX_SYMBOLS){
                symbolTable[symbolCount].name = strdup($1);
                symbolTable[symbolCount].type = "int";
                symbolTable[symbolCount].value.valor_entero = $3;
                symbolTable[symbolCount].unit[0] = "unit";
                symbolTable[symbolCount].unit[1] = "unit";
                symbolCount++;
            } else {
                yyerror("La tabla de simbolos esta llena");
                exit(1);
            }
        } else {
            symbolTable[index].value.valor_entero = $3;
        }
        cout << "Asignacion de variable int: " << $1 << "; Valor: " << $3 << endl;
    }
    
    | IDENTIFIER ASIGNACION expr_float SEMICOLON
        { 
            int index = findSymbol($1);
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup($1);
                    symbolTable[symbolCount].type = "float";
                    symbolTable[symbolCount].value.valor_real = $3;
                    symbolTable[symbolCount].unit[0] = "unit";
                    symbolTable[symbolCount].unit[1] = "unit";
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[index].value.valor_real = $3;
            }
            cout << "Asignacion de variable float: " << $1 << "; Valor: " << $3 << endl;
        }

    | IDENTIFIER ASIGNACION expr_string SEMICOLON
        { 
            int index = findSymbol($1);
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup($1);
                    symbolTable[symbolCount].type = "string";
                    symbolTable[symbolCount].value.str = $3;
                    symbolTable[symbolCount].unit[0] = "unit";
                    symbolTable[symbolCount].unit[1] = "unit";
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[index].value.str = $3;
            }
            cout << "Asignacion de variable string: " << $1 << "; Valor: " << $3 << endl;
        }

    | IDENTIFIER ASIGNACION expr_bool SEMICOLON
        { 
            int index = findSymbol($1);
            if(index == -1){
                if(symbolCount<MAX_SYMBOLS){
                    symbolTable[symbolCount].name = strdup($1);
                    symbolTable[symbolCount].type = "bool";
                    symbolTable[symbolCount].value.valor_bool = $3;
                    symbolTable[symbolCount].unit[0] = "unit";
                    symbolTable[symbolCount].unit[1] = "unit";
                    symbolCount++;
                } else {
                    yyerror("La tabla de simbolos esta llena");
                    exit(1);
                }
            } else {
                symbolTable[index].value.valor_bool = $3;
            }
            cout << "Asignacion de variable bool: " << $1 << "; Valor: " << $3 << endl;
        }

    | IDENTIFIER ASIGNACION CONVERTIR LPAREN IDENTIFIER COMMA UNIDAD RPAREN SEMICOLON
    {
        convertUnit($5,$7);
        cout << "Convertir variable " << $1 << " a " << $7 << endl;
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
        if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            char* tipo = symbolTable[index].type;
            if(strcmp(tipo,"int") == 0){
                int value = symbolTable[index].value.valor_entero;
                string categoryUnit = symbolTable[index].unit[0];
                string unitCategory = symbolTable[index].unit[1];
                cout << categoryUnit << " " << $3 << ": " << value << unitCategory << endl;
            }
            if(strcmp(tipo,"float") == 0){
                float value = symbolTable[index].value.valor_real;
                string categoryUnit = symbolTable[index].unit[0];
                string unitCategory = symbolTable[index].unit[1];
                cout << categoryUnit << " " << $3 << ": " << value << unitCategory << endl;
            }
            if(strcmp(tipo,"bool") == 0){
                int value = symbolTable[index].value.valor_bool;
                string categoryUnit = symbolTable[index].unit[0];
                string unitCategory = symbolTable[index].unit[1];
                cout << categoryUnit << " " << $3 << ": " << (value ? "false" : "true") << unitCategory << endl;
            }
            if(strcmp(tipo,"string") == 0){
                char* value = symbolTable[index].value.str;
                string categoryUnit = symbolTable[index].unit[0];
                string unitCategory = symbolTable[index].unit[1];
                cout << categoryUnit << " " << $3 << ": " << value << endl;
            }
        }
    }
    | PRINT LPAREN expr_string RPAREN SEMICOLON
    {
        string printText = $3;
        replace(printText.begin(), printText.end(), '"', ' ');
        cout << printText << endl;
    }
    ;

if_statement:
    SI LPAREN expr RPAREN LCURLYBR statements RCURLYBR {
        cout << "" << endl;
    }
    | SI LPAREN IDENTIFIER GREATER_THAN expr_int RPAREN LCURLYBR statements RCURLYBR SINO LCURLYBR statements RCURLYBR{
        cout << "" << endl;
    }
    ;

while_statement:
    MIENTRAS LPAREN expr RPAREN LCURLYBR statements RCURLYBR
    ;

//PENDIENTE VALIDACION QUE LA VARIABLE TENGA EL TIPO CORRECTO
plus_statement:
    IDENTIFIER ASIGNACION expr_int PLUS expr_int SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_entero = $3+$5;
        }
        cout << "Realizar suma de int-int" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_int PLUS expr_float SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3+$5;
        }
        cout << "Realizar suma de int-float" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_float PLUS expr_int SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3+$5;
        }
        cout << "Realizar suma de float-int" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_float PLUS expr_float SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3+$5;
        }
        cout << "Realizar suma de float-float" << $3 << " y " << $5 << endl;
    }

minus_statement:
    IDENTIFIER ASIGNACION expr_int MINUS expr_int SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_entero = $3-$5;
        }
        cout << "Realizar resta de int-int" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_int MINUS expr_float SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3-$5;
        }
        cout << "Realizar resta de int-float" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_float MINUS expr_int SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3-$5;
        }
        cout << "Realizar resta de float-int" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_float MINUS expr_float SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3-$5;
        }
        cout << "Realizar resta de float-float" << $3 << " y " << $5 << endl;
    }

multiply_statement:
    IDENTIFIER ASIGNACION expr_int MULTIPLY expr_int SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_entero = $3*$5;
        }
        cout << "Realizar multiplicacion de int-int" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_int MULTIPLY expr_float SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3*$5;
        }
        cout << "Realizar multiplicacion de int-float" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_float MULTIPLY expr_int SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3*$5;
        }
        cout << "Realizar multiplicacion de float-int" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_float MULTIPLY expr_float SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3*$5;
        }
        cout << "Realizar multiplicacion de float-float" << $3 << " y " << $5 << endl;
    }   

divide_statement:
    IDENTIFIER ASIGNACION expr_int DIVIDE expr_int SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3/$5;
        }
        cout << "Realizar division de int-int" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_int DIVIDE expr_float SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3/$5;
        }
        cout << "Realizar division de int-float" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_float DIVIDE expr_int SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3/$5;
        }
        cout << "Realizar division de float-int" << $3 << " y " << $5 << endl;
    }
    | IDENTIFIER ASIGNACION expr_float DIVIDE expr_float SEMICOLON {
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            symbolTable[index].value.valor_real = $3/$5;
        }
        cout << "Realizar division de float-float" << $3 << " y " << $5 << endl;
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
    | IDENTIFIER GREATER_THAN expr_int { 
        
        printf("expresion (mayor-que), %s, %i\n", $1,$3); }
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
    IDENTIFIER PLUS PLUS SEMICOLON{
        int index = findSymbol($1);
         if(index == -1){
            yyerror("La variable no se encuentra declarada");
            exit(1);
        }else{
            char* tipo = symbolTable[index].type;
            if(strcmp(tipo,"int") == 0){
                symbolTable[index].value.valor_entero = symbolTable[index].value.valor_entero+1;
            }
            if(strcmp(tipo,"float") == 0){
                symbolTable[index].value.valor_real = symbolTable[index].value.valor_real+1;
            }
        }
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
  inicializa();
  yyparse();
  return 0;
}