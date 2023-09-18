#include <iostream>
#include "Player.hpp"
int main()
{
    Player player;
    player.setXPos(5);
    std::cout << "player x pos: " << player.getXPos() << std::endl;
    return (0);
}