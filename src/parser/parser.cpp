#include "parser.h"

#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), current(0)
{
}

std::vector<ASTNodePtr> Parser::parse()
{
    std::vector<ASTNodePtr> statements;

    if (match(TokenType::KAAM))
    {
        consume(TokenType::SHURU, "Expected 'shuru' after 'kaam'.");
        consume(TokenType::LEFT_BRACE, "Expected '{' after 'kaam shuru'.");

        while (!check(TokenType::RIGHT_BRACE) && !isAtEnd())
        {
            statements.push_back(statement());
        }

        consume(TokenType::RIGHT_BRACE, "Expected '}' after program.");
        return statements;
    }

    while (!isAtEnd())
    {
        statements.push_back(statement());
    }

    return statements;
}

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

Token Parser::consume(TokenType type, const std::string& message)
{
    if (check(type))
    {
        return advance();
    }

    throw std::runtime_error(message);
}

ASTNodePtr Parser::statement()
{
    if (check(TokenType::GHE))
    {
        return variableDeclaration();
    }

    if (check(TokenType::KAAM))
    {
        return functionDeclaration();
    }

    if (check(TokenType::JALLARI))
    {
        return ifStatement();
    }

    ASTNodePtr expr = expression();

    consume(TokenType::SEMICOLON, "Expected ';' after expression.");

    return expr;
}

