#include "Trip.hpp"

Trip::Trip(){}

Trip::Trip(const str& dest, const DateInterval& period, float rating,
    const str& comment, const std::vector<str>& photos)
    : m_dest(dest), m_period(period), m_rating(rating), m_comment(comment), m_photos(photos) {}