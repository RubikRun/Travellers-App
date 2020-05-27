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

        nUserIO::ReadCommand(command, username);
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
    if (command == nCommand::EXIT) this->Exit();
    else if (command == nCommand::HELP) this->Help();
    else if (command == nCommand::REGISTER) this->Register();
    else if (command == nCommand::LOGIN) this->LogIn();
    else if (command == nCommand::LOGOUT) this->LogOut();
    else if (command == nCommand::ADDTRIP) this->AddTrip();
    else if (command == nCommand::LISTDESTS) this->ListDests();
    else if (command == nCommand::CHECKOUTDEST) this->CheckoutDest();
    else if (command == nCommand::ADDFRIEND) this->AddFriend();
    else if (command == nCommand::REMOVEFRIEND) this->RemoveFriend();
    else if (command == nCommand::CHECKOUTFRIEND) this->CheckoutFriend();
    else nUserIO::Log(nMsg::COMMAND_INVALID);
}

void Core::Exit()
{
    //TODO
}

void Core::Help() const
{
    //TODO
}

void Core::Register()
{
    //TODO
}

void Core::LogIn()
{
    //TODO
}

void Core::LogOut()
{
    //TODO
}

void Core::AddTrip()
{
    //TODO
}

void Core::ListDests() const
{
    //TODO
}

void Core::CheckoutDest()
{
    //TODO
}

void Core::AddFriend()
{
    //TODO
}

void Core::RemoveFriend()
{
    //TODO
}

void Core::CheckoutFriend() const
{
    //TODO
}