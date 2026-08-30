#include "Parser.h"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0)
{
}

void Parser::parse()
{
    while (!isAtEnd())
    {
        functionDeclaration();
    }

    std::cout << "Parsing completed successfully.\n";
}

void Parser::functionDeclaration()
{
    consume(
        TokenType::KAAM,
        "Expected 'kaam' at beginning of function."
    );

    consume(
        TokenType::IDENTIFIER,
        "Expected function name."
    );

    consume(
        TokenType::LEFT_PAREN,
        "Expected '(' after function name."
    );

    consume(
        TokenType::RIGHT_PAREN,
        "Expected ')' after function parameters."
    );

    block();
}

void Parser::block()
{
    consume(
        TokenType::LEFT_BRACE,
        "Expected '{' before function body."
    );

    while (!check(TokenType::RIGHT_BRACE) &&
           !isAtEnd())
    {
        statement();
    }

    consume(
        TokenType::RIGHT_BRACE,
        "Expected '}' after function body."
    );
}

void Parser::statement()
{
    if (match(TokenType::GHE))
    {
        variableDeclaration();
    }
    else if (match(TokenType::DHAKE))
    {
        printStatement();
    }
    else
    {
        expressionStatement();
    }
}

void Parser::variableDeclaration()
{
    consume(
        TokenType::IDENTIFIER,
        "Expected variable name after 'ghe'."
    );

    consume(
        TokenType::ASSIGN,
        "Expected '=' after variable name."
    );

    expression();

    consume(
        TokenType::SEMICOLON,
        "Expected ';' after variable declaration."
    );
}

void Parser::printStatement()
{
    consume(
        TokenType::LEFT_PAREN,
        "Expected '(' after 'dhake'."
    );

    expression();

    consume(
        TokenType::RIGHT_PAREN,
        "Expected ')' after expression."
    );

    consume(
        TokenType::SEMICOLON,
        "Expected ';' after print statement."
    );
}

void Parser::expressionStatement()
{
    expression();

    consume(
        TokenType::SEMICOLON,
        "Expected ';' after expression."
    );
}

void Parser::expression()
{
    addition();
}

void Parser::addition()
{
    primary();

    while (match(TokenType::PLUS, TokenType::MINUS))
    {
        primary();
    }
}

void Parser::primary()
{
    if (match(TokenType::NUMBER))
    {
        return;
    }

    if (match(TokenType::STRING))
    {
        return;
    }

    if (match(TokenType::IDENTIFIER))
    {
        return;
    }

    if (match(TokenType::TRUE))
    {
        return;
    }

    if (match(TokenType::FALSE))
    {
        return;
    }

    if (match(TokenType::NULL_VALUE))
    {
        return;
    }

    if (match(TokenType::LEFT_PAREN))
    {
        expression();

        consume(
            TokenType::RIGHT_PAREN,
            "Expected ')' after expression."
        );

        return;
    }

    std::cerr
        << "Parser error: Expected expression near '"
        << peek().getLexeme()
        << "'\n";

    advance();
}

bool Parser::match(TokenType type)
{
    if (!check(type))
    {
        return false;
    }

    advance();

    return true;
}

bool Parser::match(TokenType type1, TokenType type2)
{
    if (check(type1))
    {
        advance();
        return true;
    }

    if (check(type2))
    {
        advance();
        return true;
    }

    return false;
}

bool Parser::check(TokenType type)
{
    if (isAtEnd())
    {
        return type == TokenType::END_OF_FILE;
    }

    return peek().getType() == type;
}

bool Parser::isAtEnd()
{
    return peek().getType() == TokenType::END_OF_FILE;
}

Token Parser::advance()
{
    if (!isAtEnd())
    {
        current++;
    }

    return previous();
}

Token Parser::peek()
{
    return tokens[current];
}

Token Parser::previous()
{
    return tokens[current - 1];
}

Token Parser::consume(
    TokenType type,
    const std::string& message
)
{
    if (check(type))
    {
        return advance();
    }

    std::cerr
        << "Parser error: "
        << message
        << " Found '"
        << peek().getLexeme()
        << "' instead.\n";

    return peek();
}