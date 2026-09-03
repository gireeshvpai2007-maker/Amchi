#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include <string>

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

    bool isAtEnd();
    Token peek();
    Token previous();
    Token advance();

    bool check(TokenType type);
    bool match(TokenType type);

    Token consume(
        TokenType type,
        const std::string& message
    );

    ASTNodePtr statement();
    ASTNodePtr variableDeclaration();
    ASTNodePtr functionDeclaration();
    ASTNodePtr ifStatement();
    ASTNodePtr block();

    ASTNodePtr expression();
    ASTNodePtr assignment();
    ASTNodePtr orExpression();
    ASTNodePtr andExpression();
    ASTNodePtr equality();
    ASTNodePtr comparison();
    ASTNodePtr term();
    ASTNodePtr factor();
    ASTNodePtr unary();
    ASTNodePtr call();
    ASTNodePtr primary();
};

#endif