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

namespace nUsername
{
    namespace nLength
    {
        const int MIN = 3;
        const int MAX = 30;
    }
}

namespace nPassword
{
    namespace nLength
    {
        const int MIN = 8;
        const int MAX = 40;
    }
}

namespace nEmail
{
    const char AT = '@';
    const char DOT = '.';
    const int AT_DOT_DIFF = 2;
    const int DOT_DIFF = 2;
    const int AT_DIFF = 1;
    namespace nLength
    {
        const int MIN = AT_DIFF + 1 + AT_DOT_DIFF + 1 + DOT_DIFF;
        const int MAX = 40;
    }
}

namespace nDest
{
    const int NULL_IND = -1; //index indicating null
}

namespace nDate
{
    const str FORMAT = "dd.mm.yyyy";
}

namespace nGrade
{
    const int MIN = 0;
    const int MAX = 5;
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
    "   *Add a friend (send/accept a friend request) with the \"" + nCommand::ADDFRIEND + "\" command\n"
    "   *Remove a friend (or decline a friend request) with the \"" + nCommand::REMOVEFRIEND + "\" command\n"
    "   *Check out a friend to see their trips with the \"" + nCommand::CHECKOUTFRIEND + "\" command\n\n";

    namespace nList
    {
        const str DESTS =
        "All destinations: ";

        const str AVG_DEST_GRADE =
        "Destination's average grade: ";

        const str DEST_GRADES =
        "All grades it recieved: ";

        const str TRIPS =
        "All user's trips: ";
    }

    namespace nEnter
    {
        const str USERNAME =
        "Enter username: ";

        const str PASSWORD =
        "Enter password: ";

        const str EMAIL =
        "Enter email: ";

        const str DEST =
        "Enter destination: ";

        const str BEGIN =
        "Enter begin date: ";

        const str END =
        "Enter end date: ";

        const str GRADE =
        "Enter grade: ";

        const str COMMENT =
        "Enter comment: ";

        const str PHOTOS_COUNT =
        "Enter the number of photos: ";

        const str ADDFRIEND =
        "Enter username of the user you want to add as a friend: ";

        const str RMFRIEND =
        "Enter username of the user you want to remove from you friends: ";

        const str CHECKOUTFRIEND =
        "Enter username of you friend whose trips you want to see: ";
    }

    namespace nSuccess
    {
        const str REGISTER =
        "You registered successfully.";

        const str LOGIN =
        "You logged in successfully.";

        const str LOGOUT =
        "You logged out successfully.";

        const str ADDTRIP =
        "Trip added successfully.";

        const str ACCEPT_FRREQ =
        "Friend request accepted.";

        const str SENT_FRREQ =
        "Friend request sent.";

        const str REMOVE_FRIEND =
        "Friend removed successfully.";
    }

    namespace nInvalid
    {
        const str COMMAND =
        "Not a valid command.\n"
        "Type \"" + nCommand::HELP + "\" if you don't know what to do.\n";

        const str USERNAME =
        "Not a valid username.\n"
        "Usernames should be between " +
        std::to_string(nUsername::nLength::MIN) + " and " + std::to_string(nUsername::nLength::MAX)
        + " characters long and contain no spaces.";

        const str PASSWORD =
        "Not a valid password.\n"
        "Passwords should be between " +
        std::to_string(nPassword::nLength::MIN) + " and " + std::to_string(nPassword::nLength::MAX)
        + " characters long\n"
        "and contain at least one letter and at least one digit.";

        const str EMAIL =
        "Not a valid email address.";

        const str DATE =
        "Not a valid date. Dates should be in " + nDate::FORMAT + " format.";

        const str END_DATE =
        "End date cannot be before begin date.\n"
        "Also it should be in " + nDate::FORMAT + " format.";

        const str GRADE =
        "Not a valid grade.\n"
        "Grades should be integers between " +
        std::to_string(nGrade::MIN) + " and " + std::to_string(nGrade::MAX) + ".";

        const str PHOTOS_COUNT =
        "Not a valid number. It should be a non-negative integer.";

        const str PHOTO =
        "Not a valid photo file name.\n"
        "Photo file names should contain only letters and underscores\n"
        "and have a .png or .jpeg extension.";
    }

    namespace nNotUnique
    {
        const str USERNAME =
        "There is already a user with this username.";

        const str EMAIL =
        "This email is being used by another user.";
    }

    namespace nNotAllow
    {
        const str REGISTER_LOGGED =
        "You cannot register while you're logged in.";

        const str LOGIN_LOGGED =
        "You are already logged in.\n"
        "Use \"" + nCommand::LOGOUT + "\" command to log out.";

        const str PASSWORD =
        "Incorrect password.";

        const str LOGOUT_NONLOGGED =
        "You cannot log out. You are not logged in.";

        const str ADDTRIP_NONLOGGED =
        "You cannot add a trip. You are not logged in.";

        const str LISTDESTS_NONLOGGED =
        "You cannot list destinations. You are not logged in.";

        const str CHECKOUTDEST_NONLOGGED =
        "You cannot check out a destination. You are not logged in.";

        const str ADDFRIEND_NONLOGGED =
        "You cannot add a friend. You are not logged in.";

        const str ADDFRIEND_FRIEND =
        "This user is already your friend.";

        const str RMFRIEND_NONLOGGED =
        "You cannot remove a friend. You are not logged in.";

        const str RM_NONFRIEND =
        "This user is already not your friend.";

        const str CHECKOUTFRIEND_NONLOGGED =
        "You cannot checkout a friend. You are not logged in.";

        const str CHECKOUT_NONFRIEND =
        "You are not a friend of this user, you cannot see his trips";
    }

    namespace nNotExist
    {
        const str USERNAME =
        "There is no user with this username.";

        const str DESTNAME =
        "There is no destination with this name";
    }
}