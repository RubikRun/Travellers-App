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
    nUserIO::Log(nMsg::WELCOME);

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
    else nUserIO::Log(nMsg::nInvalid::COMMAND);
}

void Core::Exit()
{
    m_running = false;
}

void Core::Help() const
{
    nUserIO::Log(nMsg::HELP);
}

void Core::Register()
{
    if (m_userInd != nUser::NULL_IND)
    {
        nUserIO::nError::Log(nMsg::nNotAllow::REGISTER_LOGGED);
        return;
    }

    str username, password, email;

    //Read valid username, password and email
    nUserIO::ReadValid(username, User::UsernameIsValid,
        nMsg::nEnter::USERNAME, nMsg::nInvalid::USERNAME);
    nUserIO::ReadValid(password, User::PasswordIsValid,
        nMsg::nEnter::PASSWORD, nMsg::nInvalid::PASSWORD);
    nUserIO::ReadValid(email, User::EmailIsValid,
        nMsg::nEnter::EMAIL, nMsg::nInvalid::EMAIL);

    //Add a new user with that info
    m_users.emplace_back(username, password, email);

    nUserIO::Log(nMsg::nSuccess::REGISTER);
}

void Core::LogIn()
{
    if (m_userInd != nUser::NULL_IND)
    {
        nUserIO::nError::Log(nMsg::nNotAllow::LOGIN_LOGGED);
        return;
    }

    str username, password;

    //Read username of an existing user
    nUserIO::ReadValid(username,
        [this](const str& s) {
            return (this->FindUser(s) != nUser::NULL_IND);
        },
        nMsg::nEnter::USERNAME,
        nMsg::nNotExist::USERNAME
    );
    //Find user
    int userInd = this->FindUser(username);
    User* user = &m_users[userInd];

    //Read the correct password
    nUserIO::ReadValid(password,
        [user](const str& s) {
            return user->PasswordsMatch(s);
        },
        nMsg::nEnter::PASSWORD,
        nMsg::nNotAllow::PASSWORD
    );

    //Log in the user
    m_userInd = userInd;

    nUserIO::Log(nMsg::nSuccess::LOGIN);
}

void Core::LogOut()
{
    if (m_userInd == nUser::NULL_IND)
    {
        nUserIO::Log(nMsg::nNotAllow::LOGOUT_NONLOGGED);
        return;
    }

    //Log out the user
    m_userInd = nUser::NULL_IND;

    nUserIO::Log(nMsg::nSuccess::LOGOUT);
}

//Reads info about a trip from the user
void ReadTripInfo(str& dest, Date& begin, Date& end, 
    int& grade, str& comment, std::vector<str>& photos);

void Core::AddTrip()
{
    if (m_userInd == nUser::NULL_IND)
    {
        nUserIO::Log(nMsg::nNotAllow::ADDTRIP_NONLOGGED);
        return;
    }

    str destName, comment;
    Date begin, end;
    int grade;
    std::vector<str> photos;

    //Read all info about trip from user
    ReadTripInfo(destName, begin, end, grade, comment, photos);

    //Find the destination and update it
    int destInd = this->UpdateDests(destName, m_userInd, grade);

    //Create a trip with that info and add it to user's trips
    Trip trip(destInd, begin, end, grade, comment, photos);
    m_users[m_userInd].AddTrip(trip);

    nUserIO::Log(nMsg::nSuccess::ADDTRIP);
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

int Core::FindUser(const str& username) const
{
    //TODO
}

int Core::FindUserByEmail(const str& email) const
{
    //TODO
}

int Core::UpdateDests(const str& destName, int userInd, int grade)
{
    //TODO
}

//Reading each part of a trip's info separately
void ReadTripDest(str& dest);
void ReadTripBeginEnd(Date& begin, Date& end);
void ReadTripGrade(int& grade);
void ReadTripComment(str& comment);
void ReadTripPhotos(std::vector<str>& photos);

void ReadTripInfo(str& dest, Date& begin, Date& end, 
    int& grade, str& comment, std::vector<str>& photos)
{
    ReadTripDest(dest);

    ReadTripBeginEnd(begin, end);

    ReadTripGrade(grade);

    ReadTripComment(comment);

    ReadTripPhotos(photos);
}

void ReadTripDest(str& dest)
{
    nUserIO::ReadValid(dest, [](const str&){return true;}, nMsg::nEnter::DEST, "");
}

void ReadTripBeginEnd(Date& begin, Date& end)
{
    str beginStr, endStr;

    nUserIO::ReadValid(beginStr,
        [](const str& s) { return Date::StrIsDate(s); },
        nMsg::nEnter::BEGIN, nMsg::nInvalid::DATE);
    begin = Date::FromStr(beginStr);

    nUserIO::ReadValid(endStr,
        [begin](const str& s) {
            return (Date::StrIsDate(s) && begin <= Date::FromStr(s));
        },
        nMsg::nEnter::END, nMsg::nInvalid::END_DATE);
    end = Date::FromStr(endStr);
}

void ReadTripGrade(int& grade)
{
    str gradeStr;

    nUserIO::ReadValid(gradeStr,
        [](const str& s) {
            if (!nUserIO::IsInt(s)) return false;
            int grade = std::stoi(s);
            return (grade >= nGrade::MIN && grade <= nGrade::MAX);
        },
        nMsg::nEnter::GRADE, nMsg::nInvalid::GRADE);
    grade = std::stoi(gradeStr);
}

void ReadTripComment(str& comment)
{
    nUserIO::ReadValid(comment, [](const str&){return true;}, nMsg::nEnter::COMMENT, "");
}

void ReadTripPhotos(std::vector<str>& photos)
{
    str photosCountStr;

    nUserIO::ReadValid(photosCountStr,
        [](const str& s) { return (nUserIO::IsInt(s) && std::stoi(s) >= 0); },
        nMsg::nEnter::PHOTOS_COUNT, nMsg::nInvalid::PHOTOS_COUNT);
    int photosCount = std::stoi(photosCountStr);

    photos = std::vector<str>(photosCount);
    for (int i = 0; i < photosCount; i++)
    {
        str enterMsg = "Enter photo #" + std::to_string(i + 1) + ": ";
        nUserIO::ReadValid(photos[i], Trip::IsValidPhoto, enterMsg, nMsg::nInvalid::PHOTO);
    }
}