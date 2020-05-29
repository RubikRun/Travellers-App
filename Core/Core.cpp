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
    const str DIR = "Database/";
    const str EXT = ".db";

    const str USERS = DIR + "users" + EXT;
    const str DESTS = DIR + "dests" + EXT;
}

namespace nFile
{
    const str CANNOT_OPEN = "TODO";
    const str CANNOT_CLOSE = "TODO";
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