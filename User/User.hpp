#pragma once

#include "../DatabaseIO/Serializable.hpp"
#include "../UserIO/Printable.hpp"
#include "../Trip/Trip.hpp"

#include <string>
#include <vector>
typedef std::string str;

class User : public Serializable, public Printable
{
    //User's info
    str m_username, m_password, m_email;
    //User's trips
    std::vector<Trip> m_trips;
    //User's friends (their indecies)
    std::vector<int> m_frsInd;
    //User's friend requests (senders' indecies)
    std::vector<int> m_frReqsInd;

    public:

        //Creates a
        User();

        //Returns user's username
        const str& GetUsername() const;

        str Serialize() const;

        void Deserialize(const str&);

        str ToStr() const;
};