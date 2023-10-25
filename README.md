# Compilador para ByteWave

<hr>

### Definición

    ByteWave tiene como objetivo proporcionar una manera sencilla y eficiente de realizar conversiones entre diferentes unidades de medida. Está diseñado para ser utilizado por cualquier persona que necesite realizar conversiones de manera precisa y rápida, adicionalmente permite realizar algunos cálculos sobre estas cantidades.  
    

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
