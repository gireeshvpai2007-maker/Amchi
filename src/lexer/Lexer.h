#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

class Lexer {

public:

    Lexer(const std::string& source);

    std::vector<Token> tokenize();

private:

    std::string source;
    std::vector<Token> tokens;

    int current;
    int start;

    void scanToken();

    char advance();
    char peek();
    char peekNext();

    bool match(char expected);

    void addToken(TokenType type);
    void addToken(TokenType type, const std::string& lexeme);

    void identifier();
    void number();
    void string();

    bool isDigit(char c);
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);

    TokenType keywordType(const std::string& text);
};

#endif