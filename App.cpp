#include "App.hpp"
#include "UI/UI.hpp"

#include <string>
typedef std::string str;

namespace nMsg
{
    const str WELCOME = "TODO";
}

App::App()
{
    //Load the core
    m_core.Load();
}

void App::Run()
{
    m_running = true;
    nUI::PrintMsg(nMsg::WELCOME);

    while (m_running)
    {
        str currUser = m_core.GetCurrUser();

        str command = nUI::ReadCommand(currUser + ": ");
        this->ExecuteCommand(command);
    }
}

void App::ExecuteCommand(const str& command)
{
    //TODO
}