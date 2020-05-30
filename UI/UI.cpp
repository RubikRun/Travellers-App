#include "UI.hpp"

#include <iostream>

str nUI::ReadCommand(const str& beginMsg, const str& endMsg)
{
    str command;

    nUI::PrintMsg(beginMsg, "", "");
    std::getline(std::cin, command);
    nUI::PrintMsg(endMsg, "", "");

    return command;
}

str nUI::ReadValidInput(const str& enterMsg,
    const std::function<bool(const str&)>& IsValid1, const str& invalidMsg1,
    const std::function<bool(const str&)>& IsValid2, const str& invalidMsg2)
{
    str input;

    bool valid1, valid2;
    do
    {
        nUI::PrintMsg(enterMsg, "", "");
        std::getline(std::cin, input);

        valid1 = IsValid1(input);
        if (!valid1)
        {
            nUI::nError::PrintMsg(invalidMsg1);
        }
        valid2 = IsValid2(input);
        if (!valid2)
        {
            nUI::nError::PrintMsg(invalidMsg2);
        }
    } while (!valid1 || !valid2);

    return input;
}

void nUI::PrintMsg(const str& msg, const str& begin, const str& end)
{
    std::cout << begin << msg << end;
}

void nUI::PrintVec(const std::vector<str>& vec, const str& beginMsg, const str& endMsg, bool lineNumbers)
{
    nUI::PrintMsg(beginMsg);

    for (int i = 0; i < vec.size(); i++)
    {
        if (lineNumbers)
        {
            std::cout << i + 1 << ". ";
        }
        std::cout << vec[i] << std::endl;
    }

    nUI::PrintMsg(endMsg);
}

void nUI::nError::PrintMsg(const str& msg)
{
    nUI::PrintMsg(msg, "Error: ");
}

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

str nUI::ReadExistingDest(const Core* core)
{
    return ReadValidInput(nMsg::nInput::DEST,
    [core](const str& d) { return core->DestExists(d); }, nMsg::nNotExist::DEST);
}

void nUI::ReadBeginEndDate(Date& begin, Date& end)
{
    str beginStr, endStr;

    //Reads a valid begin date
    beginStr = nUI::ReadValidInput(nMsg::nInput::BEGIN_DATE, nInputValidator::DateStr, nMsg::nInvalid::DATE);
    begin = Date::FromStr(beginStr);

    //Reads a valid end date that is after the begin date
    endStr = nUI::ReadValidInput(nMsg::nInput::END_DATE, nInputValidator::DateStr, nMsg::nInvalid::DATE,
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
        userGradeStrs[i] = usersGrades[i].username + " graded with " + std::to_string(usersGrades[i].grade);
    }

    //Print grades
    nUI::PrintVec(userGradeStrs, nMsg::nList::GRADES);
}

void nUI::PrintTrips(const std::vector<Trip>& trips)
{
    nUI::PrintMsg(nMsg::nList::TRIPS, "\n");
    for (int i = 0; i < trips.size(); i++)
    {
        str tripStr = trips[i].ToStr();
        nUI::PrintMsg(tripStr);
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
    int filenameEnd = -1;
    if (nString::EndsWith(s, nPhoto::JPEG_EXT))
    {
        filenameEnd = s.length() - nPhoto::JPEG_EXT.length();
    }
    else if (nString::EndsWith(s, nPhoto::PNG_EXT))
    {
        filenameEnd = s.length() - nPhoto::PNG_EXT.length();
    }
    else
    {
        return false;
    }

    for (int i = 0; i < filenameEnd; i++)
    {
        if (!std::isalpha(s[i]) && s[i] != '_')
        {
            return false;
        }
    }

    return true;
}

std::vector<str> nString::Split(const str& s, const char delimeter)
{
    std::vector<str> parts;

    int lastBegin = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == delimeter)
        {
            str currPart = s.substr(lastBegin, i - lastBegin);
            parts.push_back(currPart);
            lastBegin = i + 1;
        }
    }
    if (lastBegin < s.length())
    {
        str lastPart = s.substr(lastBegin);
        parts.push_back(lastPart);
    }

    return parts;
}

bool nString::StrIsInt(const str& s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!std::isdigit(s[i]) && 
            !(i == 0 && (s[i] == '+' || s[i] == '-')))
        {
            return false;
        }
    }

    return true;
}

bool nString::EndsWith(const str& s, const str& suffix)
{
    if (suffix.length() > s.length())
        return false;

    int j = s.length() - suffix.length();
    for (int i = 0; i < suffix.length(); i++)
    {
        if (suffix[i] != s[j])
        {
            return false;
        }
        j++;
    }

    return true;
}