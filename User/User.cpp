#include "User.hpp"

User::User(){}

User::User(const str& username, const str& password, const str& email)
    : m_username(username), m_password(password), m_email(email) {}

const str& User::GetUsername() const
{
    return m_username;
}

bool User::PasswordsMatch(const str& password)
{
    //TODO
}

void User::AddTrip(const Trip& trip)
{
    //TODO
}

bool User::UsernameIsValid(const str&)
{
    //TODO
}

bool User::PasswordIsValid(const str&)
{
    //TODO
}

bool User::EmailIsValid(const str&)
{
    //TODO
}

str User::Serialize() const
{
    //TODO
}

void User::Deserialize(const str&)
{
    //TODO
}

str User::ToStr() const
{
    //TODO
}