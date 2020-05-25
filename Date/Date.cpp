#include "Date.hpp"
#include "../Constants/Constants.hpp"

Date::Date()
    : m_day(1), m_month(1), m_year(0) {}

Date::Date(int day, int month, int year)
    : m_day(day), m_month(month), m_year(year) {}

bool Date::IsValid() const
{
    if (!IN_INTERVAL(m_month, MIN_MONTH, MAX_MONTH) || m_year < MIN_YEAR || m_day < MIN_DAY)
        return false;

    int daysInMonth = Date::GetDaysInMonth(m_month, m_year);
    return (m_day <= daysInMonth);
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

int Date::ParseToInt() const
{
    return m_year * 10000 + m_month * 100 + m_day;
}

#define COMPARE_DATES_OPERATOR(sign) \
bool operator sign(const Date& date1, const Date& date2) \
{ \
    return (date1.ParseToInt() sign date2.ParseToInt()); \
}

COMPARE_DATES_OPERATOR(==)
COMPARE_DATES_OPERATOR(<)
COMPARE_DATES_OPERATOR(>)
COMPARE_DATES_OPERATOR(<=)
COMPARE_DATES_OPERATOR(>=)

str Date::ToStr() const
{
    str dayStr = std::to_string(m_day);
    dayStr = str(2 - dayStr.length(), '0') + dayStr;

    str monthStr = std::to_string(m_month);
    monthStr = str(2 - monthStr.length(), '0') + monthStr;

    str yearStr = std::to_string(m_year);
    yearStr = str(4 - yearStr.length(), '0') + yearStr;

    return dayStr + DATE_SEPARATOR
        + monthStr + DATE_SEPARATOR 
        + yearStr;
}

Date Date::FromStr(const str& s)
{
    Date date;
    #define n(i) (s[i] - '0')
    date.m_day = n(0) * 10 + n(1);
    date.m_month = n(3) * 10 + n(4);
    date.m_year = n(6) * 1000 + n(7) * 100 + n(8) * 10 + n(9);

    return date;
}

bool Date::IsValidStr(const str& s)
{
    if (s.length() != DATE_FORMAT.length())
        return false;

    ITERATE_AND_FIND(0, s.length(),
        std::isdigit(s[i]) == (DATE_FORMAT[i] != DATE_SEPARATOR),
        return false, return true)
}

std::istream& operator>>(std::istream& stream, Date& date)
{
    str s;
    std::getline(stream, s);

    date = Date::FromStr(s);

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Date& date)
{
    stream << date.ToStr();

    return stream;
}