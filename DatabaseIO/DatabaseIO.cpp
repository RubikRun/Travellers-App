#include "DatabaseIO.hpp"
#include "../Constants/Constants.hpp"

#include <queue>
#include <string>
typedef std::string str;

void nDatabaseIO::Read(Serializable& obj, std::istream& stream)
{
    std::queue<char> chars;

    char newChar;
    //Read chars one by one and push them to the queue
    while ((stream >> std::noskipws >> newChar) && newChar != nDatabase::DELIMETER)
    {
        chars.push(newChar);
    }
    //Create a string from the queue
    str serialized(chars.size(), 0);
    for (int i = 0; i < serialized.size(); i++)
    {
        serialized[i] = chars.front();
        chars.pop();
    }

    //Deserialize the string
    obj.Deserialize(serialized);
}

void nDatabaseIO::Write(const Serializable& obj, std::ostream& stream)
{
    //Serializa the object
    str serialized = obj.Serialize();

    //Write it to stream
    stream << serialized << nDatabase::DELIMETER;
}