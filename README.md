# **Compiler Design | `Lexical Analysis`**

Design and implementation of a lexical analyzer (`scanner`) for the SM (Stack Machine Language) defined in the first section. The lexical analyzer is a fundamental part of a compiler and breaks down the source code into smaller units called tokens to facilitate subsequent processing and analysis.

## **SM (Stack Machine Language)**

The following grammar establishes the basic structure of instructions in the SM language, including the possibility of labels, jump instructions, and unary operations.

```plaintext
<program>       ::= <instruction>+
<instruction>   ::= <label>? (<unaryinstr> | <opinstr> <num> | <jmpinstr> <id>) <eol>
<unaryinstr>    ::= skip | pop | dup | swap | add | sub | mul | div | print
<opinstr>       ::= push | store | load
<jmpinstr>      ::= jmpeq | jmpgt | jmpge | jmplt | jmple | goto
```

The lexical specification defines rules to recognize tokens and lexemes in the SM source code. Here are the regular expressions used:

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

According to these lexical rules, lexical units like `<id>`, `<num>`, `<eol>`, and all reserved words become tokens. However, the `<ws>` pattern, representing whitespace, does not generate tokens and is ignored. Token names are written in uppercase and match the corresponding lexical units.

## **Example input and output**

**input**: example0.svm

```plaintext
push 3


L1: jmpgt
mul
add
goto L2

```

**output**:

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
