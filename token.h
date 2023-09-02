#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// Enumeración que define los tipos de tokens posibles.
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

// Vector que almacena los nombres de los tokens en el mismo orden que la enumeración Type.
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

// Mapa que asocia palabras reservadas con sus tipos de token correspondientes.
const std::unordered_map<std::string, Type> keywordMap = {
    {"push", PUSH},
    {"jmpeq", JMPEQ},
    {"jmpgt", JMPGT},
    {"jmpge", JMPGE},
    {"jmplt", JMPLT},
    {"jmple", JMPLE},
    //{"goto", GOTO},
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

    Token(Type t); // Constructor para tokens sin lexema.
    Token(Type t, char c); // Constructor para tokens con lexema numérico o caracter.
    Token(Type t, const std::string& s); // Constructor para tokens con lexema de cadena.
};

Token::Token(Type t): type(t), lexeme("") { }; // Constructor para tokens sin lexema.

Token::Token(Type t, char c): type(t), lexeme(std::to_string(c)) { }; // Constructor para tokens con lexema numérico o caracter.

Token::Token(Type t, const std::string& s): type(t), lexeme(s) { }; // Constructor para tokens con lexema de cadena.

// Sobrecarga del operador de salida para imprimir información de un Token.
std::ostream& operator<<(std::ostream& os, const Token& t) {
    os << tokenNames[t.type]; // Imprime el nombre del tipo de token
    
    // Si el token tiene un lexema, lo imprime entre paréntesis
    if (!t.lexeme.empty())
        os << "(" << t.lexeme << ")";
    
    return os;
}

// Función que verifica si un lexema es una palabra reservada (keyword).
Token* isKW(const std::string& l) {
    auto it = keywordMap.find(l);
    if (it != keywordMap.end()) return new Token(it->second); // Devuelve un nuevo token con el tipo de token correspondiente a la palabra reservada.

    return nullptr; // Si el lexema no es una palabra reservada, devuelve nullptr (nulo).
}

#endif // TOKEN_H
