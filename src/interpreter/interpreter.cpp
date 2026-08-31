#include "interpreter.h"

#include <iostream>
#include <stdexcept>
#include <memory>

// ============================================================
// INTERPRET PROGRAM
// ============================================================

void Interpreter::interpret(
    const std::vector<ASTNodePtr>& statements
)
{
    for (const auto& statement : statements)
    {
        execute(statement);
    }
}


// ============================================================
// EXECUTE STATEMENTS
// ============================================================

void Interpreter::execute(const ASTNodePtr& node)
{
    // --------------------------------------------------------
    // Variable declaration
    // --------------------------------------------------------

    auto variable =
        std::dynamic_pointer_cast<VariableDeclaration>(node);

    if (variable)
    {
        double value =
            evaluate(variable->getInitializer());

        environment[variable->getName()] = value;

        return;
    }


    // --------------------------------------------------------
    // Block statement
    // --------------------------------------------------------

    auto block =
        std::dynamic_pointer_cast<BlockStatement>(node);

    if (block)
    {
        for (const auto& statement : block->getStatements())
        {
            execute(statement);
        }

        return;
    }


    // --------------------------------------------------------
    // If statement
    // --------------------------------------------------------

    auto ifStatement =
        std::dynamic_pointer_cast<IfStatement>(node);

    if (ifStatement)
    {
        double condition =
            evaluate(ifStatement->getCondition());

        if (condition != 0)
        {
            execute(ifStatement->getThenBranch());
        }
        else if (ifStatement->getElseBranch())
        {
            execute(ifStatement->getElseBranch());
        }

        return;
    }


    // --------------------------------------------------------
    // Function call
    // --------------------------------------------------------

    auto call =
        std::dynamic_pointer_cast<CallExpression>(node);

    if (call)
    {
        evaluate(call);
        return;
    }


    // --------------------------------------------------------
    // Other expression
    // --------------------------------------------------------

    evaluate(node);
}


// ============================================================
// EVALUATE EXPRESSIONS
// ============================================================

double Interpreter::evaluate(
    const ASTNodePtr& node
)
{
    // --------------------------------------------------------
    // Number
    // --------------------------------------------------------

    auto number =
        std::dynamic_pointer_cast<NumberExpression>(node);

    if (number)
    {
        return std::stod(number->getValue());
    }


    // --------------------------------------------------------
    // Identifier
    // --------------------------------------------------------

    auto identifier =
        std::dynamic_pointer_cast<IdentifierExpression>(node);

    if (identifier)
    {
        const std::string& name =
            identifier->getName();

        auto it = environment.find(name);

        if (it == environment.end())
        {
            throw std::runtime_error(
                "Undefined variable: " + name
            );
        }

        return it->second;
    }


    // --------------------------------------------------------
    // Binary expression
    // --------------------------------------------------------

    auto binary =
        std::dynamic_pointer_cast<BinaryExpression>(node);

    if (binary)
    {
        double left =
            evaluate(binary->getLeft());

        double right =
            evaluate(binary->getRight());

        return evaluateBinary(
            binary->getOperator(),
            left,
            right
        );
    }


    // --------------------------------------------------------
    // Unary expression
    // --------------------------------------------------------

    auto unary =
        std::dynamic_pointer_cast<UnaryExpression>(node);

    if (unary)
    {
        double right =
            evaluate(unary->getRight());

        return evaluateUnary(
            unary->getOperator(),
            right
        );
    }


    // --------------------------------------------------------
    // Function call
    // --------------------------------------------------------

    auto call =
        std::dynamic_pointer_cast<CallExpression>(node);

    if (call)
    {
        auto callee =
            std::dynamic_pointer_cast<IdentifierExpression>(
                call->getCallee()
            );

        if (!callee)
        {
            throw std::runtime_error(
                "Invalid function call."
            );
        }

        std::string functionName =
            callee->getName();


        // ----------------------------------------------------
        // dhake()
        // ----------------------------------------------------

        if (functionName == "dhake")
        {
            if (call->getArguments().size() != 1)
            {
                throw std::runtime_error(
                    "dhake() expects exactly one argument."
                );
            }

            ASTNodePtr argument =
                call->getArguments()[0];

            // String arguments are handled separately.
            auto stringExpression =
                std::dynamic_pointer_cast<StringExpression>(
                    argument
                );

            if (stringExpression)
            {
                std::cout
                    << stringExpression->getValue()
                    << std::endl;

                return 0;
            }

            double value =
                evaluate(argument);

            std::cout << value << std::endl;

            return value;
        }


        throw std::runtime_error(
            "Unknown function: " + functionName
        );
    }


    // --------------------------------------------------------
    // Unsupported node
    // --------------------------------------------------------

    throw std::runtime_error(
        "Cannot evaluate AST node."
    );
}


// ============================================================
// BINARY OPERATORS
// ============================================================

double Interpreter::evaluateBinary(
    const std::string& op,
    double left,
    double right
)
{
    if (op == "+")
        return left + right;

    if (op == "-")
        return left - right;

    if (op == "*")
        return left * right;

    if (op == "/")
    {
        if (right == 0)
        {
            throw std::runtime_error(
                "Division by zero."
            );
        }

        return left / right;
    }

    if (op == "%")
    {
        if (right == 0)
        {
            throw std::runtime_error(
                "Modulo by zero."
            );
        }

        return static_cast<int>(left) %
               static_cast<int>(right);
    }

    if (op == ">")
        return left > right;

    if (op == "<")
        return left < right;

    if (op == ">=")
        return left >= right;

    if (op == "<=")
        return left <= right;

    if (op == "==")
        return left == right;

    if (op == "!=")
        return left != right;

    if (op == "&&")
        return (left != 0) && (right != 0);

    if (op == "||")
        return (left != 0) || (right != 0);

    throw std::runtime_error(
        "Unknown binary operator: " + op
    );
}


// ============================================================
// UNARY OPERATORS
// ============================================================

double Interpreter::evaluateUnary(
    const std::string& op,
    double right
)
{
    if (op == "-")
        return -right;

    if (op == "!")
        return !right;

    throw std::runtime_error(
        "Unknown unary operator: " + op
    );
}