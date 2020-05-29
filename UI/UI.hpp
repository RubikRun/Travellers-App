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

    //Prints a vector of strings to the user
    void PrintVec(const std::vector<str>& vec, const str& beginMsg = "", const str& endMsg = "");

    namespace nError
    {
        //Prints an error message to the user
        void PrintMsg(const str& msg);
    }
}

namespace nMsg
{
    const str WELCOME = "TODO";
    const str HELP = "TODO";

    namespace nInvalid
    {
        const str COMMAND = "TODO";
        const str USERNAME = "TODO";
        const str PASSWORD = "TODO";
        const str EMAIL = "TODO";
        const str GRADE = "TODO";
    }

    namespace nDuplicate
    {
        const str USERNAME = "TODO";
        const str EMAIL = "TODO";
    }

    namespace nNotAllow
    {
        const str WHEN_LOGGED_IN = "TODO";
        const str WHEN_NOT_LOGGED_IN = "TODO";
        const str PASSWORD_NOT_MATCHING = "TODO";
    }

    namespace nNotExist
    {
        const str USERNAME = "TODO";
    }

    namespace nInput
    {
        const str USERNAME = "TODO";
        const str PASSWORD = "TODO";
        const str EMAIL = "TODO";
        const str DEST = "TODO";
        const str GRADE = "TODO";
        const str COMMENT = "TODO";
    }

    namespace nSuccess
    {
        const str REGISTER = "TODO";
        const str LOGIN = "TODO";
        const str LOGOUT = "TODO";
        const str ADDTRIP = "TODO";
    }

    namespace nList
    {
        const str DESTS = "TODO";
    }
}