#include "Core/Core.hpp"
#include "User/User.hpp"
#include "Constants/Constants.hpp"

int main()
{
    Core core(USERS_DB);

    if (Core::FileExists(USERS_DB))
    {
        core.LoadCore(USERS_DB);
    }

    core.Run();

    return 0;
}