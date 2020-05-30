//A file containing all functionality needed to read/write from/to database

#pragma once

#include "Serializable.hpp"

#include <iostream>
#include <string>
typedef std::string str;

#define DB_READ_VEC(db, vec, type) \
{ \
    int objCount = nDatabaseIO::ReadInt(db); \
    vec = std::vector<type>(objCount); \
    for (int i = 0; i < objCount; i++) \
    { nDatabaseIO::ReadObj(vec[i], db); } \
}

#define DB_WRITE_VEC(db, vec, type) \
{ \
    nDatabaseIO::WriteInt(vec.size(), db); \
    for (int i = 0; i < vec.size(); i++) \
    { nDatabaseIO::WriteObj(vec[i], db); } \
}

namespace nDatabaseIO
{
    //Reads a string from a database
    str ReadStr(std::istream& db);
    //Writes a string to a database
    void WriteStr(const str&, std::ostream& db);

    //Reads an int from a database
    int ReadInt(std::istream& db);
    //Writes an int to a database
    void WriteInt(int, std::ostream& db);

    //Reads a serializable object from a database
    void ReadObj(Serializable&, std::istream& db);
    //Writes a serializable object to a database
    void WriteObj(const Serializable&, std::ostream& db);

    //Checks if a database with this name exists
    bool DbExists(const str& dbName);

    const char DELIMETER = '\n';
}