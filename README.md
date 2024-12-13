# **Compiler Design | `Lexical Analysis`**

Implementación académica de un analizador léxico (`scanner`) para el lenguaje SM (Lenguaje de Máquina de Pila). El analizador léxico es una parte fundamental de un compilador y se encarga de dividir el código fuente en unidades más pequeñas llamadas *tokens*, facilitando su procesamiento y análisis posterior.

## **SM (Stack Machine Language)**

La siguiente gramática establece la estructura básica de las instrucciones del lenguaje SM, incluyendo la posibilidad de etiquetas, instrucciones de salto y operaciones unarias.

```plaintext
<program>       ::= <instruction>+
<instruction>   ::= <label>? (<unaryinstr> | <opinstr> <num> | <jmpinstr> <id>) <eol>
<unaryinstr>    ::= skip | pop | dup | swap | add | sub | mul | div | print
<opinstr>       ::= push | store | load
<jmpinstr>      ::= jmpeq | jmpgt | jmpge | jmplt | jmple | goto
```

La especificación léxica establece las reglas para identificar los tokens y lexemas presentes en el código fuente del lenguaje SM. A continuación, se presentan las expresiones regulares utilizadas:

```plaintext
digit               ::= [0-9]
character           ::= [a-zA-Z]
<reserved-word>     ::= push | jmpeq | jmpgt | jmpge | jmplt | jmple | skip | pop | 
                        dup | swap | add | sub | mul | div | store | load | goto | print
<id>                ::= character | (character | digit | ‘_’)*
<label>             ::= <id>:
<num>               ::= digit+
<eol>               ::= ‘\n’+
<ws>                ::= (‘ ‘ | ‘\t’)+
```

De acuerdo con estas reglas léxicas, las unidades léxicas como `<id>`, `<num>`, `<eol>` y todas las palabras reservadas se convierten en *tokens*. Sin embargo, el patrón `<ws>`, que representa los espacios en blanco, no genera tokens y se ignora. Los nombres de los tokens se escriben en mayúsculas y coinciden con las unidades léxicas correspondientes.

## **Ejemplo de entrada y salida**

**Entrada**: `example0.svm`

```plaintext
push 3


L1: jmpgt
mul
add
goto L2

```

**Salida**:

```plaintext
next token PUSH
next token NUM(3)
next token EOL
next token LABEL(L1)
next token JMPGT
next token EOL
next token MUL
next token EOL
next token ADD
next token EOL
next token GOTO
next token ID(L2)
next token EOL
```
