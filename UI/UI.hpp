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
    void PrintVec(const std::vector<str>& vec, const str& beginMsg = "", const str& endMsg = "");

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

namespace nCommand
{
    const str EXIT = "TODO";
    const str HELP = "TODO";
    const str REGISTER = "TODO";
    const str LOGIN = "TODO";
    const str LOGOUT = "TODO";
    const str ADDTRIP = "TODO";
    const str LISTDESTS = "TODO";
    const str CHECKOUTDEST = "TODO";
    const str ADDFRIEND = "TODO";
    const str REMOVEFRIEND = "TODO";
    const str CHECKOUTFRIEND = "TODO";
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
        const str DATE = "TODO";
        const str PHOTOS = "TODO";
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
        const str ADDFRIEND_SELF = "TODO";
        const str ADDFRIEND_FR = "TODO";
        const str ADDFRIEND_FRREQ = "TODO";
        const str RMFRIEND_SELF = "TODO";
        const str RMFRIEND_NONFR = "TODO";
        const str CHECKOUTFR_NONFR = "TODO";
        const str END_BEFORE_BEGIN_DATE = "TODO";
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
        const str BEGIN_DATE = "TODO";
        const str END_DATE = "TODO";
        const str PHOTOS = "TODO";
    }

    namespace nSuccess
    {
        const str REGISTER = "TODO";
        const str LOGIN = "TODO";
        const str LOGOUT = "TODO";
        const str ADDTRIP = "TODO";
        const str FRREQ_SENT = "TODO";
        const str FRREQ_CONFIRMED = "TODO";
        const str RMFRIEND_FR = "TODO";
        const str FRREQ_DECLINED = "TODO";
        const str FRREQ_UNSENT = "TODO";
    }

    namespace nList
    {
        const str DESTS = "TODO";
        const str GRADES = "TODO";
        const str TRIPS = "TODO";
    }
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