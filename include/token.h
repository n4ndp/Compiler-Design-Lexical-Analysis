#ifndef Lexical_Analysis_TOKEN_H
#define Lexical_Analysis_TOKEN_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <unordered_map>

struct Token {
    enum Type { ID=0, LABEL, NUM, EOL, ERR, END, 
                PUSH, JMPEQ, JMPGT, JMPGE, JMPLT, JMPLE, 
                GOTO, SKIP, POP, DUP, SWAP, 
                ADD, SUB, MUL, DIV, STORE, LOAD };
    static const char* token_names[23];

    Type type;
    std::string lexeme;

    Token(Type);
    Token(Type, char);
    Token(Type, const std::string&);
};

const char* Token::token_names[23] = { "ID", "LABEL", "NUM", "EOL", "ERR", "END", 
                                       "PUSH", "JMEPEQ", "JMPGT", "JMPGE", "JMPLT", "JMPLE", 
                                       "GOTO", "SKIP", "POP", "DUP", "SWAP", 
                                       "ADD", "SUB", "MUL", "DIV", "STORE", "LOAD" };

Token::Token(Type t): type(t) { lexeme = ""; }
Token::Token(Type t, char c): type(t) { lexeme = c; }
Token::Token(Type t, const std::string& source): type(t) { lexeme = source; }

std::ostream& operator<<(std::ostream& stream, const Token& token) {
    stream << Token::token_names[token.type];
    if (!token.lexeme.empty()) stream << "(" << token.lexeme << ")";
    
    return stream;
}

#endif // Lexical_Analysis_TOKEN_H
