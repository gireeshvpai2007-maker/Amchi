#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {

    // ---------- Keywords ----------
    GHE,            // variable
    DHAKE,          // print
    NIMGI,          // input
    JALLARI,        // if
    NAJALLARI,      // else
    JAVCHVARE,      // while
    KAAM,           // function
    VISHAY,         // class
    SHURU,          // main
    JAAG,           // address-of

    // ---------- Literals ----------
    NUMBER,
    STRING,
    TRUE,
    FALSE,
    NULL_VALUE,

    // ---------- Identifier ----------
    IDENTIFIER,

    // ---------- Arithmetic Operators ----------
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,

    // ---------- Assignment ----------
    ASSIGN,

    // ---------- Comparison ----------
    EQUAL_EQUAL,
    NOT_EQUAL,
    GREATER,
    LESS,
    GREATER_EQUAL,
    LESS_EQUAL,

    // ---------- Logical ----------
    AND,
    OR,
    NOT,

    // ---------- Input ----------
    INPUT,

    // ---------- Symbols ----------
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    COMMA,

    // ---------- Special ----------
    END_OF_FILE,
    UNKNOWN
};


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