#pragma once

#include "Date.hpp"

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
};