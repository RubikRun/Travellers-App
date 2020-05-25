#pragma once

#include <iostream>
#include <string>
typedef std::string str;

class Date
{
    int m_day, m_month, m_year;

    public:

        //Creates a default zero date
        Date();

        //Creates a date
        Date(int day, int month, int year);

        //Checks if the date is valid
        bool IsValid() const;

        //Comparing dates
        friend bool operator==(const Date&, const Date&);
        friend bool operator<(const Date&, const Date&);
        friend bool operator>(const Date&, const Date&);
        friend bool operator<=(const Date&, const Date&);
        friend bool operator>=(const Date&, const Date&);

        //Parse the date to string
        str ToStr() const;

        //Parse a string to a date
        static Date FromStr(const str&);

        //Checks if a string represents a date in the correct format
        static bool IsValidStr(const str&);

        //Reads a date from a stream
        friend std::istream& operator>>(std::istream&, Date&);

        //Writes a date to a stream
        friend std::ostream& operator<<(std::ostream&, const Date&);

    private:

        //Checks if this is a leap year
        static bool IsLeapYear(int year);

        //Calculates the number of days in the given month
        static int GetDaysInMonth(int month, int year);

        //Parses the date to int
        //The resulting number is literally the year, month and day concatenated
        int ParseToInt() const;
};