#include <string>
typedef std::string str;

namespace nUserInput
{
    //Reads a command from the user
    void ReadCommand(str& command, const str* username);
}

namespace nUserOutput
{
    namespace nError
    {
        //Logs an error message
        void Log(const str& msg);
    }
}