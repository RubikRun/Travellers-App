#include "Core.hpp"
#include "Constants.hpp"

#include <iostream>

Core::Core()
    : m_user(nullptr) {}

Core::Core(const std::string& usersFile)
    : m_user(nullptr)
{
    //TODO
    //Read users from usersFile to m_users
    //TODO
}

void Core::Run()
{
    std::cout << WELCOME_MESSAGE << std::endl;
    std::string command;
    do
    {
        std::cin >> command;
    }
    while (this->ExecuteCommand(command));
}

bool Core::ExecuteCommand(const std::string& command)
{
    return true;
}