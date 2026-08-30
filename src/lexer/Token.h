#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {

    GHE,
    DHAKE,
    NIMGI,
    JALLARI,
    NAJALLARI,
    JAVCHVARE,
    KAAM,
    VISHAY,
    SHURU,
    JAAG,

    NUMBER,
    STRING,
    TRUE,
    FALSE,
    NULL_VALUE,

    IDENTIFIER,

    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,

    ASSIGN,

    EQUAL_EQUAL,
    NOT_EQUAL,
    GREATER,
    LESS,
    GREATER_EQUAL,
    LESS_EQUAL,

    AND,
    OR,
    NOT,

    INPUT,

    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    COMMA,

    END_OF_FILE,
    UNKNOWN
};

std::string tokenTypeToString(TokenType type);

class Token {

public:

    Token(TokenType type, const std::string& lexeme);

    TokenType getType() const;
    std::string getLexeme() const;

private:

    TokenType type;
    std::string lexeme;
};

#endif