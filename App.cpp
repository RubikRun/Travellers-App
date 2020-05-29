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
namespace nInputValidator
{
    bool Username(const str&);
    bool Password(const str&);
    bool Email(const str&);
    bool DateStr(const str&);
    bool GradeStr(const str&);
    bool PhotosCountStr(const str&);
    bool Photo(const str&);
}

//Reads valid begin and end dates
void ReadBeginEndDate(Date& begin, Date& end);

//Reads valid photos
void ReadPhotos(std::vector<str>& photos);

//Prints a list of grades
void PrintUsersGrades(const std::vector<UserGrade>& usersGrades);

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
    str username = nUI::ReadValidInput(nMsg::nInput::USERNAME, nInputValidator::Username, nMsg::nInvalid::USERNAME,
        [this](const str& u) { return !this->m_core.UsernameExists(u); }, nMsg::nDuplicate::USERNAME);

    //Read a valid password
    str password = nUI::ReadValidInput(nMsg::nInput::PASSWORD, nInputValidator::Password, nMsg::nInvalid::PASSWORD);

    //Read a valid and unique email
    str email = nUI::ReadValidInput(nMsg::nInput::EMAIL, nInputValidator::Email, nMsg::nInvalid::EMAIL,
        [this](const str& e) { return !this->m_core.EmailExists(e); }, nMsg::nDuplicate::EMAIL);

    //Add user to core
    m_core.AddUser(username, password, email);

    nUI::PrintMsg(nMsg::nSuccess::REGISTER);
}

void App::LogIn()
{
    DONT_ALLOW_LOGGED_IN

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
    ALLOW_ONLY_LOGGED_IN

    //Log out the user
    m_core.LogOutCurrUser();

    nUI::PrintMsg(nMsg::nSuccess::LOGOUT);
}

void App::AddTrip()
{
    ALLOW_ONLY_LOGGED_IN

    //Read a destination
    str dest = nUI::ReadValidInput(nMsg::nInput::DEST);
    //Read valid begin and end dates
    Date begin, end;
    ReadBeginEndDate(begin, end);
    //Read a valid grade
    str gradeStr = nUI::ReadValidInput(nMsg::nInput::GRADE, nInputValidator::GradeStr, nMsg::nInvalid::GRADE);
    int grade = std::stoi(gradeStr);
    //Read a comment
    str comment = nUI::ReadValidInput(nMsg::nInput::COMMENT);
    //Read valid photos
    std::vector<str> photos;
    ReadPhotos(photos);

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
    PrintUsersGrades(usersGrades);
}

void App::AddFriend()
{
    ALLOW_ONLY_LOGGED_IN

    //Read a username of an existing user
    str fr = nUI::ReadValidInput(nMsg::nInput::USERNAME,
        [this](const str& u) { return this->m_core.UsernameExists(u); }, nMsg::nNotExist::USERNAME);

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
    str fr = nUI::ReadValidInput(nMsg::nInput::USERNAME,
        [this](const str& u) { return this->m_core.UsernameExists(u); }, nMsg::nNotExist::USERNAME);

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
    //TODO
}