#pragma once

#include "GradeEntry.hpp"

#include <string>
#include <vector>
typedef std::string str;

class Destination
{
    //The name of the destination
    str m_name;
    //Keeps track of which user graded the destination and with what grade
    std::vector<GradeEntry> m_grades;
};