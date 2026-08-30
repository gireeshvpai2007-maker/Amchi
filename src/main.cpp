#include <iostream>
#include "lexer/Lexer.h"

int main()
{
    std::string source = R"(
        kaam shuru() {
            ghe a = 10;
            ghe b = 20;

            dhake(a + b);
        }
    )";

    Lexer lexer(source);

    std::vector<Token> tokens = lexer.tokenize();

    for (const Token& token : tokens)
    {
        std::cout << tokenTypeToString(token.getType())
          << " : "
          << token.getLexeme()
          << std::endl;
    }

    return 0;
}