#include "App.hpp"
#include "UI/UI.hpp"

#include <string>
typedef std::string str;

namespace nCommand
{
    const str EXIT = "TODO";
    const str HELP = "TODO";
    const str REGISTER = "TODO";
    const str LOGIN = "TODO";
    const str LOGOUT = "TODO";
    const str ADDTRIP = "TODO";
    const str LISTDESTS = "TODO";
    const str CHECKOUTDEST = "TODO";
    const str ADDFRIEND = "TODO";
    const str REMOVEFRIEND = "TODO";
    const str CHECKOUTFRIEND = "TODO";
}

App::App()
{
    //Load the core
    m_core.Load();
}

void App::Run()
{
    m_running = true;
    nUI::PrintMsg(nMsg::WELCOME);

    while (m_running)
    {
        str currUser = m_core.GetCurrUser();

        str command = nUI::ReadCommand(currUser + ": ");
        this->ExecuteCommand(command);
    }
}

void App::ExecuteCommand(const str& command)
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
    else nUI::nError::PrintMsg(nMsg::nInvalid::COMMAND);
}

void App::Exit()
{
    //TODO
}

void App::Help() const
{
    //TODO
}

void App::Register()
{
    //TODO
}

void App::LogIn()
{
    //TODO
}

void App::LogOut()
{
    //TODO
}

void App::AddTrip()
{
    //TODO
}

void App::ListDests() const
{
    //TODO
}

void App::CheckoutDest()
{
    //TODO
}

void App::AddFriend()
{
    //TODO
}

void App::RemoveFriend()
{
    //TODO
}

void App::CheckoutFriend() const
{
    //TODO
}