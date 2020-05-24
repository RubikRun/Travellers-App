#pragma once

#include "../User/User.hpp"

#include <string>
#include <vector>
#include <functional>

typedef std::string str;

class Core
{
    //All users registered in the app
    std::vector<User> m_users;
    //The name of the file where all registered users will be stored
    str m_usersFile;

    //The user that is currently logged in (his index)
    int m_userIndex;

    public:

        //Creates an empty core for the app
        Core(const str& usersFile);

        //Loads the core from a database file with users
        void LoadCore(const str& usersFile);

        //Run the core. Start reading and executing commands
        void Run();


    private:

        //Reads a string until a valid and unique string is entered
        static str ReadValid(const std::function<bool(const str&)>& IsValid, const str& enterMsg, const str& invalidMsg,
            const std::function<bool(const str&)>& IsUnique = [](const str&){ return true; },
            const str& duplicateMsg = "");

        //Saves all users to the database file
        void SaveUsers() const;

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

        //Finds the user with this username, returns its index
        int FindUser(const str& username) const;

        //Finds the user with this email, returns its index
        int FindUserByEmail(const str& email) const;

        //Reads a username and makes sure it's valid and unique
        str ReadUsername();

        //Reads a password and makes sure it's valid
        str ReadPassword();

        //Reads an email and makes sure it's valid and unique
        str ReadEmail();

        //Creates a file and puts the given content in it
        static void CreateFile(const str& filename, const str& content);

    public:

        //Checks if a file with this name exists
        static bool FileExists(const str& filename);
};
