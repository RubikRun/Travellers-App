#pragma once

#include "User.hpp"

#include <string>
#include <vector>

class Core
{
    //All users registered in the app
    std::vector<User> m_users;

    //The user that is currently logged in
    User* m_user;

    public:

        //Creates an empty core for the app
        Core();

        //Loads the core from a database file with users
        Core(const std::string& usersFile);

        //Run the core. Start reading and executing commands
        void Run();

    private:

        //Executes a command.
        //Returns true if we should continue executing commands after that
        bool ExecuteCommand(const std::string& command);
};