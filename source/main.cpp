#include "../include/scanner.h"
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    std::fstream file(argv[1], std::ios::in);
    std::stringstream stream;
    stream << file.rdbuf();

    Scanner scanner(stream.str().c_str());

    Token* tk = scanner.next_token();
    while (tk->type != Token::END) {
        std::cout << "next token " << *tk << std::endl;
        delete tk;
        tk =  scanner.next_token();
    }

    return 0;
}
