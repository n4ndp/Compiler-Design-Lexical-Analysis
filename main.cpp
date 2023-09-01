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
        Token* token;
        char c = nextChar();

        startLexeme();

        while (1) {
            switch (state) {
                case 0: {
                    // Estado inicial del autómata. Aquí se decide qué tipo de token reconocer.

                    if (c == ' ' || c == '\t') // Si el carácter es un espacio en blanco o una tabulación, avanzamos al siguiente carácter.
                        c = nextChar();
                    else if (isalpha(c)) // Si el carácter es una letra, pasamos al estado 1 para reconocer palabras reservadas y IDs.
                        state = 1;
                    else if (isdigit(c)) // Si el carácter es un dígito, pasamos al estado 2 para reconocer números.
                        state = 2;
                    else if (c == ':') // Si el carácter es ':' podemos estar en proceso de reconocer una etiqueta.
                        state = 3;
                    else if (c == '\n') // Si el carácter es un salto de línea, pasamos al estado 4 para reconocer fin de línea.
                        state = 4;
                    else if (c == '\0') // Si el carácter es el final del archivo, pasamos al estado 5 para reconocer fin de archivo.
                        state = 5;
                    break;
                }
                case 1: {
                    // Implementar lógica para reconocer palabras reservadas y IDs
                    break;
                }
                case 2: {
                    // Implementar lógica para reconocer números
                    break;
                }
                case 3: {
                    // Implementar lógica para reconocer etiquetas
                    break;
                }
                case 4: {
                    // Implementar lógica para reconocer fin de línea
                    break;
                }
                case 5: {
                    // Implementar lógica para reconocer fin de archivo
                    break;
                }
            }
        }

    }
    ~Scanner() = default;
};
