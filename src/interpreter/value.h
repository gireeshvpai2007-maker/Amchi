#ifndef VALUE_H
#define VALUE_H

#include <variant>
#include <string>
#include <iostream>

using Value = std::variant<
    double,
    std::string,
    bool
>;

inline std::string valueToString(const Value& value)
{
    if (std::holds_alternative<double>(value))
    {
        double number = std::get<double>(value);

        // Print 10 instead of 10.000000
        if (number == static_cast<long long>(number))
        {
            return std::to_string(
                static_cast<long long>(number)
            );
        }

        return std::to_string(number);
    }

    if (std::holds_alternative<std::string>(value))
    {
        return std::get<std::string>(value);
    }

    if (std::holds_alternative<bool>(value))
    {
        return std::get<bool>(value)
            ? "true"
            : "false";
    }

    return "null";
}

inline bool isTruthy(const Value& value)
{
    if (std::holds_alternative<bool>(value))
    {
        return std::get<bool>(value);
    }

    if (std::holds_alternative<double>(value))
    {
        return std::get<double>(value) != 0;
    }

    if (std::holds_alternative<std::string>(value))
    {
        return !std::get<std::string>(value).empty();
    }

    return false;
}

#endif