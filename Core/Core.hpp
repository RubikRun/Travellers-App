#pragma once

#include "../User/User.hpp"
#include "../Destination/Destination.hpp"

#include <string>
#include <vector>
typedef std::string str;

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

    //Indicates whether the app is currently running
    bool m_running;

    public:

        //Creates an empty core
        Core();

        //Loads users and destinations from databases
        void Load(const str& usersDb, const str& destsDb);

        //Runs the app
        void Run();

    private:

        //Loads users from a database
        void LoadUsers(const str& usersDb);

        //Loads destinations from a database
        void LoadDests(const str& destsDb);

        //Executes a command
        void ExecuteCommand(const str& command);
};