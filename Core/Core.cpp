#include "Core.hpp"
#include "Database/DatabaseIO.hpp"
#include "../UI/UI.hpp"

#include <vector>
#include <fstream>
#include <string>
typedef std::string str;

#define OPEN_IFILE(file, filename, errorMsg, onerror) \
std::ifstream file(filename); \
if (!file.is_open()) { \
    nUI::nError::PrintMsg(errorMsg); \
    onerror; \
}

#define OPEN_OFILE(file, filename, errorMsg, onerror) \
std::ofstream file(filename); \
if (!file.is_open()) { \
    nUI::nError::PrintMsg(errorMsg); \
    onerror; \
}

#define CLOSE_FILE(file, errorMsg, onerror) \
file.close(); \
if (file.is_open()) { \
    nUI::nError::PrintMsg(errorMsg); \
    onerror; \
}

namespace nDatabase
{
    const str DIR = "Core/Database/dbFiles/";
    const str EXT = ".db";

    const str USERS = DIR + "users" + EXT;
    const str DESTS = DIR + "dests" + EXT;
}

namespace nFile
{
    const str CANNOT_OPEN = "Cannot open file: ";
    const str CANNOT_CLOSE = "Cannot close file: ";
}

namespace nUser
{
    const int NULL_IND = -1;
    const str NULL_USERNAME = "guest";
}

Core::Core()
{
    m_currUserInd = nUser::NULL_IND;
}

void Core::Load()
{
    this->LoadUsers(nDatabase::USERS);
    this->LoadDests(nDatabase::DESTS);
}

void Core::Save()
{
    this->SaveUsers(nDatabase::USERS);
    this->SaveDests(nDatabase::DESTS);
}

void Core::AddUser(const str& username, const str& password, const str& email)
{
    m_users.emplace_back(username, password, email);
}

bool Core::UsernameExists(const str& username) const
{
    return (this->FindUser(username) != nUser::NULL_IND);
}

bool Core::EmailExists(const str& email) const
{
    for (int i = 0; i < m_users.size(); i++)
        if (m_users[i].GetEmail() == email)
            return true;
    return false;
}

bool Core::DestExists(const str& dest) const
{
    for (auto it = m_destUserGrades.begin(); it != m_destUserGrades.end(); it++)
        if (it->first == dest)
            return true;
    return false;
}

bool Core::UserPasswordMatch(const str& username, const str& password) const
{
    int userInd = this->FindUser(username);
    if (userInd == nUser::NULL_IND)
        return false;

    return m_users[userInd].PasswordsMatch(password);
}

bool Core::IsThereCurrUser() const
{
    return (m_currUserInd != nUser::NULL_IND);
}

void Core::SetCurrUser(const str& username)
{
    m_currUserInd = this->FindUser(username);
}

const str& Core::GetCurrUser() const
{
    if (m_currUserInd == nUser::NULL_IND)
        return nUser::NULL_USERNAME;
    else
        return m_users[m_currUserInd].GetUsername();
}

void Core::LogOutCurrUser()
{
    m_currUserInd = nUser::NULL_IND;
}

void Core::CurrUserAddTrip(const str& dest, const Date& begin, const Date& end,
        int grade, const str& comment, const std::vector<str>& photos)
{
    if (m_currUserInd == nUser::NULL_IND)
        return;

    m_users[m_currUserInd].AddTrip(dest, begin, end, grade, comment, photos);

    //If the destination is new, initialize the vector for its grades
    if (m_destUserGrades.find(dest) == m_destUserGrades.end())
        m_destUserGrades[dest] = std::vector<UserGrade>();

    m_destUserGrades[dest].push_back( {this->GetCurrUser(), grade} );
}

std::vector<str> Core::GetDests() const
{
    std::vector<str> dests;
    for (auto it = m_destUserGrades.begin(); it != m_destUserGrades.end(); it++)
    {
        str dest = it->first;
        dests.push_back(dest);
    }
    
    return dests;
}

