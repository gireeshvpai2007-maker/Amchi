#include "ast.h"

#include <sstream>

// ===============================
// Number Expression
// ===============================

NumberExpression::NumberExpression(const std::string& value)
    : value(value)
{
}

std::string NumberExpression::toString() const
{
    return value;
}


// ===============================
// Identifier Expression
// ===============================

IdentifierExpression::IdentifierExpression(const std::string& name)
    : name(name)
{
}

std::string IdentifierExpression::toString() const
{
    return name;
}


// ===============================
// Binary Expression
// ===============================

BinaryExpression::BinaryExpression(
    ASTNodePtr left,
    const std::string& op,
    ASTNodePtr right
)
    : left(left), op(op), right(right)
{
}

std::string BinaryExpression::toString() const
{
    return "(" +
           left->toString() +
           " " +
           op +
           " " +
           right->toString() +
           ")";
}


// ===============================
// Variable Declaration
// ===============================

VariableDeclaration::VariableDeclaration(
    const std::string& name,
    ASTNodePtr initializer
)
    : name(name), initializer(initializer)
{
}

std::string VariableDeclaration::toString() const
{
    return "(ghe " +
           name +
           " = " +
           initializer->toString() +
           ")";
}


// ===============================
// Function Declaration
// ===============================

FunctionDeclaration::FunctionDeclaration(
    const std::string& name,
    const std::vector<std::string>& parameters,
    const std::vector<ASTNodePtr>& body
)
    : name(name), parameters(parameters), body(body)
{
}

std::string FunctionDeclaration::toString() const
{
    std::ostringstream result;

    result << "(kaam " << name << " (";

    for (size_t i = 0; i < parameters.size(); ++i)
    {
        result << parameters[i];

        if (i + 1 < parameters.size())
        {
            result << ", ";
        }
    }

    result << ")";

    for (const auto& statement : body)
    {
        result << " " << statement->toString();
    }

    result << ")";

    return result.str();
}