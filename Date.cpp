#include "Date.hpp"
#include "Constants.hpp"

Date::Date()
    : m_year(0), m_month(1), m_day(1) {}

Date::Date(int year, int month, int day)
    : m_year(year), m_month(month), m_day(day) {}

bool Date::IsValid() const
{
    if (!IN_INTERVAL(m_month, MIN_MONTH, MAX_MONTH) || m_year < MIN_YEAR || m_day < MIN_DAY)
        return false;

    int daysInMonth = Date::GetDaysInMonth(m_month, m_year);
    return (m_day <= daysInMonth);
}

int Date::ParseToInt() const
{
    return m_year * 10000 + m_month * 100 + m_day;
}

bool Date::IsLeapYear(int year)
{
    if (year % 4)
        return false;
    else if (year % 100)
        return true;
    else if (year % 400)
        return false;
    else
        return true;
}

int Date::GetDaysInMonth(int month, int year)
{
    if (month == 2)
    {
        if (Date::IsLeapYear(year))
            return 29;
        return 28;
    }
    if ((month + (month >= 8)) % 2 == 0)
        return 30;
    return 31;
}

#define COMPARE_DATES_OPERATOR(operatorSign) \
bool operator operatorSign(const Date& date1, const Date& date2) \
{ \
    return (date1.ParseToInt() operatorSign date2.ParseToInt()); \
}

COMPARE_DATES_OPERATOR(==)
COMPARE_DATES_OPERATOR(<)
COMPARE_DATES_OPERATOR(>)
COMPARE_DATES_OPERATOR(<=)
COMPARE_DATES_OPERATOR(>=)