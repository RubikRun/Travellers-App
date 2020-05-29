#include "UI.hpp"

//Reads a valid and unique username
str nUI::ReadValidUniqueUsername(const Core* core)
{
    return ReadValidInput(nMsg::nInput::USERNAME, nInputValidator::Username, nMsg::nInvalid::USERNAME,
        [core](const str& u) { return !core->UsernameExists(u); }, nMsg::nDuplicate::USERNAME);
}

//Reads a valid password
str nUI::ReadValidPassword()
{
    return ReadValidInput(nMsg::nInput::PASSWORD, nInputValidator::Password, nMsg::nInvalid::PASSWORD);
}

//Reads a valid and unique email
str nUI::ReadValidUniqueEmail(const Core* core)
{
    return ReadValidInput(nMsg::nInput::EMAIL, nInputValidator::Email, nMsg::nInvalid::EMAIL,
        [core](const str& e) { return !core->EmailExists(e); }, nMsg::nDuplicate::EMAIL);
}

str nUI::ReadExistingUsername(const Core* core)
{
    return ReadValidInput(nMsg::nInput::USERNAME,
        [core](const str& u) { return core->UsernameExists(u); }, nMsg::nNotExist::USERNAME);
}

str nUI::ReadMatchingPassword(const Core* core, const str& username)
{
    return ReadValidInput(nMsg::nInput::PASSWORD,
        [core, &username](const str& p) { return core->UserPasswordMatch(username, p); },
        nMsg::nNotAllow::PASSWORD_NOT_MATCHING);
}

str nUI::ReadDest()
{
    return ReadValidInput(nMsg::nInput::DEST);
}

void nUI::ReadBeginEndDate(Date& begin, Date& end)
{
    str beginStr, endStr;

    //Reads a valid begin date
    nUI::ReadValidInput(nMsg::nInput::BEGIN_DATE, nInputValidator::DateStr, nMsg::nInvalid::DATE);
    begin = Date::FromStr(beginStr);

    //Reads a valid end date that is after the begin date
    nUI::ReadValidInput(nMsg::nInput::END_DATE, nInputValidator::DateStr, nMsg::nInvalid::DATE,
        [&begin](const str& s) { return begin <= Date::FromStr(s); }, nMsg::nNotAllow::END_BEFORE_BEGIN_DATE);
    end = Date::FromStr(endStr);
}

int nUI::ReadValidGrade()
{
    str gradeStr = ReadValidInput(nMsg::nInput::GRADE, nInputValidator::GradeStr, nMsg::nInvalid::GRADE);
    return std::stoi(gradeStr);
}

str nUI::ReadComment()
{
    return ReadValidInput(nMsg::nInput::COMMENT);
}

void nUI::ReadPhotos(std::vector<str>& photos)
{
    //Read valid photos in a single string
    str photosStr = nUI::ReadValidInput(nMsg::nInput::PHOTOS,
        [](const str& s) {
            std::vector<str> photos = nString::Split(s);
            for (int i = 0; i < photos.size(); i++)
                if (!nInputValidator::Photo(photos[i]))
                    return false;
            return true;
        }, nMsg::nInvalid::PHOTOS);

    //Split photos
    photos = nString::Split(photosStr);
}

void nUI::PrintUsersGrades(const std::vector<UserGrade>& usersGrades)
{
    //Convert grades to strings
    std::vector<str> userGradeStrs(usersGrades.size());
    for (int i = 0; i < usersGrades.size(); i++)
    {
        userGradeStrs[i] = usersGrades[i].username + ": " + std::to_string(usersGrades[i].grade);
    }

    //Print grades
    nUI::PrintVec(userGradeStrs, nMsg::nList::GRADES);
}

void nUI::PrintTrips(const std::vector<Trip>& trips)
{
    nUI::PrintMsg(nMsg::nList::TRIPS);
    for (int i = 0; i < trips.size(); i++)
    {
        trips[i].Print();
    }
}

bool nInputValidator::Username(const str&)
{
    //TODO
}

bool nInputValidator::Password(const str&)
{
    //TODO
}

bool nInputValidator::Email(const str&)
{
    //TODO
}

bool nInputValidator::DateStr(const str&)
{
    //TODO
}

bool nInputValidator::GradeStr(const str&)
{
    //TODO
}

bool nInputValidator::PhotosCountStr(const str&)
{
    //TODO
}

bool nInputValidator::Photo(const str&)
{
    //TODO
}