#pragma once

#include "../DatabaseIO/Serializable.hpp"
#include "../UserIO/Printable.hpp"

class Date : public Serializable, public Printable
{
    //An year, a month and a day
    int m_year, m_month, m_day;

    public:

        //Parses a string to a date
        static Date FromStr(const str&);

        //Checks if a string represents a date
        static bool StrIsDate(const str&);

        //Checks if a date is before (or equal) another date
        friend bool operator<=(const Date&, const Date&);

        str Serialize() const;

        void Deserialize(const str&);

        str ToStr() const;
};