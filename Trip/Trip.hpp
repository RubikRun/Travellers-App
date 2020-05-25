#pragma once

#include "../Date/Date.hpp"

#include <iostream>
#include <string>
#include <vector>
typedef std::string str;

class Trip
{
    str m_dest;
    Date m_begin, m_end;
    float m_rating;
    str m_comment;
    std::vector<str> m_photos;

    public:

        //Creates an empty trip
        Trip();

        //Creates a trip with the given data
        Trip(const str& dest, const Date& begin, const Date& end, float rating,
            const str& comment, const std::vector<str>& photos);

        //Reads the trip from a stream
        friend std::istream& operator>>(std::istream& stream, Trip& trip);

        //Writes the trip to a stream
        friend std::ostream& operator<<(std::ostream& stream, const Trip& trip);
};