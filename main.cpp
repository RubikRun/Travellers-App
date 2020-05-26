#include "Core/Core.hpp"
#include "Constants/Constants.hpp"

int main()
{
    Core core;

    core.Load(
        nDatabase::DIR + nDatabase::USERS + nDatabase::EXT,
        nDatabase::DIR + nDatabase::DESTS + nDatabase::EXT
    );

    core.Run();

    return 0;
}