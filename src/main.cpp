#include "../include/scanner.h"
#include <fstream>
#include <sstream>

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
