#include <iostream>
#include <string>
#include <vector>

// Enumeración que define los tipos de tokens posibles.
enum Type {
    ID, NUM, EOL, 
    PUSH, 
    JMPEQ, JMPGT, JMPGE, JMPLT, JMPLE, GOTO, SKIP, 
    POP, DUP, SWAP, ADD, SUB, MUL, DIV, 
    STORE, LOAD, LABEL, 
    ERR, END
};

// Vector que almacena los nombres de los tokens en el mismo orden que la enumeración Type.
std::vector<std::string> token_names = {
    "ID", "NUM", "EOL", 
    "PUSH", 
    "JMPEQ", "JMPGT", "JMPGE", "JMPLT", "JMPLE", "GOTO", "SKIP", 
    "POP", "DUP", "SWAP", "ADD", "SUB", "MUL", "DIV", 
    "STORE", "LOAD", "LABEL", 
    "ERR", "END"
};

// Clase que representa un token.
class Token {
public:
    Type type;
    std::string lexeme;

    // Constructor para tokens sin lexema.
    Token(Type t): type(t), lexeme("") {};

    // Constructor para tokens con lexema numérico o caracter.
    Token(Type t, char c): type(t), lexeme(std::to_string(c)) {};

    // Constructor para tokens con lexema de cadena.
    Token(Type t, const std::string source): type(t), lexeme(source) {};
};

