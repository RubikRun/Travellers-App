#include "Trip.hpp"

Trip::Trip(){}

Trip::Trip(int destInd, const Date& begin, const Date& end,
    int grade, const str& comment, const std::vector<str>& photos)
    : m_destInd(destInd), m_begin(begin), m_end(end), m_grade(grade),
        m_comment(comment), m_photos(photos) {}

bool Trip::IsValidPhoto(const str& filename)
{
    //TODO
}

str Trip::Serialize() const
{
    //TODO
}

void Trip::Deserialize(const str&)
{
    //TODO
}

str Trip::ToStr() const
{
    //TODO
}