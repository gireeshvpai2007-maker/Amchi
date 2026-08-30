#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "../lexer/Token.h"

class Parser {

public:

    Parser(const std::vector<Token>& tokens);

    void parse();

private:

    std::vector<Token> tokens;
    int current;

    void functionDeclaration();
    void block();

    void statement();
    void variableDeclaration();
    void printStatement();
    void expressionStatement();

    void expression();
    void addition();
    void primary();

    bool match(TokenType type);
    bool match(TokenType type1, TokenType type2);

    bool check(TokenType type);
    bool isAtEnd();

    Token advance();
    Token peek();
    Token previous();

    Token consume(TokenType type, const std::string& message);
};

#endif