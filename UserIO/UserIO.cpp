#include "UserIO.hpp"
#include "../Constants/Constants.hpp"

#include <iostream>

void nUserInput::ReadCommand(str& command, const str* username)
{
    str displayName = (username == nullptr) ? nUser::nUsername::NON_REGISTERED : *username;
    std::cout << displayName << ": ";

    std::getline(std::cin, command);
}

void nUserOutput::nError::Log(const str& msg)
{
    std::cout << "Error: " << msg << std::endl;
}
