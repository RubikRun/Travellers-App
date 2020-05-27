#pragma once

#include "../DatabaseIO/Serializable.hpp"
#include "../UserIO/Printable.hpp"
#include "GradeEntry.hpp"

#include <string>
#include <vector>
typedef std::string str;

class Destination : public Serializable, public Printable
{
    //The name of the destination
    str m_name;
    //The grades recieved by users
    std::vector<GradeEntry> m_grades;

    public:

        str Serialize() const;

        void Deserialize(const str&);

        str ToStr() const;
};