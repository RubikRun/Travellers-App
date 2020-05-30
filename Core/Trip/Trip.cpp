#include "Trip.hpp"

Trip::Trip(){}

Trip::Trip(const str& dest, const Date& begin, const Date& end,
    int grade, const str& comment, const std::vector<str>& photos)
        : m_dest(dest), m_begin(begin), m_end(end), m_grade(grade), 
        m_comment(comment), m_photos(photos) {}

void Trip::SerializeTo(std::ostream&) const
{
    
}