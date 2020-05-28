//An interface class for objects that can be serialized and deserialized,
//so that we can read/write them from/to a database

#pragma once

#include <string>
typedef std::string str;

class Serializable
{
  public:

    //Serializes the object to a string
    virtual str Serialize() const = 0;

    //Deserializes a string to an object
    virtual void Deserialize(str&) = 0;
};