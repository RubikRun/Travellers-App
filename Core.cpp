#include "Core.hpp"
#include "Constants.hpp"

#include <iostream>
#include <functional>

typedef std::string str;

Core::Core()
    : m_userIndex(USER_INDEX_INVALID) {}

Core::Core(const str& usersFile)
    : m_userIndex(USER_INDEX_INVALID), m_usersFile(usersFile)
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
        if (m_userIndex != USER_INDEX_INVALID)
            std::cout << m_users[m_userIndex].GetUsername() << ": ";
        std::getline(std::cin, command);
    }
    while (this->ExecuteCommand(command));
}

bool Core::ExecuteCommand(const str& command)
{
    if (command == EXIT_COMMAND) return false;
    else if (command == HELP_COMMAND) Core::Help();

    else if (command == REGISTER_COMMAND) this->Register();
    else if (command == LOGIN_COMMAND) this->LogIn();
    else if (command == LOGOUT_COMMAND) this->LogOut();

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

void Core::LogIn()
{
    //Read username until a name of an existing user is entered
    str username = Core::ReadValid(
        [this](const str& username) { return this->UserExists(username); },
        ENTER_USERNAME,
        USER_NOT_FOUND
    );

    //Find the user with the entered name
    int userIndex = this->FindUser(username);
    User& user = m_users[userIndex];

    //Read password until the correct password is entered
    Core::ReadValid(
        [&user](const str& password) {
            return user.PasswordCheck(password);
        },
        ENTER_PASSWORD,
        PASSWORD_WRONG
    );

    //Log in the user
    std::cout << LOGIN_SUCCESSFUL << std::endl;
    m_userIndex = userIndex;
}

void Core::LogOut()
{
    if (m_userIndex == USER_INDEX_INVALID)
    {
        std::cout << NOT_LOGGED_IN << std::endl;
        return;
    }

    m_userIndex = USER_INDEX_INVALID;
    std::cout << LOGOUT_SUCCESSFUL << std::endl;
}

bool Core::UserExists(const str& username) const
{
    return (this->FindUser(username) != USER_INDEX_INVALID);
}

int Core::FindUser(const str& username) const
{
    for (int i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].GetUsername() == username)
        {
            return i;
        }
    }
    return USER_INDEX_INVALID;
}

str Core::ReadValid(std::function<bool(const str&)> IsValid, const str& enterMsg, const str& invalidMsg)
{
    str s;
    bool valid;

    do
    {
        std::cout << enterMsg;
        std::getline(std::cin, s);

        valid = IsValid(s);
        if (!valid)
        {
            std::cout << invalidMsg << std::endl;
        }
    } while (!valid);

    return s;
}