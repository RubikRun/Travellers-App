#include "Date.hpp"
#include "../../Database/DatabaseIO.hpp"

Date::Date()
    : m_year(0), m_month(1), m_day(1) {}

Date::Date(int year, int month, int day)
    : m_year(year), m_month(month), m_day(day) {}

void Date::SerializeTo(std::ostream& stream) const
{
    nDatabaseIO::WriteInt(m_year, stream);
    nDatabaseIO::WriteInt(m_month, stream);
    nDatabaseIO::WriteInt(m_day, stream);
}

void Date::DeserializeFrom(std::istream& stream)
{
    m_year = nDatabaseIO::ReadInt(stream);
    m_month = nDatabaseIO::ReadInt(stream);
    m_day = nDatabaseIO::ReadInt(stream);
}

const char DATE_SEPARATOR ='.';

str Date::ToStr() const
{
    str yearStr = std::to_string(m_year);
    while (yearStr.length() < 4) yearStr = "0" + yearStr;
    str monthStr = std::to_string(m_month);
    while (monthStr.length() < 2) monthStr = "0" + monthStr;
    str dayStr = std::to_string(m_day);
    while (dayStr.length() < 2) dayStr = "0" + dayStr;

    str result = dayStr + DATE_SEPARATOR + monthStr + DATE_SEPARATOR + yearStr;

    return result;
}

Date Date::FromStr(const str& s)
{
    int year = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + (s[9] - '0');
    int month = (s[3] - '0') * 10 + (s[4] - '0');
    int day = (s[0] - '0') * 10 + (s[1] - '0');

    Date date(year, month, year);

    return date;
}

bool Date::IsStrDate(const str& s)
{
    if (s.length() != 10)
        return false;

    for (int i = 0; i < s.length(); i++)
    {
        if (i == 2 || i == 5)
        {
            if (s[i] != DATE_SEPARATOR)
                return false;
        }
        else
        {
            if (!std::isdigit(s[i]))
                return false;
        }
    }

    return true;
}

#define DEFINE_OPERATOR(sign) \
bool operator sign(const Date& date1, const Date& date2) \
{ return ( date1.ToInt() sign date2.ToInt() ); }

DEFINE_OPERATOR(==)
DEFINE_OPERATOR(<)
DEFINE_OPERATOR(<=)
DEFINE_OPERATOR(>)
DEFINE_OPERATOR(>=)

int Date::ToInt() const
{
    return m_year * 10000 + m_month * 100 + m_day;
}