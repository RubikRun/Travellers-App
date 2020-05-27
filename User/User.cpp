#include "User.hpp"

User::User(){}

const str& User::GetUsername() const
{
    return m_username;
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