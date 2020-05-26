#pragma once

#include "../Trip/Trip.hpp"

#include <string>
#include <vector>
typedef std::string str;

class User
{
    //User's info
    str m_username, m_password, m_email;
    //User's trips
    std::vector<Trip> m_trips;
    //User's friends (their indecies)
    std::vector<int> m_frsInd;
    //User's friend requests (senders' indecies)
    std::vector<int> m_frReqsInd;
};