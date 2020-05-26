#include "UserOutput.hpp"

#include <iostream>

void nUserOutput::nError::Log(const str& msg)
{
    std::cout << "Error: " << msg << std::endl;
}