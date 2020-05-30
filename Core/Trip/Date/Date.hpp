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

    //Checks if the date is a valid calendar date
    bool IsValidCalendarDate() const;

    //Operators for comparing two dates
    friend bool operator==(const Date&, const Date&);
    friend bool operator<(const Date&, const Date&);
    friend bool operator<=(const Date&, const Date&);
    friend bool operator>(const Date&, const Date&);
    friend bool operator>=(const Date&, const Date&);

  private:

    //Creates an int representation of the date
    //by literally concatenating the year, month and year
    int ToInt() const;

    //Returns the number of days in the given month on the given year
    static int GetDaysInMonth(int month, int year);

    //Checks if the year is a leap year
    static bool IsLeapYear(int year);
};