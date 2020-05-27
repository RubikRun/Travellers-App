#include "Printable.hpp"

#include <iostream>
#include <string>
#include <functional>
typedef std::string str;

namespace nUserIO
{
    //Reads a command from the user
    void ReadCommand(str& command, const str* username);

    //Reads a string until a valid string is entered
    void ReadValid(str& input, const std::function<bool(const str&)>& IsValid,
        const str& enterMsg, const str& invalidMsg);

    //Logs a message
    void Log(const str& msg);

    namespace nError
    {
        //Logs an error message
        void Log(const str& msg);
    }

    //Checks if a string represents an int
    bool IsInt(const str&);
}

//Writes the object to the stream in a -friendly way
std::ostream& operator<<(std::ostream& stream, const Printable& obj);