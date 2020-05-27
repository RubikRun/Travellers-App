#include "DatabaseIO.hpp"
#include "../Constants/Constants.hpp"

#include <queue>

void nDatabaseIO::ReadStr(str& s, std::istream& db)
{
    std::queue<char> chars;

    char newChar;
    //Read chars one by one and push them to the queue
    while ((db >> std::noskipws >> newChar) && newChar != nDatabase::DELIMETER)
    {
        chars.push(newChar);
    }
    //Create string from the queue
    s = str(chars.size(), 0);
    for (int i = 0; i < s.size(); i++)
    {
        s[i] = chars.front();
        chars.pop();
    }
}

void nDatabaseIO::WriteStr(const str& s, std::ostream& db)
{
    db << s << nDatabase::DELIMETER;
}

int nDatabaseIO::ReadInt(std::istream& db)
{
    //Read string from database
    str s;
    nDatabaseIO::ReadStr(s, db);
    //Parse it to int
    int result = std::stoi(s);

    return result;
}

void nDatabaseIO::WriteInt(int n, std::ostream& db)
{
    str nStr = std::to_string(n);
    nDatabaseIO::WriteStr(nStr, db);
}

void nDatabaseIO::Read(Serializable& obj, std::istream& db)
{
    //Read serialized string from database
    str serialized;
    nDatabaseIO::ReadStr(serialized, db);

    //Deserialize the string
    obj.Deserialize(serialized);
}

void nDatabaseIO::Write(const Serializable& obj, std::ostream& db)
{
    //Serializa the object
    str serialized = obj.Serialize();

    //Write it to database
    nDatabaseIO::WriteStr(serialized, db);
}