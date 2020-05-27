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

str User::GetNotificationsStr() const
{
    //TODO
}

void User::AddTrip(const Trip& trip)
{
    //TODO
}

const std::vector<Trip>& User::GetTrips() const
{
    //TODO
}

bool User::IsFriend(int userInd) const
{
    //TODO
}

bool User::HasFriendRequest(int userInd) const
{
    //TODO
}

void User::AcceptFriendRequest(int userInd)
{
    //TODO
}

void User::ReceiveFriendRequest(int userInd)
{
    //TODO
}

void User::RemoveFriend(int userInd)
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