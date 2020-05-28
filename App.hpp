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
};