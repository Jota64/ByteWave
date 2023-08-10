#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

struct Token {
  string Tipo; 
  string Valor; 
  int Linea;
  int Columna;
};







bool validaPalabrasClave(const string& Expresion){
    const regex PalabrasClave("\\b(var|if|else|fin|while|endwhile|float|int|bool)\\b"); // palabras reservadas
    return regex_match(Expresion, PalabrasClave);
}

bool validaIdentificadores(const string& Expresion){
    const regex Identificadores("\\b([a-zA-Z_][a-zA-Z0-9_]*)\\b"); // identificadores
    return regex_match(Expresion, Identificadores);
}

bool validaNumeros(const string& Expresion){
    const regex Numeros("\\b([0-9]+(\\.[0-9]+)?)\\b"); // números enteros o decimales
    return regex_match(Expresion, Numeros);
}


bool validaOperadores(const string& Expresion){
    const regex Operadores("[+\\-*/%=<>!&|^~]+"); // operadores aritméticos, relacionales, lógicos o a nivel de bits
    return regex_match(Expresion, Operadores);
}


bool validaDelimitadores(const string& Expresion){
    const regex Delimitadores("[;,(){}\\[\\]]"); // delimitadores
    return regex_match(Expresion, Delimitadores);
}


int main(){
    cout << "PalabrasClave: " << endl;
    cout << "if: " << validaPalabrasClave("if");
    cout << endl;
    cout << "pruebaFalsa: " << validaPalabrasClave("pruebaFalsa");


    return 0;
}


