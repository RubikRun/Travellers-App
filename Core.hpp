#pragma once

#include "User.hpp"

#include <string>
#include <vector>
#include <functional>

typedef std::string str;

class Core
{
    //All users registered in the app
    std::vector<User> m_users;
    //The name of the file where all registered users are stored
    str m_usersFile;

    //The user that is currently logged in (his index)
    int m_userIndex;

    public:

        //Creates an empty core for the app
        Core();

        //Loads the core from a database file with users
        Core(const str& usersFile);

        //Run the core. Start reading and executing commands
        void Run();

        //Reads a string until a valid string is entered
        static str ReadValid(std::function<bool(const str&)> IsValid, const str& enterMsg, const str& invalidMsg);

    private:

        //Executes a command.
        //Returns true if we should continue executing commands after that
        bool ExecuteCommand(const str& command);

        //Shows the help message
        static void Help();

        //Registers a new user
        void Register();

        //Logs in a user
        void LogIn();

        //Logs out the currently logged in user
        void LogOut();

        //Checks if a user with this username exists
        bool UserExists(const str& username) const;

        //Finds the user with this username, returns a pointer to it
        int FindUser(const str& username) const;
};