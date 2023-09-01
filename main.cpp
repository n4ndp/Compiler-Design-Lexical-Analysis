#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

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
    GOTO,
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
    "GOTO",
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
    "ERR",
    "END"
};

// Mapa que asocia palabras reservadas con sus tipos de token correspondientes.
const std::map<std::string, Type> keywordMap = {
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
    Token(Type t, const std::string s): type(t), lexeme(s) {};
};


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
    if (it != keywordMap.end())
        return new Token(it->second); // Devuelve un nuevo token con el tipo de token correspondiente a la palabra reservada.

    return nullptr; // Si el lexema no es una palabra reservada, devuelve nullptr (nulo).
}


// Clase que representa el scanner.
class Scanner {  
private:
    std::string input;
    int first, current, state;

    // Obtener el siguiente carácter del input
    char nextChar() {
        char c = input[current];
            current++;
        return c;
    }

    // Retroceder la posición actual en el input
    void rollBack() {
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
        Token* token;
        char c = nextChar();

        while (1) {
            switch (state) {
                case 0: {
                    // Estado inicial del autómata. Aquí se decide qué tipo de token reconocer.

                    if (c == ' ' || c == '\t') {
                        // Si el carácter es un espacio en blanco o una tabulación, avanzamos al siguiente carácter.
                        c = nextChar();
                    } else if (isalpha(c)) {
                        // Si el carácter es una letra, pasamos al estado 1 para reconocer palabras reservadas y IDs.
                        state = 1;
                    } else if (isdigit(c)) {
                        // Si el carácter es un dígito, pasamos al estado 2 para reconocer números.
                        state = 2;
                    } else if (c == ':') {
                        // Si el carácter es ':', cambiamos al estado 3 para reconocer etiquetas.
                        state = 3;
                    } else if (c == '\n') {
                        // Si el carácter es un salto de línea, pasamos al estado 4 para reconocer fin de línea.
                        state = 4;
                    } else if (c == '\0') {
                        // Si el carácter es el final del archivo, pasamos al estado 5 para reconocer fin de archivo.
                        state = 5;
                    } else {
                        // Si el carácter no coincide con ninguno de los casos anteriores, es un error.
                        token = new Token(ERR, std::string(1, c)); // Crear un token de error.
                        state = 0; // Regresamos al estado inicial para reconocer el próximo token.
                    }

                    break;
                }
                case 1: {
                    // Estado para reconocer palabras reservadas y IDs.
                    startLexeme();

                    while (isalnum(c) || c == '_') {
                        // Mientras el carácter actual sea alfanumérico o un '_', avanzamos en el lexema.
                        c = nextChar();
                    }

                    if (c == ':') {
                        // Si el próximo carácter es ':', cambiamos al estado 3 para reconocer etiquetas.
                        state = 3;
                    } else {
                        // Si el próximo carácter no es ':', puede ser una palabra reservada válida o un ID.

                        rollBack(); // Retrocedemos para no incluir el último carácter no alfanumérico.
                        std::string lexeme = getLexeme(); // Obtenemos el lexema acumulado.
                        Token* keywordToken = isKW(lexeme); // Verificamos si el lexema es una palabra reservada o un ID.

                        if (keywordToken) {
                            // Si es una palabra reservada, usamos el token de palabra reservada.
                            token = keywordToken;
                            state = 0; // Regresamos al estado inicial para reconocer el próximo token.
                        } else {
                             if (lexeme == "goto") {
                                // GOTO
                                token = new Token(GOTO);
                                state = 3; // Cambiamos al estado 3 para reconocer etiquetas.
                             } else {
                                // Si no es una palabra reservada, asumimos que es un ID.
                                token = new Token(ID, lexeme);
                                state = 0; // Regresamos al estado inicial para reconocer el próximo token.
                             }
                        }

                        return token;
                    }

                    break;
                }
                case 2: {
                    // Estado para reconocer números.
                    startLexeme();

                    while (isdigit(c)) {
                        // Mientras el carácter actual sea un dígito, avanzamos en el lexema.
                        c = nextChar();
                    }

                    rollBack(); // Retrocedemos para no incluir el último carácter no numérico.
                    std::string lexeme = getLexeme(); // Obtenemos el lexema acumulado.
                    token = new Token(NUM, lexeme); // Creamos un token de tipo NUM con el lexema.

                    state = 0; // Regresamos al estado inicial para reconocer el próximo token.

                    return token;

                    break;
                }
                case 3: {
                    // Estado para reconocer etiquetas.

                    rollBack(); // Retrocedemos para no incluir el último carácter no alfanumérico (acumulado en case 1).

                    std::string lexeme = getLexeme(); // Obtenemos el lexema acumulado.
                    
                    // GOTO
                    if(lexeme == "goto") {
                        // goto + espacio + label
                        c = nextChar();
                        c = nextChar();

                        // Reiniciamos el lexema
                        startLexeme();
                        while (isalnum(c) || c == '_') {
                            // Mientras el carácter actual sea alfanumérico o un '_', avanzamos en el lexema.
                            c = nextChar();
                        }
                        rollBack(); // Retrocedemos para no incluir el último carácter no alfanumérico.

                        lexeme = getLexeme(); // Actualizamos el lexema

                        token = new Token(LABEL, lexeme); // Creamos un token de tipo LABEL con el lexema.
                        state = 0; // Regresamos al estado inicial.
                    } else {
                        token = new Token(LABEL, lexeme); // Creamos un token de tipo LABEL con el lexema.
                        state = 0; // Regresamos al estado inicial.

                        c = nextChar();
                    }

                    return token;
                }
                case 4: {
                    // Estado para reconocer fin de línea.
                    startLexeme();

                    token = new Token(EOL); // Creamos un token de tipo EOL.
                    state = 0; // Regresamos al estado inicial.
                    return token;
                }
                case 5: {
                    // Estado para reconocer fin de archivo.
                    startLexeme();
                    
                    token = new Token(END); // Creamos un token de tipo END.
                    return token; // Salimos del bucle ya que no hay más tokens.
                }
            }
        }

    }
    ~Scanner() = default;
};

int main(int argc, char** argv) {
    std::fstream file(argv[1], std::ios::in);
    std::stringstream stream;
    stream << file.rdbuf();

    Scanner scanner(stream.str().c_str());

    Token* tk = scanner.nextToken();
    while (tk->type != END) {
        std::cout << "next token " << *tk << std::endl;
        delete tk;
        tk =  scanner.nextToken();
    }

    return 0;
}
