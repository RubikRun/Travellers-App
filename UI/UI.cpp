#include "UI.hpp"

str nUI::ReadValidUniqueUsername(const Core* core)
{
    return ReadValidInput(nMsg::nInput::USERNAME, nInputValidator::Username, nMsg::nInvalid::USERNAME,
        [core](const str& u) { return !core->UsernameExists(u); }, nMsg::nDuplicate::USERNAME);
}

str nUI::ReadValidPassword()
{
    return ReadValidInput(nMsg::nInput::PASSWORD, nInputValidator::Password, nMsg::nInvalid::PASSWORD);
}

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

bool nInputValidator::Username(const str& s)
{
    return (s.length() >= nUsername::MIN_LEN && s.length() <= nUsername::MAX_LEN
        && s.find(' ') == str::npos);
}

bool nInputValidator::Password(const str& s)
{
    if (s.length() < nPassword::MIN_LEN || s.length() > nPassword::MAX_LEN)
        return false;

    bool letter = false, digit = false;
    for (int i = 0; i < s.length(); i++)
    {
        if (std::isalpha(s[i])) letter = true;
        if (std::isdigit(s[i])) digit = true;
    }

    return (letter && digit);
}

bool nInputValidator::Email(const str& s)
{
    if (s.length() < nEmail::MIN_LEN || s.length() > nEmail::MAX_LEN)
        return false;

    int iAt = s.find(nEmail::AT);
    int iDot = s.rfind(nEmail::DOT);

    return (iAt >= nEmail::AT_DIFF && (iDot - iAt) >= nEmail::AT_DOT_DIFF
        && (s.length() - 1 - iDot) >= nEmail::DOT_DIFF);
}

bool nInputValidator::DateStr(const str& s)
{
    return Date::IsStrDate(s);
}

bool nInputValidator::GradeStr(const str& s)
{
    if (!nString::StrIsInt(s)) return false;

    int grade = std::stoi(s);
    return (grade >= nGrade::MIN && grade <= nGrade::MAX);
}

bool nInputValidator::Photo(const str& s)
{
    if (!nString::EndsWith(s, nPhoto::JPEG_EXT)
        || !nString::EndsWith(s, nPhoto::PNG_EXT))
            return false;

    for (int i = 0; i < s.length(); i++)
    {
        if (!std::isalpha(s[i]))
        {
            return false;
        }
    }

    return true;
}