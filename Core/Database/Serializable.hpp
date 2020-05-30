//An interface class for objects that can be serialized and deserialized,
//so that we can read/write them from/to a database

#pragma once

#include <iostream>
#include <string>
typedef std::string str;

class Serializable
{
  public:

    //Serializes the object and writes it to a stream
    virtual void SerializeTo(std::ostream&) const = 0;

    //Deserializes the object by reading it from a stream
    virtual void DeserializeFrom(std::istream&) = 0;
};