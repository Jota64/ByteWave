# Compilador para ByteWave

<hr>

### Definición

    - Definicion del Lenguaje

## Gramática

    - Explicacion Gramatica

### Gramática léxica

    - Explicacion gramatica lexica

### Gramática sintáctica

    -Explicacion gramatica sintactica

## Tokens

    - Definicion de Tokens

## Compilar y ejecutar

Para compilar seguir los siguientes pasos:

### Analizador Lexico

```
flex lexer.l
gcc lex.yy.c -o Lexer
```

Para probar con archivo de evemplo `example.txt`

```
./lexer <example.txt
o
Get-Content example.txt | .\lexer.exe
```
