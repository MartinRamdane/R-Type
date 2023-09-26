#include <iostream>
#include "GameEngine/Core.hpp"
#include "GameEngine/r-type/Player.hpp"
#include "GameEngine/r-type/Enemy.hpp"
#include "GameEngine/r-type/Projectile.hpp"

int main()
{
    Core core;
    core.mainLoop("test");
    return 0;
}