ASTNodePtr Parser::variableDeclaration()
{
    consume(TokenType::GHE, "Expected 'ghe'.");

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

ASTNodePtr Parser::functionDeclaration()
{
    consume(TokenType::KAAM, "Expected 'kaam'.");
    consume(TokenType::SHURU, "Expected 'shuru' after 'kaam'.");
    consume(TokenType::LEFT_BRACE, "Expected '{' after 'kaam shuru'.");

    std::vector<ASTNodePtr> statements;

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd())
    {
        statements.push_back(statement());
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");

    return std::make_shared<BlockStatement>(statements);
}

ASTNodePtr Parser::ifStatement()
{
    consume(TokenType::JALLARI, "Expected 'jallari'.");
    consume(TokenType::LEFT_PAREN, "Expected '(' after 'jallari'.");

    ASTNodePtr condition = expression();

    consume(TokenType::RIGHT_PAREN, "Expected ')' after condition.");

    ASTNodePtr thenBranch = block();
    ASTNodePtr elseBranch = nullptr;

    if (match(TokenType::NAJALLARI))
    {
        elseBranch = block();
    }

    return std::make_shared<IfStatement>(
        condition,
        thenBranch,
        elseBranch
    );
}

ASTNodePtr Parser::block()
{
    consume(TokenType::LEFT_BRACE, "Expected '{'.");

    std::vector<ASTNodePtr> statements;

    while (!check(TokenType::RIGHT_BRACE) && !isAtEnd())
    {
        statements.push_back(statement());
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}' after block.");

    return std::make_shared<BlockStatement>(statements);
}

ASTNodePtr Parser::expression()
{
    return assignment();
}

ASTNodePtr Parser::assignment()
{
    ASTNodePtr left = orExpression();

    if (match(TokenType::ASSIGN))
    {
        Token equals = previous();
        (void)equals;

        ASTNodePtr value = assignment();

        auto identifier =
            std::dynamic_pointer_cast<IdentifierExpression>(left);

        if (!identifier)
        {
            throw std::runtime_error(
                "Invalid assignment target."
            );
        }

        return std::make_shared<AssignmentExpression>(
            identifier->getName(),
            value
        );
    }

    return left;
}

ASTNodePtr Parser::orExpression()
{
    ASTNodePtr left = andExpression();

    while (match(TokenType::OR))
    {
        Token op = previous();
        ASTNodePtr right = andExpression();
        left = std::make_shared<BinaryExpression>(left, op.getLexeme(), right);
    }

    return left;
}

ASTNodePtr Parser::andExpression()
{
    ASTNodePtr left = equality();

    while (match(TokenType::AND))
    {
        Token op = previous();
        ASTNodePtr right = equality();
        left = std::make_shared<BinaryExpression>(left, op.getLexeme(), right);
    }

    return left;
}

ASTNodePtr Parser::equality()
{
    ASTNodePtr left = comparison();

    while (match(TokenType::EQUAL_EQUAL) || match(TokenType::NOT_EQUAL))
    {
        Token op = previous();
        ASTNodePtr right = comparison();
        left = std::make_shared<BinaryExpression>(left, op.getLexeme(), right);
    }

    return left;
}

ASTNodePtr Parser::comparison()
{
    ASTNodePtr left = term();

    while (
        match(TokenType::GREATER) ||
        match(TokenType::LESS) ||
        match(TokenType::GREATER_EQUAL) ||
        match(TokenType::LESS_EQUAL)
    )
    {
        Token op = previous();
        ASTNodePtr right = term();
        left = std::make_shared<BinaryExpression>(left, op.getLexeme(), right);
    }

    return left;
}

ASTNodePtr Parser::term()
{
    ASTNodePtr left = factor();

    while (match(TokenType::PLUS) || match(TokenType::MINUS))
    {
        Token op = previous();
        ASTNodePtr right = factor();
        left = std::make_shared<BinaryExpression>(left, op.getLexeme(), right);
    }

    return left;
}

ASTNodePtr Parser::factor()
{
    ASTNodePtr left = unary();

    while (
        match(TokenType::MULTIPLY) ||
        match(TokenType::DIVIDE) ||
        match(TokenType::MODULO)
    )
    {
        Token op = previous();
        ASTNodePtr right = unary();
        left = std::make_shared<BinaryExpression>(left, op.getLexeme(), right);
    }

    return left;
}

ASTNodePtr Parser::unary()
{
    if (match(TokenType::NOT) || match(TokenType::MINUS))
    {
        Token op = previous();
        ASTNodePtr right = unary();
        return std::make_shared<UnaryExpression>(op.getLexeme(), right);
    }

    return call();
}

ASTNodePtr Parser::call()
{
    ASTNodePtr expr = primary();

    while (true)
    {
        if (match(TokenType::LEFT_PAREN))
        {
            std::vector<ASTNodePtr> arguments;

            if (!check(TokenType::RIGHT_PAREN))
            {
                do
                {
                    arguments.push_back(expression());
                }
                while (match(TokenType::COMMA));
            }

            consume(TokenType::RIGHT_PAREN, "Expected ')' after arguments.");

            expr = std::make_shared<CallExpression>(expr, arguments);
        }
        else
        {
            break;
        }
    }

    return expr;
}

ASTNodePtr Parser::primary()
{
    if (match(TokenType::NUMBER))
    {
        return std::make_shared<NumberExpression>(previous().getLexeme());
    }

    if (match(TokenType::STRING))
    {
        return std::make_shared<StringExpression>(previous().getLexeme());
    }

    if (match(TokenType::TRUE))
    {
        return std::make_shared<LiteralExpression>(previous().getLexeme());
    }

    if (match(TokenType::FALSE))
    {
        return std::make_shared<LiteralExpression>(previous().getLexeme());
    }

    if (match(TokenType::NULL_VALUE))
    {
        return std::make_shared<LiteralExpression>(previous().getLexeme());
    }

    if (match(TokenType::IDENTIFIER))
    {
        return std::make_shared<IdentifierExpression>(previous().getLexeme());
    }

    if (match(TokenType::DHAKE))
    {
        return std::make_shared<IdentifierExpression>(previous().getLexeme());
    }

    if (match(TokenType::LEFT_PAREN))
    {
        ASTNodePtr expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");
        return expr;
    }

    throw std::runtime_error(
        "Unexpected token: " + peek().getLexeme()
    );
}