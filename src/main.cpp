#include <iostream>
#include "Player.hpp"
#include "server/Socket.hpp"
int main()
{
    Player player;
    player.setXPos(5);
    std::cout << "player x pos: " << player.getXPos() << std::endl;
    Socket socket;
    socket.connect_to("127.0.0.1", 8080);
    return (0);
}