#pragma once

#include "Printable.hpp"
#include "../User/User.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <functional>
typedef std::string str;

#define PRINT_VEC(vec) \
for (int i = 0; i < vec.size(); i++) \
{ \
    std::string objStr = vec[i].ToStr(); \
    nUserIO::Log(std::to_string(i + 1) + ". " + objStr); \
}

namespace nUserIO
{
    //Reads a command from the user
    void ReadCommand(str& command, const str* username);

    //Reads a string until a valid string is entered
    void ReadValid(str& input, const str& enterMsg,
        const std::function<bool(const str&)>& IsValid1 = [](const str&){return true;}, const str& invalidMsg1 = "",
        const std::function<bool(const str&)>& IsValid2 = [](const str&){return true;}, const str& invalidMsg2 = "");

    //Logs a message
    void Log(const str& msg);

    namespace nError
    {
        //Logs an error message
        void Log(const str& msg);
    }

    //Goes to the next line;
    void NextLine();

    //Checks if a string represents an int
    bool IsInt(const str&);
}

//Writes the object to the stream in a -friendly way
std::ostream& operator<<(std::ostream& stream, const Printable& obj);