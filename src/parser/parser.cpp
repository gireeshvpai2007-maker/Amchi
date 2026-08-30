#include "parser.h"

#include <iostream>
#include <stdexcept>


Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0)
{
}


// ===============================
// Parser Entry Point
// ===============================

std::vector<ASTNodePtr> Parser::parse()
{
    std::vector<ASTNodePtr> statements;

    while (!isAtEnd())
    {
        statements.push_back(statement());
    }

    return statements;
}


// ===============================
// Utility Functions
// ===============================

bool Parser::isAtEnd()
{
    return peek().getType() == TokenType::END_OF_FILE;
}


Token Parser::peek()
{
    return tokens[current];
}


Token Parser::previous()
{
    return tokens[current - 1];
}


Token Parser::advance()
{
    if (!isAtEnd())
    {
        current++;
    }

    return previous();
}


bool Parser::check(TokenType type)
{
    if (isAtEnd())
    {
        return type == TokenType::END_OF_FILE;
    }

    return peek().getType() == type;
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


Token Parser::consume(
    TokenType type,
    const std::string& message
)
{
    if (check(type))
    {
        return advance();
    }

    throw std::runtime_error(
        "Parser error: " + message
    );
}


// ===============================
// Statements
// ===============================

ASTNodePtr Parser::statement()
{
    if (check(TokenType::KAAM))
    {
        return functionDeclaration();
    }

    if (check(TokenType::GHE))
    {
        return variableDeclaration();
    }

    return expression();
}


// ===============================
// Variable Declaration
// ===============================

ASTNodePtr Parser::variableDeclaration()
{
    consume(
        TokenType::GHE,
        "Expected 'ghe'."
    );

    Token name = consume(
        TokenType::IDENTIFIER,
        "Expected variable name."
    );

    consume(
        TokenType::ASSIGN,
        "Expected '=' after variable name."
    );

    ASTNodePtr initializer = expression();

    consume(
        TokenType::SEMICOLON,
        "Expected ';' after variable declaration."
    );

    return std::make_shared<VariableDeclaration>(
        name.getLexeme(),
        initializer
    );
}


// ===============================
// Function Declaration
// ===============================

ASTNodePtr Parser::functionDeclaration()
{
    consume(
        TokenType::KAAM,
        "Expected 'kaam'."
    );

    Token name = consume(
        TokenType::IDENTIFIER,
        "Expected function name."
    );

    consume(
        TokenType::LEFT_PAREN,
        "Expected '(' after function name."
    );

    std::vector<std::string> parameters;

    if (!check(TokenType::RIGHT_PAREN))
    {
        do
        {
            Token parameter = consume(
                TokenType::IDENTIFIER,
                "Expected parameter name."
            );

            parameters.push_back(
                parameter.getLexeme()
            );

        } while (match(TokenType::COMMA));
    }

    consume(
        TokenType::RIGHT_PAREN,
        "Expected ')' after parameters."
    );

    consume(
        TokenType::LEFT_BRACE,
        "Expected '{' before function body."
    );

    std::vector<ASTNodePtr> body;

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd())
    {
        body.push_back(statement());
    }

    consume(
        TokenType::RIGHT_BRACE,
        "Expected '}' after function body."
    );

    return std::make_shared<FunctionDeclaration>(
        name.getLexeme(),
        parameters,
        body
    );
}


// ===============================
// Expressions
// ===============================

ASTNodePtr Parser::expression()
{
    ASTNodePtr left = primary();

    while (
        check(TokenType::PLUS) ||
        check(TokenType::MINUS) ||
        check(TokenType::MULTIPLY) ||
        check(TokenType::DIVIDE) ||
        check(TokenType::MODULO) ||
        check(TokenType::EQUAL_EQUAL) ||
        check(TokenType::NOT_EQUAL) ||
        check(TokenType::GREATER) ||
        check(TokenType::LESS) ||
        check(TokenType::GREATER_EQUAL) ||
        check(TokenType::LESS_EQUAL)
    )
    {
        Token op = advance();

        ASTNodePtr right = primary();

        left = std::make_shared<BinaryExpression>(
            left,
            op.getLexeme(),
            right
        );
    }

    return left;
}


// ===============================
// Primary Expressions
// ===============================

ASTNodePtr Parser::primary()
{
    if (match(TokenType::NUMBER))
    {
        return std::make_shared<NumberExpression>(
            previous().getLexeme()
        );
    }

    if (match(TokenType::IDENTIFIER))
    {
        return std::make_shared<IdentifierExpression>(
            previous().getLexeme()
        );
    }

    if (match(TokenType::LEFT_PAREN))
    {
        ASTNodePtr expr = expression();

        consume(
            TokenType::RIGHT_PAREN,
            "Expected ')'."
        );

        return expr;
    }

    throw std::runtime_error(
        "Parser error: Unexpected token '" +
        peek().getLexeme() +
        "'"
    );
}