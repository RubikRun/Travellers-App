//An interface class for objects that can be printed to the user

#pragma once

#include <string>
typedef std::string str;

class Printable
{
  public:

    //Returns a user-friendly string representation of the object
    virtual str ToStr() const = 0;
};