#include "Lexer.h"

#include <cctype>
#include <unordered_map>


Lexer::Lexer(const std::string& source)
    : source(source),
      current(0),
      start(0)
{
}


// ============================================================
// TOKENIZE
// ============================================================

std::vector<Token> Lexer::tokenize()
{
    tokens.clear();

    current = 0;
    start = 0;

    while (current < static_cast<int>(source.length()))
    {
        start = current;

        scanToken();
    }

    tokens.emplace_back(
        TokenType::END_OF_FILE,
        ""
    );

    return tokens;
}


// ============================================================
// SCAN TOKEN
// ============================================================

void Lexer::scanToken()
{
    char c = advance();

    switch (c)
    {
        // ----------------------------------------------------
        // Single-character tokens
        // ----------------------------------------------------

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


        // ----------------------------------------------------
        // Arithmetic operators
        // ----------------------------------------------------

        case '+':
            addToken(TokenType::PLUS);
            break;

        case '-':
            addToken(TokenType::MINUS);
            break;

        case '*':
            addToken(TokenType::MULTIPLY);
            break;

        case '%':
            addToken(TokenType::MODULO);
            break;


        // ----------------------------------------------------
        // Division / comments
        // ----------------------------------------------------

        case '/':

            if (match('/'))
            {
                // Single-line comment

                while (
                    peek() != '\n' &&
                    peek() != '\0'
                )
                {
                    advance();
                }
            }
            else if (match('*'))
            {
                // Multi-line comment

                while (
                    !(peek() == '*' &&
                      peekNext() == '/') &&
                    peek() != '\0'
                )
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


        // ----------------------------------------------------
        // Assignment / equality
        // ----------------------------------------------------

        case '=':

            if (match('='))
            {
                addToken(TokenType::EQUAL_EQUAL);
            }
            else
            {
                addToken(TokenType::ASSIGN);
            }

            break;


        // ----------------------------------------------------
        // NOT / NOT EQUAL
        // ----------------------------------------------------

        case '!':

            if (match('='))
            {
                addToken(TokenType::NOT_EQUAL);
            }
            else
            {
                addToken(TokenType::NOT);
            }

            break;


        // ----------------------------------------------------
        // Greater / input operator
        // ----------------------------------------------------

        case '>':

            if (match('='))
            {
                addToken(TokenType::GREATER_EQUAL);
            }
            else if (match('>'))
            {
                addToken(TokenType::INPUT);
            }
            else
            {
                addToken(TokenType::GREATER);
            }

            break;


        // ----------------------------------------------------
        // Less
        // ----------------------------------------------------

        case '<':

            if (match('='))
            {
                addToken(TokenType::LESS_EQUAL);
            }
            else
            {
                addToken(TokenType::LESS);
            }

            break;


        // ----------------------------------------------------
        // Logical AND
        // ----------------------------------------------------

        case '&':

            if (match('&'))
            {
                addToken(TokenType::AND);
            }
            else
            {
                addToken(TokenType::UNKNOWN);
            }

            break;


        // ----------------------------------------------------
        // Logical OR
        // ----------------------------------------------------

        case '|':

            if (match('|'))
            {
                addToken(TokenType::OR);
            }
            else
            {
                addToken(TokenType::UNKNOWN);
            }

            break;


        // ----------------------------------------------------
        // Whitespace
        // ----------------------------------------------------

        case ' ':
        case '\r':
        case '\t':
        case '\n':
            break;


        // ----------------------------------------------------
        // Strings
        // ----------------------------------------------------

        case '"':
            string();
            break;


        // ----------------------------------------------------
        // Numbers / identifiers
        // ----------------------------------------------------

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


// ============================================================
// CHARACTER HANDLING
// ============================================================

char Lexer::advance()
{
    return source[current++];
}


char Lexer::peek()
{
    if (current >= static_cast<int>(source.length()))
    {
        return '\0';
    }

    return source[current];
}


char Lexer::peekNext()
{
    if (current + 1 >= static_cast<int>(source.length()))
    {
        return '\0';
    }

    return source[current + 1];
}


bool Lexer::match(char expected)
{
    if (current >= static_cast<int>(source.length()))
    {
        return false;
    }

    if (source[current] != expected)
    {
        return false;
    }

    current++;

    return true;
}


// ============================================================
// TOKEN CREATION
// ============================================================

void Lexer::addToken(TokenType type)
{
    std::string lexeme =
        source.substr(
            start,
            current - start
        );

    tokens.emplace_back(
        type,
        lexeme
    );
}


void Lexer::addToken(
    TokenType type,
    const std::string& lexeme
)
{
    tokens.emplace_back(
        type,
        lexeme
    );
}


// ============================================================
// IDENTIFIERS / KEYWORDS
// ============================================================

void Lexer::identifier()
{
    while (isAlphaNumeric(peek()))
    {
        advance();
    }

    std::string text =
        source.substr(
            start,
            current - start
        );

    TokenType type =
        keywordType(text);

    addToken(type, text);
}


// ============================================================
// NUMBERS
// ============================================================

void Lexer::number()
{
    while (isDigit(peek()))
    {
        advance();
    }

    // Decimal numbers

    if (
        peek() == '.' &&
        isDigit(peekNext())
    )
    {
        advance();

        while (isDigit(peek()))
        {
            advance();
        }
    }

    addToken(TokenType::NUMBER);
}


// ============================================================
// STRINGS
// ============================================================

void Lexer::string()
{
    while (
        peek() != '"' &&
        peek() != '\0'
    )
    {
        advance();
    }

    if (peek() == '"')
    {
        advance();
    }

    std::string value;

    if (current - start >= 2)
    {
        value =
            source.substr(
                start + 1,
                current - start - 2
            );
    }

    addToken(
        TokenType::STRING,
        value
    );
}


// ============================================================
// CHARACTER CLASSIFICATION
// ============================================================

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
    return (
        isAlpha(c) ||
        isDigit(c)
    );
}


// ============================================================
// KEYWORDS
// ============================================================

TokenType Lexer::keywordType(
    const std::string& text
)
{
    static const std::unordered_map<
        std::string,
        TokenType
    > keywords =
    {
        // Amchi keywords

        {"ghe",       TokenType::GHE},
        {"dhake",     TokenType::DHAKE},
        {"nimgi",     TokenType::NIMGI},
        {"jallari",   TokenType::JALLARI},
        {"najallari", TokenType::NAJALLARI},
        {"javchvare", TokenType::JAVCHVARE},

        {"kaam",      TokenType::KAAM},
        {"vishay",    TokenType::VISHAY},
        {"shuru",     TokenType::SHURU},
        {"jaag",      TokenType::JAAG},

        // Literals

        {"true",      TokenType::TRUE},
        {"false",     TokenType::FALSE},
        {"null",      TokenType::NULL_VALUE}
    };

    auto it = keywords.find(text);

    if (it != keywords.end())
    {
        return it->second;
    }

    return TokenType::IDENTIFIER;
}