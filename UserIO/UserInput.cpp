#include "UserInput.hpp"
#include "../Constants/Constants.hpp"

#include <iostream>

void nUserInput::ReadCommand(str& command, const str* username)
{
    str displayName = (username == nullptr) ? nUser::nUsername::NON_REGISTERED : *username;
    std::cout << displayName << ": ";

    std::getline(std::cin, command);
}