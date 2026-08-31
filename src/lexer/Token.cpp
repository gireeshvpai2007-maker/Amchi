#include "Token.h"

Token::Token(TokenType type, const std::string& lexeme)
    : type(type), lexeme(lexeme)
{
}

TokenType Token::getType() const
{
    return type;
}

const std::string& Token::getLexeme() const
{
    return lexeme;
}

std::string Token::getTypeName() const
{
    switch (type)
    {
        case TokenType::GHE: return "GHE";
        case TokenType::DHAKE: return "DHAKE";
        case TokenType::NIMGI: return "NIMGI";
        case TokenType::JALLARI: return "JALLARI";
        case TokenType::NAJALLARI: return "NAJALLARI";
        case TokenType::JAVCHVARE: return "JAVCHVARE";

        case TokenType::KAAM: return "KAAM";
        case TokenType::VISHAY: return "VISHAY";
        case TokenType::SHURU: return "SHURU";
        case TokenType::JAAG: return "JAAG";

        case TokenType::NUMBER: return "NUMBER";
        case TokenType::STRING: return "STRING";
        case TokenType::IDENTIFIER: return "IDENTIFIER";

        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::DIVIDE: return "DIVIDE";
        case TokenType::MODULO: return "MODULO";

        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";

        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";

        case TokenType::AND: return "AND";
        case TokenType::OR: return "OR";
        case TokenType::NOT: return "NOT";

        case TokenType::INPUT: return "INPUT";

        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";

        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::COMMA: return "COMMA";

        case TokenType::TRUE: return "TRUE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::NULL_VALUE: return "NULL";

        case TokenType::UNKNOWN: return "UNKNOWN";
        case TokenType::END_OF_FILE: return "EOF";
    }

    return "UNKNOWN";
}