#include "Core.hpp"
#include "Constants.hpp"

#include <iostream>
#include <fstream>
#include <functional>

typedef std::string str;

Core::Core()
    : m_userIndex(USER_INDEX_INVALID) {}

Core::Core(const str& usersFile)
    : m_userIndex(USER_INDEX_INVALID), m_usersFile(usersFile)
{
    //Open database file
    std::ifstream dbFile(m_usersFile, std::ios::in);
    if (!dbFile.is_open())
        return;

    //Read the number of users
    int usersCount;
    dbFile >> usersCount;
    //Read users
    m_users = std::vector<User>(usersCount, User());
    for (int i = 0; i < usersCount; i++)
    {
        dbFile >> m_users[i];
    }

    //Close database file
    dbFile.close();
    CHECK_FILE_CLOSED(dbFile, m_usersFile, return)
}

void Core::Run()
{
    std::cout << WELCOME_MESSAGE << std::endl;
    str command;
    do
    {
        std::cout << std::endl;
        //If the user has logged in, print their username before each command they type
        if (m_userIndex != USER_INDEX_INVALID)
            std::cout << m_users[m_userIndex].GetUsername() << ": ";
        std::getline(std::cin, command);
    }
    while (this->ExecuteCommand(command));
}

bool Core::ExecuteCommand(const str& command)
{
    //Handle each command type separately
    if (command == EXIT_COMMAND) return false;
    else if (command == HELP_COMMAND) Core::Help();

    else if (command == REGISTER_COMMAND) this->Register();
    else if (command == LOGIN_COMMAND) this->LogIn();
    else if (command == LOGOUT_COMMAND) this->LogOut();
    else std::cout << INVALID_COMMAND_MESSAGE;

    return true;
}

void Core::SaveUsers() const
{
    //Open database file
    std::ofstream dbFile(m_usersFile);
    CHECK_FILE_OPENED(dbFile, m_usersFile, return)

    //Write the number of users
    dbFile << m_users.size() << FILE_SEPARATOR;
    //Write users
    for (int i = 0; i < m_users.size(); i++)
        dbFile << m_users[i];

    //Close database file
    dbFile.close();
    CHECK_FILE_CLOSED(dbFile, m_usersFile, return)
}

void Core::Help()
{
    std::cout << HELP_MESSAGE << std::endl;
}

void Core::Register()
{
    VALIDATE(m_userIndex == USER_INDEX_INVALID, CANT_REGISTER_WHILE_LOGGEDIN, return)

    //Read user's info
    str username;
    while (true)
    {
        username = User::ReadUsername();
        VALIDATE(this->FindUser(username) == USER_INDEX_INVALID, USERNAME_TAKEN, continue)
        break;
    }
    str password = User::ReadPassword();
    str email = User::ReadEmail();

    //Create a user
    User user(username, password, email);

    //Add user to core's users
    m_users.push_back(user);

    //Save users to database
    this->SaveUsers();
}

void Core::LogIn()
{
    VALIDATE(m_userIndex == USER_INDEX_INVALID, ALREADY_LOGGEDIN, return)

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
    VALIDATE(m_userIndex != USER_INDEX_INVALID, NOT_LOGGED_IN, return)

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
        VALIDATE(valid, invalidMsg,)
    } while (!valid);

    return s;
}