#include "Token.h"

Token::Token(TokenType type, const std::string& lexeme)
    : type(type), lexeme(lexeme)
{
}

TokenType Token::getType() const
{
    return type;
}

std::string Token::getLexeme() const
{
    return lexeme;
}