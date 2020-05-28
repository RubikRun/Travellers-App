#include "App.hpp"
#include "UI/UI.hpp"

#include <string>
typedef std::string str;

#define VALIDATE(condition, onValid, onInvalid, invalidMsg) \
if (condition) \
{ \
    onValid; \
} \
else \
{ \
    nUI::nError::PrintMsg(invalidMsg); \
    onInvalid; \
}

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

//Validation functions
bool UsernameIsValid(const str&);
bool PasswordIsValid(const str&);
bool EmailIsValid(const str&);

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
    m_running = false;
}

void App::Help() const
{
    nUI::PrintMsg(nMsg::HELP);
}

void App::Register()
{
    VALIDATE(!m_core.IsThereCurrUser(), /*nothing*/, return, nMsg::nNotAllow::WHEN_NOT_LOGGED_IN)

    //Read a valid and unique username
    str username = nUI::ReadValidInput(nMsg::nInput::USERNAME, UsernameIsValid, nMsg::nInvalid::USERNAME,
        [this](const str& u) { return !this->m_core.UsernameExists(u); }, nMsg::nDuplicate::USERNAME);

    //Read a valid password
    str password = nUI::ReadValidInput(nMsg::nInput::PASSWORD, PasswordIsValid, nMsg::nInvalid::PASSWORD);

    //Read a valid and unique email
    str email = nUI::ReadValidInput(nMsg::nInput::EMAIL, EmailIsValid, nMsg::nInvalid::EMAIL,
        [this](const str& e) { return !this->m_core.EmailExists(e); }, nMsg::nDuplicate::EMAIL);

    //Add user to core
    m_core.AddUser(username, password, email);

    nUI::PrintMsg(nMsg::nSuccess::REGISTER);
}

void App::LogIn()
{
    VALIDATE(!m_core.IsThereCurrUser(), /*nothing*/, return, nMsg::nNotAllow::WHEN_NOT_LOGGED_IN)

    //Read a username of an existing user
    str username = nUI::ReadValidInput(nMsg::nInput::USERNAME,
        [this](const str& u) { return this->m_core.UsernameExists(u); }, nMsg::nNotExist::USERNAME);

    //Read a matching password
    str password = nUI::ReadValidInput(nMsg::nInput::PASSWORD,
        [this, &username](const str& p) { return this->m_core.UserPasswordMatch(username, p); },
        nMsg::nNotAllow::PASSWORD_NOT_MATCHING);

    //Log in the user
    m_core.SetCurrUser(username);

    nUI::PrintMsg(nMsg::nSuccess::LOGIN);

    //Show user's notifications
    nUI::PrintMsg(m_core.GetCurrUserNotifs());
}

void App::LogOut()
{
    VALIDATE(m_core.IsThereCurrUser(), /*nothing*/, return, nMsg::nNotAllow::WHEN_LOGGED_IN)

    //Log out the user
    m_core.LogOutCurrUser();

    nUI::PrintMsg(nMsg::nSuccess::LOGOUT);
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