#include "Core.hpp"
#include "Constants.hpp"

#include <iostream>

typedef std::string str;

Core::Core()
    : m_user(nullptr) {}

Core::Core(const str& usersFile)
    : m_user(nullptr), m_usersFile(usersFile)
{
    //TODO
    //Read users from usersFile to m_users
    //TODO
}

void Core::Run()
{
    std::cout << WELCOME_MESSAGE << std::endl;
    str command;
    do
    {
        std::cout << std::endl;
        std::getline(std::cin, command);
    }
    while (this->ExecuteCommand(command));
}

bool Core::ExecuteCommand(const str& command)
{
    if (command == EXIT_COMMAND) return false;
    else if (command == HELP_COMMAND) this->Help();

    else if (command == REGISTER_COMMAND) this->Register();

    return true;
}

void Core::Help()
{
    std::cout << HELP_MESSAGE << std::endl;
}

void Core::Register()
{
    //Read user's info
    str username = User::ReadUsername();
    str password = User::ReadPassword();
    str email = User::ReadEmail();

    //Create a user
    User user(username, password, email);

    //Add user to core's users
    m_users.push_back(user);
}