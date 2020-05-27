#pragma once

#include <string>
typedef std::string str;

namespace nName
{
    const str APP = "Traveller's App";
}

namespace nDatabase
{
    const str DIR = "Databases/"; //directory
    const str EXT = ".db"; //extention

    const str USERS = "users";
    const str DESTS = "destinations";

    const char DELIMETER = '\n';
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
    const str LOGIN = "log in";
    const str LOGOUT = "log out";
    const str ADDTRIP = "add trip";
    const str LISTDESTS = "list dests";
    const str CHECKOUTDEST = "checkout dest";
    const str ADDFRIEND = "add friend";
    const str REMOVEFRIEND = "remove friend";
    const str CHECKOUTFRIEND = "checkout friend";
}

namespace nMsg
{
    const str WELCOME =
    "Hello! Welcome to " + nName::APP + "!\n"
    "Type \"" + nCommand::HELP + "\" if you don't know how to use it.\n";

    const str COMMAND_INVALID =
    "Not a valid command.\n"
    "Type \"" + nCommand::HELP + "\" if you don't know what to do.\n";

    const str HELP =
    "Hi! I will show you how to use " + nName::APP + ".\n"
    "You can execute commands by typing them and pressing enter.\n"
    "At any moment you can type \"" + nCommand::EXIT + "\" to exit the app.\n\n"
    "First you need to register, or log in if you already have an account.\n"
    "   *To register type \"" + nCommand::REGISTER + "\"\n"
    "   *To log in type \"" + nCommand::LOGIN + "\"\n\n"
    "After you are logged in you can:\n"
    "   *Add a new trip to your trips with the \"" + nCommand::ADDTRIP + "\" command\n"
    "   *List all destinations with the \"" + nCommand::LISTDESTS + "\" command\n"
    "   *Check out a destination to see how visitors rated it with the \"" + nCommand::CHECKOUTDEST + "\" command\n"
    "   *Add a friend (send/confirm a friend request) with the \"" + nCommand::ADDFRIEND + "\" command\n"
    "   *Remove a friend (or decline a friend request) with the \"" + nCommand::REMOVEFRIEND + "\" command\n"
    "   *Check out a friend to see their trips with the \"" + nCommand::CHECKOUTFRIEND + "\" command\n\n";
}