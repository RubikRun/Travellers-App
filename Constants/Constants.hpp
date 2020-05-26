#pragma once

#include <string>
typedef std::string str;

namespace nName
{
    const str APP = "Traveller's App";
}

namespace nDatabase
{
    const str DIR = "Database/"; //directory
    const str EXT = ".db"; //extention

    const str USERS = "users";
    const str DESTS = "destinations";
}

namespace nUser
{
    const int NULL_IND = -1; //index indicating null
    
    namespace nUsername
    {
        const str NON_REGISTERED = "guest";
    }
}

namespace nCommand
{
    const str EXIT = "exit";
    const str HELP = "help";
    const str REGISTER = "register";
    const str LOGIN = "login";
    const str LOGOUT = "logout";
}

namespace nMsg
{
    const str WELCOME =
    "Hello! Welcome to " + nName::APP + "!\n"
    "Type \"" + nCommand::HELP + "\" if you don't know how to use it.\n";

    const str HELP =
    "Hi! I will show you how to use " + nName::APP + ".\n"
    "You can execute commands by typing them and pressing enter.\n"
    "At any moment you can type \"" + nCommand::EXIT + "\" to exit the app.\n"
    "First you need to register, or log in if you already have an account.\n"
    "   *To register type \"" + nCommand::REGISTER + "\"\n"
    "   *To log in type \"" + nCommand::LOGIN + "\"\n";
}