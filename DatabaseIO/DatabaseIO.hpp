#include "../Serializable/Serializable.hpp"

#include <iostream>

namespace nDatabaseIO
{
    //Reads an object from a database
    void Read(Serializable& obj, std::istream& db);
    //Writes an object to a database
    void Write(const Serializable& obj, std::ostream& db);
}