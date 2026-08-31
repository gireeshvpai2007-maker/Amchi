#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>
#include <sstream>

// ============================================================
// BASE AST NODE
// ============================================================

class ASTNode
{
public:
    virtual ~ASTNode() = default;

    virtual std::string toString() const = 0;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;


// ============================================================
// NUMBER EXPRESSION
// ============================================================

class NumberExpression : public ASTNode
{
private:
    std::string value;

public:
    NumberExpression(const std::string& value)
        : value(value)
    {
    }

    const std::string& getValue() const
    {
        return value;
    }

    std::string toString() const override
    {
        return value;
    }
};


// ============================================================
// STRING EXPRESSION
// ============================================================

class StringExpression : public ASTNode
{
private:
    std::string value;

public:
    StringExpression(const std::string& value)
        : value(value)
    {
    }

    const std::string& getValue() const
    {
        return value;
    }

    std::string toString() const override
    {
        return "\"" + value + "\"";
    }
};


// ============================================================
// LITERAL EXPRESSION
// ============================================================

class LiteralExpression : public ASTNode
{
private:
    std::string value;

public:
    LiteralExpression(const std::string& value)
        : value(value)
    {
    }

    const std::string& getValue() const
    {
        return value;
    }

    std::string toString() const override
    {
        return value;
    }
};


// ============================================================
// IDENTIFIER EXPRESSION
// ============================================================

class IdentifierExpression : public ASTNode
{
private:
    std::string name;

public:
    IdentifierExpression(const std::string& name)
        : name(name)
    {
    }

    const std::string& getName() const
    {
        return name;
    }

    std::string toString() const override
    {
        return name;
    }
};


// ============================================================
// BINARY EXPRESSION
// ============================================================

class BinaryExpression : public ASTNode
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
    )
        : left(left),
          op(op),
          right(right)
    {
    }

    const ASTNodePtr& getLeft() const
    {
        return left;
    }

    const ASTNodePtr& getRight() const
    {
        return right;
    }

    const std::string& getOperator() const
    {
        return op;
    }

    std::string toString() const override
    {
        return "(" +
               op + " " +
               left->toString() + " " +
               right->toString() +
               ")";
    }
};


// ============================================================
// UNARY EXPRESSION
// ============================================================

class UnaryExpression : public ASTNode
{
private:
    std::string op;
    ASTNodePtr right;

public:
    UnaryExpression(
        const std::string& op,
        ASTNodePtr right
    )
        : op(op),
          right(right)
    {
    }

    const std::string& getOperator() const
    {
        return op;
    }

    const ASTNodePtr& getRight() const
    {
        return right;
    }

    std::string toString() const override
    {
        return "(" +
               op + " " +
               right->toString() +
               ")";
    }
};


// ============================================================
// VARIABLE DECLARATION
// ============================================================

class VariableDeclaration : public ASTNode
{
private:
    std::string name;
    ASTNodePtr initializer;

public:
    VariableDeclaration(
        const std::string& name,
        ASTNodePtr initializer
    )
        : name(name),
          initializer(initializer)
    {
    }

    const std::string& getName() const
    {
        return name;
    }

    const ASTNodePtr& getInitializer() const
    {
        return initializer;
    }

    std::string toString() const override
    {
        return "(var " +
               name + " " +
               initializer->toString() +
               ")";
    }
};


// ============================================================
// CALL EXPRESSION
// ============================================================

class CallExpression : public ASTNode
{
private:
    ASTNodePtr callee;
    std::vector<ASTNodePtr> arguments;

public:
    CallExpression(
        ASTNodePtr callee,
        const std::vector<ASTNodePtr>& arguments
    )
        : callee(callee),
          arguments(arguments)
    {
    }

    const ASTNodePtr& getCallee() const
    {
        return callee;
    }

    const std::vector<ASTNodePtr>& getArguments() const
    {
        return arguments;
    }

    std::string toString() const override
    {
        std::ostringstream result;

        result << "(Call "
               << callee->toString();

        for (const auto& argument : arguments)
        {
            result << " "
                   << argument->toString();
        }

        result << ")";

        return result.str();
    }
};


// ============================================================
// BLOCK STATEMENT
// ============================================================

class BlockStatement : public ASTNode
{
private:
    std::vector<ASTNodePtr> statements;

public:
    BlockStatement(
        const std::vector<ASTNodePtr>& statements
    )
        : statements(statements)
    {
    }

    const std::vector<ASTNodePtr>& getStatements() const
    {
        return statements;
    }

    std::string toString() const override
    {
        std::ostringstream result;

        result << "(block";

        for (const auto& statement : statements)
        {
            result << " "
                   << statement->toString();
        }

        result << ")";

        return result.str();
    }
};


// ============================================================
// IF STATEMENT
// ============================================================

class IfStatement : public ASTNode
{
private:
    ASTNodePtr condition;
    ASTNodePtr thenBranch;
    ASTNodePtr elseBranch;

public:
    IfStatement(
        ASTNodePtr condition,
        ASTNodePtr thenBranch,
        ASTNodePtr elseBranch = nullptr
    )
        : condition(condition),
          thenBranch(thenBranch),
          elseBranch(elseBranch)
    {
    }

    const ASTNodePtr& getCondition() const
    {
        return condition;
    }

    const ASTNodePtr& getThenBranch() const
    {
        return thenBranch;
    }

    const ASTNodePtr& getElseBranch() const
    {
        return elseBranch;
    }

    std::string toString() const override
    {
        std::ostringstream result;

        result << "(if "
               << condition->toString()
               << " "
               << thenBranch->toString();

        if (elseBranch)
        {
            result << " "
                   << elseBranch->toString();
        }

        result << ")";

        return result.str();
    }
};

#endif