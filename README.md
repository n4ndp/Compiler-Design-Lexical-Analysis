# **Compiler Design | `Lexical Analysis`**

Este repositorio contiene implementación de un analizador léxico (`Scanner`) en el lenguaje 
de programación C++ para el lenguaje de la máquina de pila SM (definido en la sección 1). 

# **1. Sintaxis de SM**

El lenguaje de máquina de pila SM está definido por la siguiente gramática:

``` 
<program> ::= <instruction>+
<instruction> ::= Label? ((<jmpinstr> <id>) | <unaryinstr> | (push <num>) <eol>
<jmpinstr> ::= jmpeq | jmpgt | jmpge | jmplt | jmple | goto
<unaryinstr> ::= skip | pop | dup | swap | add | sub | mul | div | store | load
```

La especificación léxica está dada por los siguientes patrones (expresiones regulares):

```
digit               ::= [0-9]
character           ::= [a-zA-Z]
<reserved-word>     ::= push | jmpeq | jmpgt | jmpge | jmplt | jmple | skip | pop | 
                        dup | swap | add | sub | mul | div | store | load | goto
<id>                ::= character | (character | digit | ‘_’)*
<label>             ::= <id>:
<num>               ::= digit+
<eol>               ::= ‘\n’+
<ws>                ::= (‘ ‘ | ‘\t’)+
```

Las unidades léxicas <id>, <num> y <eol> , y <reserved-word>, generan un token. El 
patrón <ws> no genera token; denota los espacios en blancos y se ignoran. Los tokens 
llevan el nombre de sus unidades léxicas pero en mayúscula e.g. el token NUM denota la 
unidad lexica <num>. Solo los tokens correspondientes a <num> y <id> tendrán como 
atributo al lexema. Solo los tokens correspondientes a <num> y <id> tendrán como atributo 
al lexema.  Resumiendo, los tokens a generar son:
• Un tipo de token por cada palabra reservada, con el mismo nombre del lexema. Por 
ejemplo, la palabra reservada pop generara el token POP.
Asi tendremos PUSH, JMPEQ, JMPGT, …, STORE, LOAD
• NUM(lexema) lexema es <num>
• ID(lexema) lexema es <id>
• LABEL(id) donde el lexema es id: 
• EOL
Además se generara un token especial para reportar errores:
• ERR(lexema) donde el lexema será el carácter invalido.
• Los espacios en blanco (<ws>) serán igorados i.e. no se generara ningún token.

En el programa, los tipos de token son definidos por enum Type: 
enum TokenType { ID, NUM, EOL, PUSH, JMPEQ, …, STORE, LOAD, ERR, END }
