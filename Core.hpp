#pragma once

#include "User.hpp"

#include <string>
#include <vector>

typedef std::string str;

class Core
{
    //All users registered in the app
    std::vector<User> m_users;
    //The name of the file where all registered users are stored
    str m_usersFile;

    //The user that is currently logged in
    User* m_user;

    public:

        //Creates an empty core for the app
        Core();

        //Loads the core from a database file with users
        Core(const str& usersFile);

        //Run the core. Start reading and executing commands
        void Run();

    private:

        //Executes a command.
        //Returns true if we should continue executing commands after that
        bool ExecuteCommand(const str& command);

        //Shows the help message
        void Help();

        //Registers a new user
        void Register();
};