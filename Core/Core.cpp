#include "Core.hpp"
#include "../Constants/Constants.hpp"

#include <iostream>
#include <fstream>
#include <functional>

Core::Core()
    : m_userIndex(USER_INDEX_INVALID) {}

Core::Core(const str& usersFile)
    : m_userIndex(USER_INDEX_INVALID), m_usersFile(usersFile)
{
    //Open database file
    std::ifstream dbFile(m_usersFile);
    if (!dbFile.is_open())
        return;

    //Read the number of users
    int usersCount;
    dbFile >> usersCount;
    //Read users
    m_users = std::vector<User>(usersCount, User());
    ITERATE_AND_DO(0, usersCount, dbFile >> m_users[i])

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
    ITERATE_AND_DO(0, m_users.size(), dbFile << m_users[i])

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
    str username = this->ReadUsername();
    str password = this->ReadPassword();
    str email = this->ReadEmail();

    //Create a user
    User user(username, password, email);

    //Add user to core's users
    m_users.push_back(user);

    //Save users to database
    this->SaveUsers();

    std::cout << REGISTER_SUCCESSFUL << std::endl;
}

void Core::LogIn()
{
    VALIDATE(m_userIndex == USER_INDEX_INVALID, ALREADY_LOGGEDIN, return)

    //Read username until a name of an existing user is entered
    str username = Core::ReadValid(
        [this](const str& username) { return (this->FindUser(username) != USER_INDEX_INVALID); },
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

int Core::FindUser(const str& username) const
{
    ITERATE_AND_FIND(0, m_users.size(), m_users[i].GetUsername() == username, return i, return USER_INDEX_INVALID)
}

int Core::FindUserByEmail(const str& email) const
{
    ITERATE_AND_FIND(0, m_users.size(), m_users[i].GetEmail() == email, return i, return USER_INDEX_INVALID)
}

str Core::ReadValid(const std::function<bool(const str&)>& IsValid, const str& enterMsg, const str& invalidMsg,
    const std::function<bool(const str&)>& IsUnique, const str& duplicateMsg)
{
    str s;
    bool valid, unique;

    do
    {
        std::cout << enterMsg;
        std::getline(std::cin, s);

        valid = IsValid(s);
        VALIDATE(valid, invalidMsg,)
        unique = IsUnique(s);
        VALIDATE(unique, duplicateMsg,)
    } while (!(valid && unique));

    return s;
}

str Core::ReadUsername()
{
    return Core::ReadValid(User::UsernameIsValid, ENTER_USERNAME, INVALID_USERNAME,
        [this](const str& username) {
            return (this->FindUser(username) == USER_INDEX_INVALID);
        },
        USERNAME_TAKEN
    );
}

str Core::ReadPassword()
{
    return Core::ReadValid(User::PasswordIsValid, ENTER_PASSWORD, INVALID_PASSWORD);
}

str Core::ReadEmail()
{
    return Core::ReadValid(User::EmailIsValid, ENTER_EMAIL, INVALID_EMAIL,
        [this](const str& email) {
            return (this->FindUserByEmail(email) == USER_INDEX_INVALID);
        },
        EMAIL_TAKEN
    );
}