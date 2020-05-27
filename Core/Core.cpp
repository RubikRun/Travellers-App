#include "Core.hpp"
#include "../UserIO/UserIO.hpp"
#include "../DatabaseIO/DatabaseIO.hpp"
#include "../Constants/Constants.hpp"

Core::Core()
    : m_userInd(nUser::NULL_IND), m_running(false) {}

void Core::Load(const str& usersDb, const str& destsDb)
{
    CHECK_FILE_EXISTS(usersDb, this->LoadUsers(usersDb),)
    CHECK_FILE_EXISTS(destsDb, this->LoadDests(destsDb),)
}

void Core::Run()
{
    m_running = true;
    std::cout << "\n" << nMsg::WELCOME << "\n";

    str command;
    while (m_running)
    {
        const str* username = (m_userInd == nUser::NULL_IND) ?
            nullptr : &m_users[m_userInd].GetUsername();

        nUserInput::ReadCommand(command, username);
        this->ExecuteCommand(command);
    }
}

void Core::LoadUsers(const str& dbName)
{
    //Open users database
    OPEN_IFILE(db, dbName, return)

    //Read users from database
    DB_READ_VEC(db, m_users, User)

    //Close database
    CLOSE_FILE(db, dbName, return)
}

void Core::SaveUsers(const str& dbName)
{
    //Open users database
    OPEN_OFILE(db, dbName, return)

    //Read users from database
    DB_WRITE_VEC(db, m_users, User)

    //Close database
    CLOSE_FILE(db, dbName, return)
}

void Core::LoadDests(const str& dbName)
{
    //Open destinations database
    OPEN_IFILE(db, dbName, return)

    //Read destinations from database
    DB_READ_VEC(db, m_dests, Destination)

    //Close database
    CLOSE_FILE(db, dbName, return)
}

void Core::SaveDests(const str& dbName)
{
    //Open destinations database
    OPEN_OFILE(db, dbName, return)

    //Read destinations from database
    DB_WRITE_VEC(db, m_dests, Destination)

    //Close database
    CLOSE_FILE(db, dbName, return)
}

void Core::ExecuteCommand(const str& command)
{
    //TODO
}