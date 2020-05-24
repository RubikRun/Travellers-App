#pragma once

class Date
{
    int m_year, m_month, m_day;

    public:

        //Creates a default zero date
        Date();

        //Creates a date
        Date(int year, int month, int day);

        //Checks if the date is valid
        bool IsValid() const;

        //Parses the date to int
        //The resulting number is literally the year, month and day concatenated
        int ParseToInt() const;

        //Comparing dates
        friend bool operator==(const Date& date1, const Date& date2);
        friend bool operator<(const Date& date1, const Date& date2);
        friend bool operator>(const Date& date1, const Date& date2);
        friend bool operator<=(const Date& date1, const Date& date2);
        friend bool operator>=(const Date& date1, const Date& date2);

    private:

        //Checks if this is a leap year
        static bool IsLeapYear(int year);

        //Calculates the number of days in the given month
        static int GetDaysInMonth(int month, int year);
};