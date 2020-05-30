//A file containing all functionality needed for a command line user interface

#pragma once

#include "../Core/Core.hpp"

#include <vector>
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
    void PrintMsg(const str& msg, const str& begin = "", const str& end = "\n\n");

    //Prints a vector of strings to the user
    void PrintVec(const std::vector<str>& vec, const str& beginMsg = "", const str& endMsg = "", bool lineNumbers = true);

    namespace nError
    {
        //Prints an error message to the user
        void PrintMsg(const str& msg);
    }

    //Reads a valid and unique username
    str ReadValidUniqueUsername(const Core*);

    //Reads a valid password
    str ReadValidPassword();

    //Reads a valid and unique email
    str ReadValidUniqueEmail(const Core*);

    //Reads a username of an existing user
    str ReadExistingUsername(const Core*);

    //Reads a password until user's password is entered
    str ReadMatchingPassword(const Core*, const str& username);

    //Reads a destination
    str ReadDest();

    //Reads an existing destination
    str ReadExistingDest(const Core*);

    //Reads valid begin and end dates
    void ReadBeginEndDate(Date& begin, Date& end);

    //Reads a valid grade
    int ReadValidGrade();

    //Reads a comment
    str ReadComment();

    //Reads valid photos
    void ReadPhotos(std::vector<str>& photos);

    //Prints a list of grades
    void PrintUsersGrades(const std::vector<UserGrade>& usersGrades);

    //Prints a list of trips
    void PrintTrips(const std::vector<Trip>& trips);
}

//Input validation functions
namespace nInputValidator
{
    bool Username(const str&);
    bool Password(const str&);
    bool Email(const str&);
    bool DateStr(const str&);
    bool GradeStr(const str&);
    bool Photo(const str&);
}

namespace nString
{
    //Splits a string on a given delimeter, returns a vector of the resulting parts
    std::vector<str> Split(const str&, const char delimeter = ' ');

    //Checks if a string represents an int
    bool StrIsInt(const str&);

    //Checks if a string ends with a given suffix
    bool EndsWith(const str&, const str& suffix);
}

namespace nApp
{
    const str NAME = "Traveller's App";
}

namespace nCommand
{
    const str EXIT = "exit";
    const str HELP = "help";
    const str REGISTER = "register";
    const str LOGIN = "login";
    const str LOGOUT = "logout";
    const str ADDTRIP = "add_trip";
    const str LISTDESTS = "list_dests";
    const str CHECKOUTDEST = "checkout_dest";
    const str ADDFRIEND = "add_fr";
    const str REMOVEFRIEND = "rm_fr";
    const str CHECKOUTFRIEND = "checkout_fr";
}

namespace nUsername
{
    const int MIN_LEN = 3;
    const int MAX_LEN = 30;
}

namespace nPassword
{
    const int MIN_LEN = 8;
    const int MAX_LEN = 40;
}

namespace nEmail
{
    const char AT = '@';
    const char DOT = '.';
    const int AT_DIFF = 2;
    const int AT_DOT_DIFF = 2;
    const int DOT_DIFF = 2;
    
    const int MIN_LEN = AT_DIFF + 1 + AT_DOT_DIFF + 1 + DOT_DIFF;
    const int MAX_LEN = 40;
}

namespace nGrade
{
    const int MIN = 1;
    const int MAX = 5;
}

namespace nPhoto
{
    const str JPEG_EXT = ".jpeg";
    const str PNG_EXT = ".png";
}

namespace nMsg
{
    const str WELCOME =
    "Hello! Welcome to " + nApp::NAME + "!\n"
    "Type \"" + nCommand::HELP + "\" if you don't know how to use it.";

    const str HELP =
    "Hi! I will show you how to use " + nApp::NAME + ".\n"
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
    "   *Check out a friend to see their trips with the \"" + nCommand::CHECKOUTFRIEND + "\" command";

