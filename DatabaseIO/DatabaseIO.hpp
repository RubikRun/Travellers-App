#pragma once

#include "Serializable.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
typedef std::string str;

#define DB_READ_VEC(db, vec, type) \
{ \
    int objCount = nDatabaseIO::ReadInt(db); \
    vec = std::vector<type>(objCount); \
    for (int i = 0; i < objCount; i++) \
    { nDatabaseIO::Read(vec[i], db); } \
}

#define DB_WRITE_VEC(db, vec, type) \
{ \
    nDatabaseIO::WriteInt(vec.size(), db); \
    for (int i = 0; i < vec.size(); i++) \
    { nDatabaseIO::Write(vec[i], db); } \
}

#define CHECK_FILE_EXISTS(filename, onexist, onmissing) \
{ \
    std::ifstream file(filename); \
    if (file.good()) { onexist; } \
    else { onmissing; } \
} \

#define OPEN_OFILE(file, filename, onerror) \
std::ofstream file(filename); \
if (!file.is_open()) { \
    nUserIO::nError::Log("Cannot open file: " + filename); \
    onerror; \
}

#define OPEN_IFILE(file, filename, onerror) \
std::ifstream file(filename); \
if (!file.is_open()) { \
    nUserIO::nError::Log("Cannot open file: " + filename); \
    onerror; \
}

#define CLOSE_FILE(file, filename, onerror) \
file.close(); \
if (!file.good()) { \
    nUserIO::nError::Log("Cannot close file: " + filename); \
    onerror; \
}

namespace nDatabaseIO
{
    //Reads a string from a database
    void ReadStr(str&, std::istream& db);
    //Writes a string to a database
    void WriteStr(const str&, std::ostream& db);

    //Reads an int from a database
    int ReadInt(std::istream& db);
    //Writes an int to a database
    void WriteInt(int, std::ostream& db);

    //Reads an object from a database
    void Read(Serializable& obj, std::istream& db);
    //Writes an object to a database
    void Write(const Serializable& obj, std::ostream& db);
}