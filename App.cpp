#include "App.hpp"
#include "UI/UI.hpp"

#include <vector>
#include <string>
typedef std::string str;

#define DONT_ALLOW_LOGGED_IN \
if (m_core.IsThereCurrUser()) { \
    nUI::nError::PrintMsg(nMsg::nNotAllow::WHEN_LOGGED_IN); \
    return; \
}

#define ALLOW_ONLY_LOGGED_IN \
if (!m_core.IsThereCurrUser()) { \
    nUI::nError::PrintMsg(nMsg::nNotAllow::WHEN_NOT_LOGGED_IN); \
    return; \
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
    m_running = false;
}

void App::Help() const
{
    nUI::PrintMsg(nMsg::HELP);
}

void App::Register()
{
    DONT_ALLOW_LOGGED_IN

    //Read a valid and unique username
    str username = nUI::ReadValidUniqueUsername(&m_core);

    //Read a valid password
    str password = nUI::ReadValidPassword();

    //Read a valid and unique email
    str email = nUI::ReadValidUniqueEmail(&m_core);

    //Add user to core
    m_core.AddUser(username, password, email);

    nUI::PrintMsg(nMsg::nSuccess::REGISTER);
}

void App::LogIn()
{
    DONT_ALLOW_LOGGED_IN

    //Read a username of an existing user
    str username = nUI::ReadExistingUsername(&m_core);

    //Read a matching password
    nUI::ReadMatchingPassword(&m_core, username);

    //Log in the user
    m_core.SetCurrUser(username);

    nUI::PrintMsg(nMsg::nSuccess::LOGIN);

    //Show user's notifications
    nUI::PrintMsg(m_core.GetCurrUserNotifs());
}

void App::LogOut()
{
    ALLOW_ONLY_LOGGED_IN

    //Log out the user
    m_core.LogOutCurrUser();

    nUI::PrintMsg(nMsg::nSuccess::LOGOUT);
}

void App::AddTrip()
{
    ALLOW_ONLY_LOGGED_IN

    //Read a destination
    str dest = nUI::ReadDest();
    //Read valid begin and end dates
    Date begin, end;
    nUI::ReadBeginEndDate(begin, end);
    //Read a valid grade
    int grade = nUI::ReadValidGrade();
    //Read a comment
    str comment = nUI::ReadComment();
    //Read valid photos
    std::vector<str> photos;
    nUI::ReadPhotos(photos);

    //Add the trip to current user's trips
    m_core.CurrUserAddTrip(dest, begin, end, grade, comment, photos);

    nUI::PrintMsg(nMsg::nSuccess::ADDTRIP);
}

void App::ListDests() const
{
    ALLOW_ONLY_LOGGED_IN

    //Get all destinations
    std::vector<str> dests = m_core.GetDests();

    //Print destinations
    nUI::PrintVec(dests, nMsg::nList::DESTS);
}

void App::CheckoutDest()
{
    ALLOW_ONLY_LOGGED_IN

    //Read a destination
    str dest = nUI::ReadValidInput(nMsg::nInput::DEST);

    //Get the grades of that destination
    const std::vector<UserGrade> usersGrades = m_core.GetUsersGrades(dest);

    //Print grades
    nUI::PrintUsersGrades(usersGrades);
}

void App::AddFriend()
{
    ALLOW_ONLY_LOGGED_IN

    //Read a username of an existing user
    str fr = nUI::ReadExistingUsername(&m_core);

    str currUser = m_core.GetCurrUser();

    if (fr == currUser)
        nUI::nError::PrintMsg(nMsg::nNotAllow::ADDFRIEND_SELF);
    else if (m_core.AreFr(currUser, fr))
        nUI::PrintMsg(nMsg::nNotAllow::ADDFRIEND_FR);
    else if (m_core.HasFrReqFrom(fr, currUser))
        nUI::nError::PrintMsg(nMsg::nNotAllow::ADDFRIEND_FRREQ);
    else if (m_core.HasFrReqFrom(currUser, fr))
    {
        //Confirm the friend request from the other user
        m_core.ConfirmFrReq(currUser, fr);
        nUI::PrintMsg(nMsg::nSuccess::FRREQ_CONFIRMED);
    }
    else
    {
        //Sends a friend request to the other user
        m_core.SendFrReq(currUser, fr);
        nUI::PrintMsg(nMsg::nSuccess::FRREQ_SENT);
    }
    
}

void App::RemoveFriend()
{
    ALLOW_ONLY_LOGGED_IN

    //Read a username of an existing user
    str fr = nUI::ReadExistingUsername(&m_core);

    str currUser = m_core.GetCurrUser();

    if (fr == currUser)
        nUI::nError::PrintMsg(nMsg::nNotAllow::RMFRIEND_SELF);
    else if (m_core.AreFr(currUser, fr))
    {
        //Remove the other user from friends
        m_core.RmFr(currUser, fr);
        nUI::PrintMsg(nMsg::nSuccess::RMFRIEND_FR);
    }
    else if (m_core.HasFrReqFrom(currUser, fr))
    {
        //Decline the friend request from the other user
        m_core.DeclineFrReq(currUser, fr);
        nUI::PrintMsg(nMsg::nSuccess::FRREQ_DECLINED);
    }
    else if (m_core.HasFrReqFrom(fr, currUser))
    {
        m_core.UnsendFrReq(currUser, fr);
        nUI::PrintMsg(nMsg::nSuccess::FRREQ_UNSENT);
    }
    else nUI::PrintMsg(nMsg::nNotAllow::RMFRIEND_NONFR);
}

void App::CheckoutFriend() const
{
    ALLOW_ONLY_LOGGED_IN

    //Read a username of an existing user
    str fr = nUI::ReadExistingUsername(&m_core);

    str currUser = m_core.GetCurrUser();

    //Don't allow checking out of a non-friend
    if (!m_core.AreFr(currUser, fr))
    {
        nUI::nError::PrintMsg(nMsg::nNotAllow::CHECKOUTFR_NONFR);
        return;
    }

    //Print friend's trips
    const std::vector<Trip>& trips = m_core.GetUserTrips(fr);
    nUI::PrintTrips(trips);
}