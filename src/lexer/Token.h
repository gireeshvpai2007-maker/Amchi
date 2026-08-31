#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
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
    GREATER_EQUAL,
    LESS,
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

    TRUE,
    FALSE,
    NULL_VALUE,

    UNKNOWN,
    END_OF_FILE
};

class Token
{
public:

    Token(TokenType type, const std::string& lexeme);

    TokenType getType() const;

    const std::string& getLexeme() const;

    std::string getTypeName() const;

private:

    TokenType type;
    std::string lexeme;
};

#endif