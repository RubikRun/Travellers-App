#include "Trip.hpp"
#include "../Constants/Constants.hpp"

Trip::Trip(){}

Trip::Trip(const str& dest, const Date& begin, const Date& end,
    float rating, const str& comment, const std::vector<str>& photos)
    : m_dest(dest), m_begin(begin), m_end(end), m_rating(rating),
        m_comment(comment), m_photos(photos) {}

std::istream& operator>>(std::istream& stream, Trip& trip)
{
    //Read trip's info
    std::getline(stream, trip.m_dest);
    stream >> trip.m_begin >> trip.m_end;
    READ_INT(stream, trip.m_rating)
    std::getline(stream, trip.m_comment);
    //Read the number of photos
    int photosCount;
    READ_INT(stream, photosCount);
    //Create photos
    trip.m_photos.clear();
    trip.m_photos = std::vector<str>(photosCount);
    //Read photos
    ITERATE_AND_DO(0, photosCount, std::getline(stream, trip.m_photos[i]))

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Trip& trip)
{
    //Write trip's info
    stream << trip.m_dest << SEPARATOR << trip.m_begin << SEPARATOR << trip.m_end
    << SEPARATOR << trip.m_rating << SEPARATOR << trip.m_comment << SEPARATOR;
    //Write the number of photos
    stream << trip.m_photos.size();
    //Write photos
    ITERATE_AND_DO(0, trip.m_photos.size(), stream << SEPARATOR << trip.m_photos[i])

    return stream;
}