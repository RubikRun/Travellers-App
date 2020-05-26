#pragma once

#include "../UserIO/UserOutput.hpp"

#include <iostream>
#include <fstream>

#define CHECK_FILE_EXISTS(filename, onexist, onmissing) \
{ \
    std::ifstream file(filename); \
    if (file.good()) { onexist; } \
    else { onmissing; } \
} \

#define OPEN_OFILE(file, filename, onerror) \
std::ofstream file(filename); \
if (!file.is_open()) { \
    nUserOutput::nError::Log("Cannot open file: " + filename); \
    onerror; \
}

#define OPEN_IFILE(file, filename, onerror) \
std::ifstream file(filename); \
if (!file.is_open()) { \
    nUserOutput::nError::Log("Cannot open file: " + filename); \
    onerror; \
}

#define CLOSE_FILE(file, filename, onerror) \
file.close(); \
if (!file.good()) { \
    nUserOutput::nError::Log("Cannot close file: " + filename); \
    onerror; \
}
