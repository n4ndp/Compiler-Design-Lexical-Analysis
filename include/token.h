#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// Enumeración que define los tokens posibles.
enum Type {
    ID,
    NUM,
    EOL,

    PUSH,
    JMPEQ,
    JMPGT,
    JMPGE,
    JMPLT,
    JMPLE,

    SKIP,
    POP,
    DUP,
    SWAP,
    ADD,
    SUB,
    MULT,
    DIV, 
    STORE,
    LOAD,

    LABEL,
    GOTO,

    ERR,
    END
};

// Vector que almacena los nombres de los tokens.
const std::vector<std::string> tokenNames = {
    "ID",
    "NUM",
    "EOL",

    "PUSH",
    "JMPEQ",
    "JMPGT",
    "JMPGE",
    "JMPLT",
    "JMPLE",

    "SKIP",
    "POP",
    "DUP",
    "SWAP",
    "ADD",
    "SUB",
    "MULT",
    "DIV", 
    "STORE",
    "LOAD",

    "LABEL",
    "GOTO",

    "ERR",
    "END"
};

// Mapa que asocia palabras reservadas con sus tokens correspondientes.
const std::unordered_map<std::string, Type> keywordMap = {
    {"push", PUSH},
    {"jmpeq", JMPEQ},
    {"jmpgt", JMPGT},
    {"jmpge", JMPGE},
    {"jmplt", JMPLT},
    {"jmple", JMPLE},
    {"goto", GOTO},
    {"skip", SKIP},
    {"pop", POP},
    {"dup", DUP},
    {"swap", SWAP},
    {"add", ADD},
    {"sub", SUB},
    {"mult", MULT},
    {"div", DIV},
    {"store", STORE},
    {"load", LOAD}
};

// Estructura que representa un token.
struct Token {
    Type type;
    std::string lexeme;

    // Constructores.
    Token(Type t);
    Token(Type t, char c);
    Token(Type t, const std::string& s);
};

// Constructores.
Token::Token(Type t): type(t), lexeme("") { };
Token::Token(Type t, char c): type(t), lexeme(std::to_string(c)) { };
Token::Token(Type t, const std::string& s): type(t), lexeme(s) { };

// Sobrecarga del operador de salida para imprimir información de un Token.
std::ostream& operator<<(std::ostream& os, const Token& t) {
    os << tokenNames[t.type]; // Imprime el nombre del token.
    
    // Si el token tiene un lexema, lo imprime entre paréntesis.
    if (!t.lexeme.empty()) os << "(" << t.lexeme << ")";
    
    return os;
}

// Función que verifica si un token es una palabra reservada (keyword).
Token* isKW(const std::string& l) {
    auto it = keywordMap.find(l);
    if (it != keywordMap.end()) return new Token(it->second); // Devuelve un token correspondiente a la palabra reservada.

    return nullptr; // Si no es una palabra reservada, devuelve nullptr.
}

#endif // TOKEN_H
