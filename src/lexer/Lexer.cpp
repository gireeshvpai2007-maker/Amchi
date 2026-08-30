#include "Lexer.h"

#include <cctype>
#include <unordered_map>

Lexer::Lexer(const std::string& source)
    : source(source), current(0), start(0)
{
}

std::vector<Token> Lexer::tokenize()
{
    tokens.clear();
    current = 0;

    while (current < static_cast<int>(source.length()))
    {
        start = current;
        scanToken();
    }

    tokens.emplace_back(TokenType::END_OF_FILE, "");

    return tokens;
}


void Lexer::scanToken()
{
    char c = advance();

    switch (c)
    {
        // ---------- Single-character tokens ----------

        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;

        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;

        case '{':
            addToken(TokenType::LEFT_BRACE);
            break;

        case '}':
            addToken(TokenType::RIGHT_BRACE);
            break;

        case ';':
            addToken(TokenType::SEMICOLON);
            break;

        case ',':
            addToken(TokenType::COMMA);
            break;


        // ---------- Operators ----------

        case '+':
            addToken(TokenType::PLUS);
            break;

        case '-':
            addToken(TokenType::MINUS);
            break;

        case '*':
            addToken(TokenType::MULTIPLY);
            break;

        case '/':
            if (match('/'))
            {
                // Single-line comment
                while (peek() != '\n' && peek() != '\0')
                    advance();
            }
            else if (match('*'))
            {
                // Multi-line comment
                while (!(peek() == '*' && peekNext() == '/') &&
                       peek() != '\0')
                {
                    advance();
                }

                if (peek() != '\0')
                {
                    advance(); // *
                    advance(); // /
                }
            }
            else
            {
                addToken(TokenType::DIVIDE);
            }

            break;

        case '%':
            addToken(TokenType::MODULO);
            break;


        // ---------- Assignment / Equality ----------

        case '=':
            addToken(
                match('=') ? TokenType::EQUAL_EQUAL
                           : TokenType::ASSIGN
            );
            break;


        // ---------- Not / Not Equal ----------

        case '!':
            addToken(
                match('=') ? TokenType::NOT_EQUAL
                           : TokenType::NOT
            );
            break;


        // ---------- Greater / Greater Equal ----------

        case '>':
            if (match('='))
                addToken(TokenType::GREATER_EQUAL);
            else if (match('>'))
                addToken(TokenType::INPUT);
            else
                addToken(TokenType::GREATER);

            break;


        // ---------- Less / Less Equal ----------

        case '<':
            addToken(
                match('=') ? TokenType::LESS_EQUAL
                           : TokenType::LESS
            );
            break;


        // ---------- Logical AND ----------

        case '&':
            if (match('&'))
                addToken(TokenType::AND);
            else
                addToken(TokenType::UNKNOWN);

            break;


        // ---------- Logical OR ----------

        case '|':
            if (match('|'))
                addToken(TokenType::OR);
            else
                addToken(TokenType::UNKNOWN);

            break;


        // ---------- Whitespace ----------

        case ' ':
        case '\r':
        case '\t':
        case '\n':
            break;


        // ---------- String ----------

        case '"':
            string();
            break;


        // ---------- Numbers ----------

        default:

            if (isDigit(c))
            {
                number();
            }
            else if (isAlpha(c))
            {
                identifier();
            }
            else
            {
                addToken(TokenType::UNKNOWN);
            }

            break;
    }
}


char Lexer::advance()
{
    return source[current++];
}


char Lexer::peek()
{
    if (current >= static_cast<int>(source.length()))
        return '\0';

    return source[current];
}


char Lexer::peekNext()
{
    if (current + 1 >= static_cast<int>(source.length()))
        return '\0';

    return source[current + 1];
}


bool Lexer::match(char expected)
{
    if (current >= static_cast<int>(source.length()))
        return false;

    if (source[current] != expected)
        return false;

    current++;

    return true;
}


void Lexer::addToken(TokenType type)
{
    std::string lexeme = source.substr(
        start,
        current - start
    );

    tokens.emplace_back(type, lexeme);
}


void Lexer::addToken(TokenType type, const std::string& lexeme)
{
    tokens.emplace_back(type, lexeme);
}


void Lexer::identifier()
{
    while (isAlphaNumeric(peek()))
        advance();

    std::string text = source.substr(
        start,
        current - start
    );

    TokenType type = keywordType(text);

    addToken(type, text);
}


void Lexer::number()
{
    while (isDigit(peek()))
        advance();

    // Decimal numbers
    if (peek() == '.' && isDigit(peekNext()))
    {
        advance();

        while (isDigit(peek()))
            advance();
    }

    addToken(TokenType::NUMBER);
}


void Lexer::string()
{
    while (peek() != '"' && peek() != '\0')
        advance();

    if (peek() == '"')
        advance();

    std::string value = source.substr(
        start + 1,
        current - start - 2
    );

    addToken(TokenType::STRING, value);
}


bool Lexer::isDigit(char c)
{
    return std::isdigit(
        static_cast<unsigned char>(c)
    );
}


bool Lexer::isAlpha(char c)
{
    return std::isalpha(
        static_cast<unsigned char>(c)
    ) || c == '_';
}


bool Lexer::isAlphaNumeric(char c)
{
    return isAlpha(c) || isDigit(c);
}


TokenType Lexer::keywordType(const std::string& text)
{
    static const std::unordered_map<std::string, TokenType> keywords =
    {
        {"ghe", TokenType::GHE},
        {"dhake", TokenType::DHAKE},
        {"nimgi", TokenType::NIMGI},
        {"jallari", TokenType::JALLARI},
        {"najallari", TokenType::NAJALLARI},
        {"javchvare", TokenType::JAVCHVARE},
        {"kaam", TokenType::KAAM},
        {"vishay", TokenType::VISHAY},
        {"shuru", TokenType::SHURU},
        {"jaag", TokenType::JAAG},

        {"true", TokenType::TRUE},
        {"false", TokenType::FALSE},
        {"null", TokenType::NULL_VALUE}
    };

    auto it = keywords.find(text);

    if (it != keywords.end())
        return it->second;

    return TokenType::IDENTIFIER;
}