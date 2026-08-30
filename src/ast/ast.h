#ifndef AST_H
#define AST_H

#include <memory>
#include <string>
#include <vector>

class ASTNode
{
public:
    virtual ~ASTNode() = default;

    virtual std::string toString() const = 0;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;


// ===============================
// Expression Base
// ===============================

class Expression : public ASTNode
{
};


// ===============================
// Statement Base
// ===============================

class Statement : public ASTNode
{
};


// ===============================
// Number Literal
// ===============================

class NumberExpression : public Expression
{
private:
    std::string value;

public:
    NumberExpression(const std::string& value);

    std::string toString() const override;
};


// ===============================
// Identifier
// ===============================

class IdentifierExpression : public Expression
{
private:
    std::string name;

public:
    IdentifierExpression(const std::string& name);

    std::string toString() const override;
};


// ===============================
// Binary Expression
// ===============================

class BinaryExpression : public Expression
{
private:
    ASTNodePtr left;
    std::string op;
    ASTNodePtr right;

public:
    BinaryExpression(
        ASTNodePtr left,
        const std::string& op,
        ASTNodePtr right
    );

    std::string toString() const override;
};


// ===============================
// Variable Declaration
// ===============================

class VariableDeclaration : public Statement
{
private:
    std::string name;
    ASTNodePtr initializer;

public:
    VariableDeclaration(
        const std::string& name,
        ASTNodePtr initializer
    );

    std::string toString() const override;
};


// ===============================
// Function Declaration
// ===============================

class FunctionDeclaration : public Statement
{
private:
    std::string name;
    std::vector<std::string> parameters;
    std::vector<ASTNodePtr> body;

public:
    FunctionDeclaration(
        const std::string& name,
        const std::vector<std::string>& parameters,
        const std::vector<ASTNodePtr>& body
    );

    std::string toString() const override;
};
class UnaryExpression : public ASTNode
{
public:
    UnaryExpression(
        const std::string& op,
        ASTNodePtr right
    )
        : op(op), right(right)
    {
    }

    std::string toString() const override
    {
        return "(" + op + " " + right->toString() + ")";
    }

private:
    std::string op;
    ASTNodePtr right;
};
#endif