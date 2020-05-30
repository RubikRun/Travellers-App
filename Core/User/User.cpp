#include "User.hpp"
#include "../Database/DatabaseIO.hpp"

User::User(){}

User::User(const str& username, const str& password, const str& email)
    : m_username(username), m_password(password), m_email(email) {}

const str& User::GetUsername() const
{
    return m_username;
}

bool User::PasswordsMatch(const str& password) const
{
    return (m_password == password);
}

const str& User::GetEmail() const
{
    return m_email;
}

const std::vector<Trip>& User::GetTrips() const
{
    return m_trips;
}

void User::AddTrip(const str& dest, const Date& begin, const Date& end,
        int grade, const str& comment, const std::vector<str>& photos)
{
    m_trips.emplace_back(dest, begin, end, grade, comment, photos);
}

void User::SerializeTo(std::ostream& stream) const
{
    nDatabaseIO::WriteStr(m_username, stream);
    nDatabaseIO::WriteStr(m_password, stream);
    nDatabaseIO::WriteStr(m_email, stream);

    nDatabaseIO::WriteInt(m_trips.size(), stream);
    for (int i = 0; i < m_trips.size(); i++)
    {
        m_trips[i].SerializeTo(stream);
    }
}

void User::DeserializeFrom(std::istream& stream)
{
    m_username = nDatabaseIO::ReadStr(stream);
    m_password = nDatabaseIO::ReadStr(stream);
    m_email = nDatabaseIO::ReadStr(stream);

    int tripsCount = nDatabaseIO::ReadInt(stream);
    m_trips = std::vector<Trip>(tripsCount);
    for (int i = 0; i < tripsCount; i++)
    {
        m_trips[i].DeserializeFrom(stream);
    }
}