const std::vector<UserGrade>& Core::GetUsersGrades(const str& dest) const
{
    return m_destUserGrades.at(dest);
}

bool Core::AreFr(const str& username1, const str& username2) const
{
    int user1 = this->FindUser(username1);
    int user2 = this->FindUser(username2);
    if (user1 == nUser::NULL_IND || user2 == nUser::NULL_IND)
        return false;
    
    return (m_friends.at(user1).count(user2) == 1 && m_friends.at(user2).count(user1) == 1);
}

bool Core::HasFrReqFrom(const str& username1, const str& username2) const
{
    int user1 = this->FindUser(username1);
    int user2 = this->FindUser(username2);
    if (user1 == nUser::NULL_IND || user2 == nUser::NULL_IND)
        return false;

    return (m_friends.at(user1).count(user2) == 0 && m_friends.at(user2).count(user1) == 1);
}

void Core::SendFrReq(const str& username1, const str& username2)
{
    int user1 = this->FindUser(username1);
    int user2 = this->FindUser(username2);
    if (user1 == nUser::NULL_IND || user2 == nUser::NULL_IND)
        return;

    m_friends[user1].insert(user2);
}

void Core::UnsendFrReq(const str& username1, const str& username2)
{
    int user1 = this->FindUser(username1);
    int user2 = this->FindUser(username2);
    if (user1 == nUser::NULL_IND || user2 == nUser::NULL_IND)
        return;

    m_friends[user1].erase(user2);
}

void Core::ConfirmFrReq(const str& username1, const str& username2)
{
    int user1 = this->FindUser(username1);
    int user2 = this->FindUser(username2);
    if (user1 == nUser::NULL_IND || user2 == nUser::NULL_IND)
        return;

    if (m_friends[user2].count(user1) == 0)
        return;

    m_friends[user1].insert(user2);
}

void Core::DeclineFrReq(const str& username1, const str& username2)
{
    int user1 = this->FindUser(username1);
    int user2 = this->FindUser(username2);
    if (user1 == nUser::NULL_IND || user2 == nUser::NULL_IND)
        return;

    m_friends[user2].erase(user1);
}

void Core::RmFr(const str& username1, const str& username2)
{
    int user1 = this->FindUser(username1);
    int user2 = this->FindUser(username2);
    if (user1 == nUser::NULL_IND || user2 == nUser::NULL_IND)
        return;

    m_friends[user1].erase(user2);
    m_friends[user2].erase(user1);
}

const std::vector<Trip>& Core::GetUserTrips(const str& username) const
{
    int userInd = this->FindUser(username);

    return m_users[userInd].GetTrips();
}

std::vector<str> Core::GetCurrUserFrReqs() const
{
    if (m_currUserInd == nUser::NULL_IND)
        return std::vector<str>();

    std::vector<str> frReqs;

    for (auto it = m_friends.begin(); it != m_friends.end(); it++)
    {
        int otherUser = it->first;
        if (m_friends.at(otherUser).count(m_currUserInd) == 1
            && m_friends.at(m_currUserInd).count(otherUser) == 0)
        {
            str otherUserUsername = m_users[otherUser].GetUsername();
            frReqs.push_back(otherUserUsername);
        }
    }

    return frReqs;
}

void Core::LoadUsers(const str& dbName)
{
    OPEN_IFILE(db, dbName, nFile::CANNOT_OPEN + dbName, return)

    //Read the users
    this->ReadUsers(db);

    //Read the friendships between users
    this->ReadFriendships(db);

    CLOSE_FILE(db, nFile::CANNOT_CLOSE + dbName,)
}

void Core::LoadDests(const str& dbName)
{
    OPEN_IFILE(db, dbName, nFile::CANNOT_OPEN + dbName, return)

    m_destUserGrades.clear();

    //Read the number of destinations
    int destsCount = nDatabaseIO::ReadInt(db);
    //Read destinations and for each destination a list of grades
    for (int i = 0; i < destsCount; i++)
    {
        str currDest = nDatabaseIO::ReadStr(db);
        m_destUserGrades[currDest] = std::vector<UserGrade>();
        int gradesCount = nDatabaseIO::ReadInt(db);
        for (int j = 0; j < gradesCount; j++)
        {
            str currUser = nDatabaseIO::ReadStr(db);
            int currGrade = nDatabaseIO::ReadInt(db);
            //Add grade
            m_destUserGrades[currDest].push_back( {currUser, currGrade} );
        }
    }

    CLOSE_FILE(db, nFile::CANNOT_CLOSE + dbName,)
}

