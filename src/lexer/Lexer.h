#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "Token.h"

class Lexer
{
public:
    explicit Lexer(const std::string& source);

    // Convert source code into tokens
    std::vector<Token> tokenize();

private:
    std::string source;

    // Keep the same order as the constructor initializer
    int current;
    int start;

    std::vector<Token> tokens;

    // Main scanner
    void scanToken();

    // Character utilities
    char advance();
    char peek();
    char peekNext();

    bool match(char expected);

    // Token creation
    void addToken(TokenType type);
    void addToken(
        TokenType type,
        const std::string& lexeme
    );

    // Lexing helpers
    void identifier();
    void number();
    void string();

    // Character checks
    static bool isDigit(char c);
    static bool isAlpha(char c);
    static bool isAlphaNumeric(char c);

    // Keyword handling
    TokenType keywordType(const std::string& text);
};

#endif