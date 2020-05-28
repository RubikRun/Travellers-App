//An interface class for objects that can be printed to the user

#pragma once

class Printable
{
  public:

    //Prints the object to the user
    virtual void Print() const = 0;
};