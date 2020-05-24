#include "Core/Core.hpp"
#include "User/User.hpp"
#include "Constants/Constants.hpp"

int main()
{
    Core core(DATABASE_DIR + USERS_FILE);
    core.Run();

    return 0;
}