    namespace nInvalid
    {
        const str COMMAND =
        "Not a valid command.\n"
        "Type \"" + nCommand::HELP + "\" if you don't know what to do.";

        const str USERNAME =
        "Not a valid username.\n"
        "Usernames should be between "
        + std::to_string(nUsername::MIN_LEN) + " and " + std::to_string(nUsername::MAX_LEN)
        + " characters long and contain no spaces.";

        const str PASSWORD =
        "Not a valid password.\n"
        "Passwords should be between "
        + std::to_string(nPassword::MIN_LEN) + " and " + std::to_string(nPassword::MAX_LEN)
        + " characters long.";

        const str EMAIL = "Not a valid email address.";

        const str GRADE =
        "Not a valid grade.\n"
        "Grades should be integers between "
        + std::to_string(nGrade::MIN) + " and " + std::to_string(nGrade::MAX) + ".";

        const str DATE = 
        "Not a valid date.\n"
        "Dates should be in dd.mm.yyyy format.";

        const str PHOTOS = 
        "Not valid photo names.\n"
        "They should be space separated file names.\n"
        "Each file name can contain only letters and underscores,\n"
        "and should be in " + nPhoto::JPEG_EXT + " or " + nPhoto::PNG_EXT + " format.";
    }

    namespace nDuplicate
    {
        const str USERNAME = "There is already a user with this username";
        const str EMAIL = "There is already a user with this email";
    }

    namespace nNotAllow
    {
        const str WHEN_LOGGED_IN = "You cannot execute this command when you are logged in.";
        const str WHEN_NOT_LOGGED_IN = "You cannot execute this command when you are not logged in.";
        const str PASSWORD_NOT_MATCHING = "Incorrect password";
        const str ADDFRIEND_SELF = "You cannot add yourself as a friend";
        const str ADDFRIEND_FR = "This user is already your friend";
        const str ADDFRIEND_FRREQ = "You have already sent a friend request to this user";
        const str RMFRIEND_SELF = "You cannot unfriend yourself";
        const str RMFRIEND_NONFR = "This user is already not your friend";
        const str CHECKOUTFR_NONFR = "You are not friends with this user, you cannot check him out";
        const str END_BEFORE_BEGIN_DATE = "End date should be after begin date";
    }

    namespace nNotExist
    {
        const str USERNAME = "There is no user with this username.";
        const str DEST = "There is no destination with this name.";
    }

    namespace nInput
    {
        const str USERNAME = "Enter username: ";
        const str PASSWORD = "Enter password: ";
        const str EMAIL = "Enter email: ";
        const str DEST = "Enter destination: ";
        const str GRADE = "Enter grade: ";
        const str COMMENT = "Enter comment: ";
        const str BEGIN_DATE = "Enter begin date: ";
        const str END_DATE = "Enter end date: ";
        const str PHOTOS = "Enter photos: ";
    }

    namespace nSuccess
    {
        const str REGISTER = "You registered successfully.";
        const str LOGIN = "You logged in successfully.";
        const str LOGOUT = "You logged out successfully.";
        const str ADDTRIP = "You added a trip successfully.";
        const str FRREQ_SENT = "You sent a friend request successfully.";
        const str FRREQ_CONFIRMED = "Friend request confirmed.";
        const str RMFRIEND_FR = "Friend removed.";
        const str FRREQ_DECLINED = "Friend request declined.";
        const str FRREQ_UNSENT = "Friend request unsent.";
    }

    namespace nList
    {
        const str DESTS = "List of all destinations:";
        const str GRADES = "List of grades of the destination:";
        const str TRIPS = "List of trips of the user:";
    }

    namespace nNotif
    {
        const str FRREQS = "Notifications: You have friend requests from these users:";
    }

    namespace nTrip
    {
        const str DEST = "Destination: ";
        const str BEGIN_DATE = "Begin date: ";
        const str END_DATE = "End date: ";
        const str GRADE = "Grade: ";
        const str COMMENT = "Comment: ";
        const str PHOTOS = "Photos: ";
    }
}