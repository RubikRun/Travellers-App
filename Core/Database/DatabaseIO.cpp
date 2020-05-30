#include "DatabaseIO.hpp"

#include <queue>

str nDatabaseIO::ReadStr(std::istream& db)
{
    std::queue<char> chars;

    char newChar;
    //Read chars one by one and push them to the queue
    while ((db >> std::noskipws >> newChar) && newChar != nDatabaseIO::DELIMETER)
    {
        chars.push(newChar);
    }
    //Create string from the queue
    str result = str(chars.size(), '\0');
    for (int i = 0; i < result.size(); i++)
    {
        result[i] = chars.front();
        chars.pop();
    }

    return result;
}

void nDatabaseIO::WriteStr(const str& s, std::ostream& db)
{
    db << s << nDatabaseIO::DELIMETER;
}

int nDatabaseIO::ReadInt(std::istream& db)
{
    str s = nDatabaseIO::ReadStr(db);
    int result = std::stoi(s);

    return result;
}

void nDatabaseIO::WriteInt(int n, std::ostream& db)
{
    str nStr = std::to_string(n);
    nDatabaseIO::WriteStr(nStr, db);
}

void nDatabaseIO::ReadObj(Serializable& obj, std::istream& db)
{
    obj.DeserializeFrom(db);
}

void nDatabaseIO::WriteObj(const Serializable& obj, std::ostream& db)
{
    obj.SerializeTo(db);
}