#pragma once

#include "../Date/DateInterval.hpp"

#include <string>
#include <vector>

typedef std::string str;

class Trip
{
    str m_dest;
    DateInterval m_period;
    float m_rating;
    str m_comment;
    std::vector<str> m_photos;

    public:

        //Creates an empty trip
        Trip();

        //Creates a trip with the given data
        Trip(const str& dest, const DateInterval& period, float rating,
            const str& comment, const std::vector<str>& photos);
};