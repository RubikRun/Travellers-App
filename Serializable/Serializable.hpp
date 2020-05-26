#pragma once

#include <string>
typedef std::string str;

class Serializable
{
    public:

        //Serializes the object to a string
        virtual str Serialize() const = 0;

        //Deserializes the object from a string
        virtual void Deserialize(const str&) = 0;
};