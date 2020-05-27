#pragma once

#include "../UserIO/Printable.hpp"

#include <string>
typedef std::string str;

class GradeEntry : Printable
{
    //The user who gave the grade (their index)
    int userInd;
    //The grade they gave
    int grade;

    public:

        str ToStr() const;
};