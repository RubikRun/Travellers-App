#include "UserIO.hpp"
#include "../Constants/Constants.hpp"

#include <iostream>

std::ostream& operator<<(std::ostream& stream, const Printable& obj)
{
    stream << obj.ToStr();
}

void nUserIO::ReadCommand(str& command, const str* username)
{
    str displayName = (username == nullptr) ? nUser::nUsername::NON_REGISTERED : *username;
    std::cout << displayName << ": ";

    std::getline(std::cin, command);
}

void nUserIO::Log(const str& msg)
{
    std::cout << msg << std::endl;
}

void nUserIO::nError::Log(const str& msg)
{
    std::cout << "Error: " << msg << std::endl;
}
