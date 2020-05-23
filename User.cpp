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

bool User::PasswordCheck(const str& password)
{
    return (m_password == password);
}

str User::ReadUsername()
{
    return Core::ReadValid(User::UsernameIsValid, ENTER_USERNAME, INVALID_USERNAME);
}

str User::ReadPassword()
{
    return Core::ReadValid(User::PasswordIsValid, ENTER_PASSWORD, INVALID_PASSWORD);
}

str User::ReadEmail()
{
    return Core::ReadValid(User::EmailIsValid, ENTER_EMAIL, INVALID_EMAIL);
}

bool User::UsernameIsValid(const str& username)
{
    return (
        (username.length() >= MIN_USERNAME_LEN && username.length() <= MAX_USERNAME_LEN)
        &&
        (username.find(' ') == std::string::npos)
    );
}

bool User::PasswordIsValid(const str& password)
{
    //Check if password has at least one digit and at lest one letter
    bool digit = false, letter = false;
    for (int i = 0; i < password.length(); i++)
    {
        if (std::isdigit(password[i]))
        {
            digit = true;
        }
        if (std::isalpha(password[i]))
        {
            letter = true;
        }
    }

    return (
        digit && letter
        &&
        (password.length() >= MIN_PASSWORD_LEN && password.length() <= MAX_PASSWORD_LEN)
    );
}

bool User::EmailIsValid(const str& email)
{
    if (email.find(' ') != std::string::npos)
        return false;
    if (email.length() < MIN_EMAIL_LEN || email.length() > MAX_EMAIL_LEN)
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