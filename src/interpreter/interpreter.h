#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../ast/ast.h"

class Interpreter
{
public:
    void interpret(const std::vector<ASTNodePtr>& statements);

private:
    std::unordered_map<std::string, double> environment;

    void execute(const ASTNodePtr& node);

    double evaluate(const ASTNodePtr& node);

    double evaluateBinary(
        const std::string& op,
        double left,
        double right
    );

    double evaluateUnary(
        const std::string& op,
        double right
    );
};

#endif