void Core::SaveUsers(const str& dbName) const
{
    OPEN_OFILE(db, dbName, nFile::CANNOT_OPEN + dbName, return)

    //Write the users
    this->WriteUsers(db);

    //Write friendships
    this->WriteFriendships(db);

    CLOSE_FILE(db, nFile::CANNOT_CLOSE + dbName,)
}

void Core::SaveDests(const str& dbName) const
{
    OPEN_OFILE(db, dbName, nFile::CANNOT_OPEN + dbName, return)

    //Write the number of destinations
    nDatabaseIO::WriteInt(m_destUserGrades.size(), db);
    //Write destinations and for each destination a list of grades
    for (auto destIt = m_destUserGrades.begin(); destIt != m_destUserGrades.end(); destIt++)
    {
        str currDest = destIt->first;
        const std::vector<UserGrade>& currGrades = destIt->second;
        //Write the current destination
        nDatabaseIO::WriteStr(currDest, db);
        //Write the number of grades of the current destination
        nDatabaseIO::WriteInt(currGrades.size(), db);
        for (int i = 0; i < currGrades.size(); i++)
        {
            //Write current user grade
            nDatabaseIO::WriteStr(currGrades[i].username, db);
            nDatabaseIO::WriteInt(currGrades[i].grade, db);
        }
    }

    CLOSE_FILE(db, nFile::CANNOT_CLOSE + dbName,)
}

void Core::ReadUsers(std::ifstream& db)
{
    //Read the number of users
    int usersCount = nDatabaseIO::ReadInt(db);
    //Read users
    m_users = std::vector<User>(usersCount);
    for (int i = 0; i < usersCount; i++)
    {
        nDatabaseIO::ReadObj(m_users[i], db);
    }
}

void Core::ReadFriendships(std::ifstream& db)
{
    m_friends.clear();

    //Read the number of users who have a set of friends in the map of friendships
    int usersWithFriendsCount = nDatabaseIO::ReadInt(db);
    //Read each user's set of friends
    for (int i = 0; i < usersWithFriendsCount; i++)
    {
        int currUser = nDatabaseIO::ReadInt(db);
        m_friends[currUser] = std::set<int>();
        int friendsCount = nDatabaseIO::ReadInt(db);
        for (int j = 0; j < friendsCount; j++)
        {
            int currFriend = nDatabaseIO::ReadInt(db);
            //Add friend
            m_friends[currUser].insert(currFriend);
        }
    }
}

void Core::WriteUsers(std::ofstream& db) const
{
    //Write the number of users
    nDatabaseIO::WriteInt(m_users.size(), db);
    //Write users
    for (int i = 0; i < m_users.size(); i++)
    {
        nDatabaseIO::WriteObj(m_users[i], db);
    }
}

void Core::WriteFriendships(std::ofstream& db) const
{
    //Write the number of users who have a set of friends in the map of friendships
    nDatabaseIO::WriteInt(m_friends.size(), db);
    //Write each user's set of friends
    for (auto it = m_friends.begin(); it != m_friends.end(); it++)
    {
        int currUser = it->first;
        const std::set<int>& currFriends = it->second;
        //Write user to database
        nDatabaseIO::WriteInt(currUser, db);
        //Write the number of friends of this user
        nDatabaseIO::WriteInt(currFriends.size(), db);
        //Write the friends of this user
        for (auto fr = currFriends.begin(); fr != currFriends.end(); fr++)
        {
            //Write friends
            nDatabaseIO::WriteInt(*fr, db);
        }
    }
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
    return nUser::NULL_IND;
}