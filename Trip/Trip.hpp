#pragma once

#include "../DatabaseIO/Serializable.hpp"
#include "../UserIO/Printable.hpp"
#include "../Date/Date.hpp"

#include <string>
#include <vector>
typedef std::string str;

class Trip : public Serializable, public Printable
{
    //The destination of the trip (its index)
    int m_destInd;
    //The begin and end dates of the trip
    Date m_begin, m_end;
    //User's grade of the trip
    int grade;
    //User's comment about the trip
    str m_comment;
    //User's photos from the trip
    std::vector<str> m_photos;

    public:

        str Serialize() const;

        void Deserialize(const str&);

        str ToStr() const;
};