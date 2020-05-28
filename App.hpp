//The app itself.
//We can run it from here.
//It should read and execute user's commands.

#pragma once

#include "Core/Core.hpp"

class App
{
    //The app's core, used to store data and deal with it
    Core m_core;

    //Indicates if the app is currently running
    bool m_running;

  public:

    //Loads the core of the app
    App();
    
    //Runs the app
    void Run();

  private:

    //Executes the given command
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

    //Sends/accepts a friend request
    void AddFriend();

    //Removes a friend or declines a friend request
    void RemoveFriend();

    //Lists the trips of a friend
    void CheckoutFriend() const;
};