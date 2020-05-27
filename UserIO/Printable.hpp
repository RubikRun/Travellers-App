#pragma once

#include <iostream>
#include <string>
typedef std::string str;

class Printable
{
    public:
    
        //Creates a user-friendly string representing the object
        virtual str ToStr() const = 0;
};