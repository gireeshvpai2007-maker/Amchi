#include <iostream>
#include <string>
#include <vector>

#include "lexer/Lexer.h"
#include "parser/parser.h"
#include "interpreter/interpreter.h"

int main()
{
    std::string source = R"(
kaam shuru {
    ghe a = 10;
    ghe b = 20;

    jallari (a > b) {
        dhake("a is greater");
    }

    najallari {
        dhake("b is greater");
    }
}
)";

    // ============================================================
    // LEXER
    // ============================================================

    Lexer lexer(source);

    std::vector<Token> tokens = lexer.tokenize();

    std::cout << "===== TOKENS =====\n";

    for (const auto& token : tokens)
    {
        std::cout
            << token.getTypeName()
            << " : "
            << token.getLexeme()
            << '\n';
    }


    // ============================================================
    // PARSER
    // ============================================================

    Parser parser(tokens);

    std::vector<ASTNodePtr> statements = parser.parse();

    std::cout << "\n===== AST =====\n";

    for (const auto& statement : statements)
    {
        std::cout << statement->toString() << '\n';
    }


    // ============================================================
    // INTERPRETER
    // ============================================================

    std::cout << "\n===== OUTPUT =====\n";

    Interpreter interpreter;

    interpreter.interpret(statements);

    return 0;
}