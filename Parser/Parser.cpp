#include "Parser.hpp"

int Parser::ToInt(const str& s)
{
    bool negative = (s[0] == '-');

    int result = 0;
    for (int i = (negative ? 1 : 0); i < s.length(); i++)
        result = result * 10 + (s[i] - '0');

    return (negative ? -result : result);
}