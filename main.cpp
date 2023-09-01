#include <iostream>
#include <fstream>
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

// Sobrecarga del operador de salida para imprimir información de un Token.
std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token_names[token.type]; // Imprime el nombre del tipo de token
    
    // Si el token tiene un lexema, lo imprime entre paréntesis
    if (!token.lexeme.empty())
        os << "(" << token.lexeme << ")";
    
    return os;
}

// Clase que representa el scanner.
class Scanner {  
private:
    std::string input;
    int first, current, state;

    // Obtener el siguiente carácter del input
    char nextChar() {
        char c = input[current];
        if (c != '\0')
            current++;
        return c;
    }

    // Retroceder la posición actual en el input
    void rollBack() {
        if (input[current] != '\0')
            current--;
        return;
    }

    // Iniciar el índice del lexema
    void startLexeme() {
        first = current-1;  
        return;
    }

    // Incrementar el índice del lexema
    void incrStartLexeme() {
        first++;
    }

    // Obtener el lexema actual
    std::string getLexeme() {
        return input.substr(first,current-first);
    }

public:
    Scanner(const char* in): input(in), first(0), current(0), state(0) {}
    Token* nextToken() {
        // Aquí es donde implementarás la lógica para reconocer tokens
        // basados en el autómata finito y los estados definidos.
        // Retorna el token apropiado en cada caso.
    }
    ~Scanner() = default;
};




