# **Compiler Design | `Lexical Analysis`**

La siguiente gramática define la estructura y organización de las instrucciones en el lenguaje SM:

```plaintext
<program>       ::= <instruction>+
<instruction>   ::= Label? ((<jmpinstr> <id>) | <unaryinstr> | (push <num>) <eol>)
<jmpinstr>      ::= jmpeq | jmpgt | jmpge | jmplt | jmple | goto
<unaryinstr>    ::= skip | pop | dup | swap | add | sub | mul | div | store | load
```

La especificación léxica describe las reglas para reconocer tokens y lexemas en el código fuente SM. Aquí están las expresiones regulares que se utilizan:

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

Las unidades léxicas, como `<id>`, `<num>`, `<eol>` y todas las palabras reservadas, se convierten en tokens. Sin embargo, el patrón `<ws>`, que representa espacios en blanco, no genera tokens y se prefiere ignorarlos. Los nombres de los tokens se escriben en mayúsculas y coinciden con las unidades léxicas correspondientes. Solo los tokens correspondientes a `<num>` y `<id>` tendrán como atributo al lexema. Además, se han definido dos tokens especiales para señalar errores y el final del archivo.

En resumen, los tipos de tokens generados son:
- Un token por cada palabra reservada, con un nombre idéntico al lexema. Por ejemplo, la palabra reservada "pop" genera el token `POP`. Así, tenemos `PUSH`, `JMPEQ`, `JMPGT`, …, `STORE`, `LOAD`.
- `NUM(lexema)`, donde lexema es igual a `<num>`.
- `ID(lexema)`, donde lexema es igual a `<id>`.
- `LABEL(id)`, donde el lexema corresponde a `id:`.
- `EOL` y `END`.
- `ERR(lexema)`, donde el lexema será el carácter inválido.
