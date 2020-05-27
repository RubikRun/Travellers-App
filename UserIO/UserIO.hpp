#include "Printable.hpp"

#include <iostream>
#include <string>
typedef std::string str;

namespace nUserIO
{
    //Reads a command from the user
    void ReadCommand(str& command, const str* username);

    //Logs a message
    void Log(const str& msg);

    namespace nError
    {
        //Logs an error message
        void Log(const str& msg);
    }
}

//Writes the object to the stream in a user-friendly way
std::ostream& operator<<(std::ostream& stream, const Printable& obj);