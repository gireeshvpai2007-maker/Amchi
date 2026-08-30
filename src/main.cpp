#include <iostream>
#include <vector>
#include <memory>

#include "lexer/Lexer.h"
#include "parser/parser.h"
#include "ast/ast.h"

int main()
{std::string source = R"(
    ghe a = 10 + 20 * 3;
    ghe b = (10 + 20) * 3;
    ghe c = a > b;
)";
    // ===============================
    // Lexical Analysis
    // ===============================

    Lexer lexer(source);

    std::vector<Token> tokens = lexer.tokenize();

    std::cout << "=== TOKENS ===\n\n";

    for (const Token& token : tokens)
    {
        std::cout
            << tokenTypeToString(token.getType())
            << " : "
            << token.getLexeme()
            << "\n";
    }


    // ===============================
    // Parsing
    // ===============================

    std::cout << "\n=== AST ===\n\n";

    try
    {
        Parser parser(tokens);

        std::vector<ASTNodePtr> ast = parser.parse();

        for (const ASTNodePtr& node : ast)
        {
            std::cout << node->toString() << "\n";
        }
    }
    catch (const std::exception& error)
    {
        std::cerr
            << "Parser error: "
            << error.what()
            << "\n";

        return 1;
    }

    return 0;
}