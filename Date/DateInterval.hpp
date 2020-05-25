#pragma once

#include "Date.hpp"

#include <iostream>

class DateInterval
{
    Date m_first, m_last;

    public:

        //Creates a default date interval
        DateInterval();

        //Creates a date interval for the given period
        DateInterval(const Date& first, const Date& last);

        //Checks if the date interval is valid
        bool IsValid();

        //Reads a date interval from a stream
        friend std::istream& operator>>(std::istream& stream, DateInterval& dateInterval);

        //Writes a date interval to a stream
        friend std::ostream& operator<<(std::ostream& stream, const DateInterval& dateInterval);
};