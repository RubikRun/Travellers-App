//A file containing all functionality needed for a command line user interface

#pragma once

#include <string>
#include <functional>
typedef std::string str;

namespace nUI
{
    //Reads a command from the user
    //Shows messages (if specified) before and after the user enters a command
    str ReadCommand(const str& beginMsg = "", const str& endMsg = "");

    //Reads an input until a valid input is entered
    str ReadValidInput(const str& enterMsg,
        const std::function<bool(const str&)>& IsValid1 = [](const str&){return true;}, const str& invalidMsg1 = "",
        const std::function<bool(const str&)>& IsValid2 = [](const str&){return true;}, const str& invalidMsg2 = "");

    //Prints a message to the user
    void PrintMsg(const str& msg);

    namespace nError
    {
        //Prints an error message to the user
        void PrintMsg(const str& msg);
    }
}