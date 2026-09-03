#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../ast/ast.h"
#include "value.h"

class Interpreter
{
public:
    void interpret(
        const std::vector<ASTNodePtr>& statements
    );

private:

    // Variable name -> runtime value
    std::unordered_map<std::string, Value> environment;

    void execute(
        const ASTNodePtr& node
    );

    Value evaluate(
        const ASTNodePtr& node
    );

    Value evaluateBinary(
        const std::string& op,
        const Value& left,
        const Value& right
    );

    Value evaluateUnary(
        const std::string& op,
        const Value& right
    );
};

#endif