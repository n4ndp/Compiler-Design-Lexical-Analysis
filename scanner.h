#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

// Clase que representa el scanner.
class Scanner {
private:
    std::string input;
    int first, current, state;

public:
    Scanner(const char* in);
    ~Scanner();
    Token* nextToken();

private:
    char nextChar(); // Obtener el siguiente carácter del input.
    void rollBack(); // Retroceder la posición actual en el input.
    void startLexeme(); // Iniciar el índice del lexema.
    void incrStartLexeme(); // Incrementar el índice del lexema.
    std::string getLexeme(); // Obtener el lexema actual.
};

Scanner::Scanner(const char* in): input(in), first(0), current(0), state(0) { }

Scanner::~Scanner() { }

// Obtener el siguiente carácter del input.
char Scanner::nextChar() {
    int c = input[current];
    if (c != '\0') current++;
    return c;
}

// Retroceder la posición actual en el input.
void Scanner::rollBack() {
    /*if (input[current] != '\0') */current--;
    return;
}

// Iniciar el índice del lexema.
void Scanner::startLexeme() {
    first = current-1;  
    return;
}

// Incrementar el índice del lexema.
void Scanner::incrStartLexeme() {
    first++;
    return;
}

// Obtener el lexema actual.
std::string Scanner::getLexeme() {
    return input.substr(first,current-first);
}

// Analizador
Token* Scanner::nextToken() {
    Token* token;
    char c = nextChar();

    while (true) {
        switch (state) {
            case 0: { // Estado inicial del autómata (reconocedor).
                if (c == ' ' || c == '\t') c = nextChar(); // Si el carácter es un espacio en blanco o una tabulación, avanzamos al siguiente carácter.
                else if (isalpha(c)) state = 1; // Si el carácter es una letra, pasamos al estado 1 para reconocer palabras reservadas y IDs.
                else if (isdigit(c)) state = 2; // Si el carácter es un dígito, pasamos al estado 2 para reconocer números.
                else if (c == ':') state = 3; // Si el carácter es ':', cambiamos al estado 3 para reconocer etiquetas.
                else if (c == '\n') state = 4; // Si el carácter es un salto de línea, pasamos al estado 4 para reconocer fin de línea.
                else if (c == '\0') state = 5; // Si el carácter es el final del archivo, pasamos al estado 5 para reconocer fin de archivo.
                else { 
                    // Si el carácter no coincide con ninguno de los casos anteriores, es un error.
                    token = new Token(ERR);
                    state = 0; // Regresamos al estado inicial para reconocer el próximo token.

                    return token;
                }

                break;
            }
            case 1: { // Estado para reconocer palabras reservadas y IDs.
                startLexeme();
                while (isalnum(c) || c == '_') c = nextChar();

                if (c == ':') state = 3; // Si el próximo carácter es ':', cambiamos al estado 3 para reconocer etiquetas.
                else {
                    // Si el próximo carácter no es ':', puede ser una palabra reservada válida o un ID.
                    rollBack(); // Retrocedemos para no incluir el último carácter no alfanumérico.
                    std::string lexeme = getLexeme(); // Obtenemos el lexema acumulado.
                    Token* keywordToken = isKW(lexeme); // Verificamos si el lexema es una palabra reservada o un ID.

                    if (keywordToken) token = keywordToken;
                    else {
                        if (lexeme == "goto") token = new Token(GOTO);
                        else token = new Token(ID, lexeme);
                    }
                    state = 0; // Regresamos al estado inicial para reconocer el próximo token.

                    return token;
                }

                break;
            }
            case 2: { // Estado para reconocer números.
                startLexeme();
                while (isdigit(c)) c = nextChar();

                rollBack(); // Retrocedemos para no incluir el último carácter no numérico.
                std::string lexeme = getLexeme(); // Obtenemos el lexema acumulado.
                token = new Token(NUM, lexeme);
                state = 0; // Regresamos al estado inicial para reconocer el próximo token.

                return token;
            }
            case 3: { // Estado para reconocer etiquetas.
                rollBack(); // Retrocedemos para no incluir el último carácter no alfanumérico (acumulado en case 1).
                std::string lexeme = getLexeme(); // Obtenemos el lexema acumulado.
                token = new Token(LABEL, lexeme);
                state = 0; // Regresamos al estado inicial para reconocer el próximo token.

                c = nextChar(); // Para omitir el carácter ':' luego de la etiqueta.

                return token;
            }
            case 4: { // Estado para reconocer fin de línea.
                startLexeme();

                token = new Token(EOL); // Creamos un token de tipo EOL.
                state = 0; // Regresamos al estado inicial.

                return token;
            }
            case 5: { // Estado para reconocer fin de archivo.
                startLexeme();
                    
                token = new Token(END);
                return token;
            }
        }
    }
}

#endif // SCANNER_H
