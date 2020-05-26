#include "Core.hpp"
#include "../UserIO/UserInput.hpp"
#include "../Constants/Constants.hpp"
#include "../Macros/Macros.hpp"

#include <iostream>

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

void Core::LoadUsers(const str& usersDb)
{
    //TODO
}

void Core::LoadDests(const str& destsDb)
{
    //TODO
}

void Core::ExecuteCommand(const str& command)
{
    //TODO
}