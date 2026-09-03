#include "interpreter.h"

#include <iostream>
#include <stdexcept>
#include <memory>
#include <cmath>

void Interpreter::interpret(
    const std::vector<ASTNodePtr>& statements
)
{
    for (const auto& statement : statements)
    {
        execute(statement);
    }
}

void Interpreter::execute(const ASTNodePtr& node)
{
    auto variable = std::dynamic_pointer_cast<VariableDeclaration>(node);

    if (variable)
    {
        Value value = evaluate(variable->getInitializer());
        environment[variable->getName()] = value;
        return;
    }

    auto assignment = std::dynamic_pointer_cast<AssignmentExpression>(node);

    if (assignment)
    {
        auto it = environment.find(assignment->getName());

        if (it == environment.end())
        {
            throw std::runtime_error(
                "Undefined variable: " + assignment->getName()
            );
        }

        Value value = evaluate(assignment->getValue());
        it->second = value;
        return;
    }

    auto block = std::dynamic_pointer_cast<BlockStatement>(node);

    if (block)
    {
        for (const auto& statement : block->getStatements())
        {
            execute(statement);
        }
        return;
    }

    auto ifStatement = std::dynamic_pointer_cast<IfStatement>(node);

    if (ifStatement)
    {
        Value condition = evaluate(ifStatement->getCondition());

        if (isTruthy(condition))
        {
            execute(ifStatement->getThenBranch());
        }
        else if (ifStatement->getElseBranch())
        {
            execute(ifStatement->getElseBranch());
        }
        return;
    }

    auto call = std::dynamic_pointer_cast<CallExpression>(node);

    if (call)
    {
        evaluate(call);
        return;
    }

    evaluate(node);
}

Value Interpreter::evaluate(const ASTNodePtr& node)
{
    auto number = std::dynamic_pointer_cast<NumberExpression>(node);

    if (number)
    {
        return std::stod(number->getValue());
    }

    auto stringExpression = std::dynamic_pointer_cast<StringExpression>(node);

    if (stringExpression)
    {
        return stringExpression->getValue();
    }

    auto literal = std::dynamic_pointer_cast<LiteralExpression>(node);

    if (literal)
    {
        if (literal->getValue() == "true") return true;
        if (literal->getValue() == "false") return false;

        throw std::runtime_error(
            "Unknown literal: " + literal->getValue()
        );
    }

    auto identifier = std::dynamic_pointer_cast<IdentifierExpression>(node);

    if (identifier)
    {
        const std::string& name = identifier->getName();
        auto it = environment.find(name);

        if (it == environment.end())
        {
            throw std::runtime_error(
                "Undefined variable: " + name
            );
        }

        return it->second;
    }

    auto assignment = std::dynamic_pointer_cast<AssignmentExpression>(node);

    if (assignment)
    {
        auto it = environment.find(assignment->getName());

        if (it == environment.end())
        {
            throw std::runtime_error(
                "Undefined variable: " + assignment->getName()
            );
        }

        Value value = evaluate(assignment->getValue());
        it->second = value;
        return value;
    }

    auto binary = std::dynamic_pointer_cast<BinaryExpression>(node);

    if (binary)
    {
        Value left = evaluate(binary->getLeft());
        Value right = evaluate(binary->getRight());

        return evaluateBinary(
            binary->getOperator(),
            left,
            right
        );
    }

    auto unary = std::dynamic_pointer_cast<UnaryExpression>(node);

    if (unary)
    {
        Value right = evaluate(unary->getRight());

        return evaluateUnary(
            unary->getOperator(),
            right
        );
    }

    auto call = std::dynamic_pointer_cast<CallExpression>(node);

    if (call)
    {
        auto callee = std::dynamic_pointer_cast<IdentifierExpression>(
            call->getCallee()
        );

        if (!callee)
        {
            throw std::runtime_error("Invalid function call.");
        }

        std::string functionName = callee->getName();

        if (functionName == "dhake")
        {
            if (call->getArguments().size() != 1)
            {
                throw std::runtime_error(
                    "dhake() expects exactly one argument."
                );
            }

            Value value = evaluate(call->getArguments()[0]);
            std::cout << valueToString(value) << std::endl;
            return value;
        }

        throw std::runtime_error(
            "Unknown function: " + functionName
        );
    }

    throw std::runtime_error("Cannot evaluate AST node.");
}

Value Interpreter::evaluateBinary(
    const std::string& op,
    const Value& left,
    const Value& right
)
{
    if (op == "+")
    {
        if (std::holds_alternative<double>(left) &&
            std::holds_alternative<double>(right))
        {
            return std::get<double>(left) + std::get<double>(right);
        }

        if (std::holds_alternative<std::string>(left) &&
            std::holds_alternative<std::string>(right))
        {
            return std::get<std::string>(left) + std::get<std::string>(right);
        }

        throw std::runtime_error(
            "Operator '+' requires two numbers or two strings."
        );
    }

    if (op == "-" || op == "*" || op == "/" || op == "%")
    {
        if (!std::holds_alternative<double>(left) ||
            !std::holds_alternative<double>(right))
        {
            throw std::runtime_error(
                "Operator '" + op + "' requires two numbers."
            );
        }

        double l = std::get<double>(left);
        double r = std::get<double>(right);

        if ((op == "/" || op == "%") && r == 0)
        {
            throw std::runtime_error("Division by zero.");
        }

        if (op == "-") return l - r;
        if (op == "*") return l * r;
        if (op == "/") return l / r;
        return std::fmod(l, r);
    }

    if (op == ">" || op == "<" || op == ">=" || op == "<=")
    {
        if (!std::holds_alternative<double>(left) ||
            !std::holds_alternative<double>(right))
        {
            throw std::runtime_error(
                "Operator '" + op + "' requires two numbers."
            );
        }

        double l = std::get<double>(left);
        double r = std::get<double>(right);

        if (op == ">")  return l > r;
        if (op == "<")  return l < r;
        if (op == ">=") return l >= r;
        return l <= r;
    }

    if (op == "==" || op == "!=")
    {
        bool equal = false;

        if (left.index() == right.index())
        {
            if (std::holds_alternative<double>(left))
            {
                equal = std::get<double>(left) == std::get<double>(right);
            }
            else if (std::holds_alternative<std::string>(left))
            {
                equal = std::get<std::string>(left) == std::get<std::string>(right);
            }
            else if (std::holds_alternative<bool>(left))
            {
                equal = std::get<bool>(left) == std::get<bool>(right);
            }
        }

        return op == "==" ? equal : !equal;
    }

    if (op == "&&" || op == "||")
    {
        bool l = isTruthy(left);
        bool r = isTruthy(right);

        if (op == "&&") return l && r;
        return l || r;
    }

    throw std::runtime_error(
        "Unknown binary operator: " + op
    );
}

Value Interpreter::evaluateUnary(
    const std::string& op,
    const Value& right
)
{
    if (op == "-")
    {
        if (!std::holds_alternative<double>(right))
        {
            throw std::runtime_error(
                "Unary '-' requires a number."
            );
        }

        return -std::get<double>(right);
    }

    if (op == "!")
    {
        return !isTruthy(right);
    }

    throw std::runtime_error(
        "Unknown unary operator: " + op
    );
}
