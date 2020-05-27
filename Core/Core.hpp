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

        //Saves users to database
        void SaveUsers(const str& usersDb);

        //Loads destinations from a database
        void LoadDests(const str& destsDb);

        //Saves destinations to database
        void SaveDests(const str& destsDb);

        //Executes a command
        void ExecuteCommand(const str& command);

        //Exits the app
        void Exit();

        //Brings up the help message
        void Help() const;

        //Registers a new user
        void Register();

        //Logs in a user
        void LogIn();

        //Logs out the user
        void LogOut();

        //Adds a new trip to user's trips
        void AddTrip();

        //Lists all the destinations
        void ListDests() const;

        //Lists the grades of a destination
        void CheckoutDest();

        //Sends/confirms a friend request
        void AddFriend();

        //Removes a friend/Declines a friend request
        void RemoveFriend();

        //Lists the trips of a friend
        void CheckoutFriend() const;

        //Finds the user with the given username (returns their index)
        int FindUser(const str& username) const;

        //Finds the user with the given email (returns their index)
        int FindUserByEmail(const str& email) const;

        //Finds/Creates the destination with the given name,
        //updates its grades, and returns its index
        int UpdateDests(const str& destName, int userInd, int grade);
};