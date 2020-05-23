#include "Core.hpp"
#include "User.hpp"
#include "Constants.hpp"

int main()
{
    Core core(USERS_DATABASE_FILE);
    core.Run();

    return 0;
}