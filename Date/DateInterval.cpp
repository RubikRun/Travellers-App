#include "DateInterval.hpp"

DateInterval::DateInterval(){}

DateInterval::DateInterval(const Date& first, const Date& last)
    : m_first(first), m_last(last) {}

bool DateInterval::IsValid()
{
    return (m_first <= m_last);
}