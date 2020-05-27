#pragma once

#include "../DatabaseIO/Serializable.hpp"
#include "../UserIO/Printable.hpp"

class Date : public Serializable, public Printable
{
    //An year, a month and a day
    int m_year, m_month, m_day;

    public:

        str Serialize() const;

        void Deserialize(const str&);

        str ToStr() const;
};