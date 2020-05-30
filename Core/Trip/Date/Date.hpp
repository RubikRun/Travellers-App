//Date is a class representing a calendar date

#pragma once

#include "../../Database/Serializable.hpp"
#include "../../../UI/Printable.hpp"

#include <string>
typedef std::string str;

class Date : public Serializable, public Printable
{
    //The year, month and day
    int m_year, m_month, m_day;

  public:

    //Creates a default date
    Date();

    //Creates a date with the given year, month and day
    Date(int year, int month, int day);

    //Operators for comparing two dates
    friend bool operator==(const Date&, const Date&);
    friend bool operator<(const Date&, const Date&);
    friend bool operator<=(const Date&, const Date&);
    friend bool operator>(const Date&, const Date&);
    friend bool operator>=(const Date&, const Date&);

    //Serializes the date
    void SerializeTo(std::ostream&) const;

    //Deserializes the date
    void DeserializeFrom(std::istream&);

    //Converts the date to a string
    str ToStr() const;

    //Converts a string to a date
    static Date FromStr(const str&);

    //Checks if a string represents a date (can be converted to a date)
    static bool IsStrDate(const str&);
};