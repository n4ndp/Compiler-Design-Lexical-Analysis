# **Compiler Design | Lexical Analysis**

Este repositorio contiene la implementación de un analizador léxico (`Scanner`) en el lenguaje de programación C++ para el lenguaje de la máquina de pila SM.

## 1. Sintaxis de SM

El lenguaje de máquina de pila SM está definido por la siguiente gramática:

```plaintext
<program> ::= <instruction>+
<instruction> ::= Label? ((<jmpinstr> <id>) | <unaryinstr> | (push <num>) <eol>)
<jmpinstr> ::= jmpeq | jmpgt | jmpge | jmplt | jmple | goto
<unaryinstr> ::= skip | pop | dup | swap | add | sub | mul | div | store | load
```

### Especificación Léxica

La especificación léxica está dada por los siguientes patrones (expresiones regulares):

```plaintext
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

### Tokens Generados

- Las unidades léxicas `<id>`, `<num>` y `<eol>`, y `<reserved-word>`, generan un token.
- El patrón `<ws>` no genera token; denota los espacios en blanco y se ignoran.
- Los tokens llevan el nombre de sus unidades léxicas pero en mayúscula. Por ejemplo, el token `NUM` denota la unidad léxica `<num>`.
- Solo los tokens correspondientes a `<num>` y `<id>` tendrán como atributo al lexema.
- Resumiendo, los tokens a generar son:

  - Un tipo de token por cada palabra reservada, con el mismo nombre del lexema. Por ejemplo, la palabra reservada "pop" generará el token `POP`. Así tendremos `PUSH`, `JMPEQ`, `JMPGT`, ..., `STORE`, `LOAD`.
  - `NUM(lexema)` donde el lexema es `<num>`.
  - `ID(lexema)` donde el lexema es `<id>`.
  - `LABEL(id)` donde el lexema es `id:`.
  - `EOL`.
  
Además, se generará un token especial para reportar errores:

- `ERR(lexema)` donde el lexema será el carácter inválido.
- Los espacios en blanco (`<ws>`) serán ignorados, es decir, no se generará ningún token.

En el programa, los tipos de token son definidos por el enumerado `enum Type`:

```cpp
enum Type {
    ID,
    NUM,
    EOL,
    PUSH,
    JMPEQ,
    // ... (otros tokens)
    STORE,
    LOAD,
    ERR,
    END
}
```
```

Este es un resumen de la sintaxis y especificaciones léxicas del lenguaje SM.
```