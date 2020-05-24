#include "Core.hpp"
#include "User.hpp"
#include "Constants.hpp"

#include <iostream>
#include <functional>

User::User(){}

User::User(const str& username, const str& password, const str& email)
    : m_username(username), m_password(password), m_email(email) {}

const str& User::GetUsername() const
{
    return m_username;
}

const str& User::GetEmail() const
{
    return m_email;
}

bool User::PasswordCheck(const str& password)
{
    return (m_password == password);
}

bool User::UsernameIsValid(const str& username)
{
    return (
        IN_INTERVAL(username.length(), MIN_USERNAME_LEN, MAX_USERNAME_LEN)
        &&
        (username.find(' ') == std::string::npos)
    );
}

bool User::PasswordIsValid(const str& password)
{
    //Check if password has at least one digit and at lest one letter
    bool digit = false, letter = false;
    ITERATE_AND_FIND(0, password.length(), std::isdigit(password[i]), digit = true,)
    ITERATE_AND_FIND(0, password.length(), std::isalpha(password[i]), letter = true,)

    return (
        digit && letter
        &&
        IN_INTERVAL(password.length(), MIN_PASSWORD_LEN, MAX_PASSWORD_LEN)
    );
}

bool User::EmailIsValid(const str& email)
{
    //don't bother reading this mess
    if (email.find(' ') != std::string::npos)
        return false;
    if (!IN_INTERVAL(email.length(), MIN_EMAIL_LEN, MAX_EMAIL_LEN))
        return false;
    int at = email.find('@');
    int dot = email.rfind('.');
    if (at == std::string::npos || dot == std::string::npos || dot < at)
        return false;
    if (
        dot - at - 1 < MIN_EMAIL_DOMAIN_LEN
        || email.length() - dot - 1 < MIN_EMAIL_DOMAIN_NETWORK_LEN
        || at < MIN_EMAIL_NAME_LEN
    )
        return false;
    return true;
}

//Reads user from stream
std::istream& operator>>(std::istream& stream, User& user)
{
    stream >> 
    user.m_username >>
    user.m_password >>
    user.m_email;

    return stream;
}

//Writes user to stream
std::ostream& operator<<(std::ostream& stream, const User& user)
{
    stream << 
    user.m_username << FILE_SEPARATOR <<
    user.m_password << FILE_SEPARATOR <<
    user.m_email << FILE_SEPARATOR;

    return stream;
}