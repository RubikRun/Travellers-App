//Trip is a class representing a user's trip.
//It contains all the data about the trip,
//and the functionality needed to manage that data

#pragma once

#include "Date/Date.hpp"
#include "../../Database/Serializable.hpp"
#include "../../../UI/Printable.hpp"

#include <vector>
#include <string>
typedef std::string str;

class Trip : public Serializable, public Printable
{
    //The destination of the trip
    str m_dest;

    //The begin and end date of the trip
    Date m_begin, m_end;

    //The grade of the trip
    int m_grade;

    //User's comment about the trip
    str m_comment;

    //User's photos from the trip (filenames)
    std::vector<str> m_photos;

  public:

    //Creates a default trip
    Trip();  

    //Creates a trip with the given info
    Trip(const str& dest, const Date& begin, const Date& end,
        int grade, const str& comment, const std::vector<str>& photos);

    //Serializes the trip
    str Serialize() const;

    //Deserializes the trip
    void Deserialize(const str&);

    //Prints the trip to the user
    void Print() const;
};