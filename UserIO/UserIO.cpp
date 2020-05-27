#include "UserIO.hpp"
#include "../Constants/Constants.hpp"

#include <iostream>

void nUserIO::ReadCommand(str& command, const str* username)
{
    str displayName = (username == nullptr) ? nUser::nUsername::NON_REGISTERED : *username;
    std::cout << displayName << ": ";

    std::getline(std::cin, command);
}

void nUserIO::ReadValid(str& input, const str& enterMsg,
    const std::function<bool(const str&)>& IsValid1, const str& invalidMsg1,
    const std::function<bool(const str&)>& IsValid2, const str& invalidMsg2)
{
    //TODO
}

void nUserIO::Log(const str& msg)
{
    std::cout << msg << std::endl;
}

void nUserIO::nError::Log(const str& msg)
{
    std::cout << "Error: " << msg << std::endl;
}

void nUserIO::NextLine()
{
    std::cout << std::endl;
}

bool nUserIO::IsInt(const str&)
{
    //TODO
}

std::ostream& operator<<(std::ostream& stream, const Printable& obj)
{
    stream << obj.ToStr();
}