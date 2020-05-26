#pragma once

#include "../User/User.hpp"
#include "../Destination/Destination.hpp"

#include <vector>

//The core of the app.
//Contains all the needed data and executes commands
class Core
{
    //App's users
    std::vector<User> m_users;
    //App's destinations
    std::vector<Destination> m_dests;
    //The user currently logged in (their index)
    int m_userInd;
};