#include "DateInterval.hpp"
#include "../Constants/Constants.hpp"

DateInterval::DateInterval(){}

DateInterval::DateInterval(const Date& first, const Date& last)
    : m_first(first), m_last(last) {}

bool DateInterval::IsValid()
{
    return (m_first <= m_last);
}

std::istream& operator>>(std::istream& stream, DateInterval& dateInterval)
{
    stream >> dateInterval.m_first >> dateInterval.m_last;

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const DateInterval& dateInterval)
{
    stream <<
    dateInterval.m_first << SEPARATOR <<
    dateInterval.m_last;

    return stream;
}