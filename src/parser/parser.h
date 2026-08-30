#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>

#include "../lexer/Token.h"
#include "../ast/ast.h"

class Parser
{
public:
    Parser(const std::vector<Token>& tokens);

    std::vector<ASTNodePtr> parse();

private:
    const std::vector<Token>& tokens;
    int current;

    // Utility
    bool isAtEnd();
    Token peek();
    Token previous();
    Token advance();

    bool check(TokenType type);
    bool match(TokenType type);

    Token consume(TokenType type, const std::string& message);

    // Expressions
    ASTNodePtr expression();
    ASTNodePtr primary();

    // Statements
    ASTNodePtr statement();
    ASTNodePtr variableDeclaration();

    // Functions
    ASTNodePtr functionDeclaration();
};

#endif