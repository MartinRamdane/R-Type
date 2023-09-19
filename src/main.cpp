#include <iostream>
#include "Player.hpp"
#include "server/Socket.hpp"
#include "server/UDPServer.hpp"
int main()
{
    Player player;
    player.setXPos(5);
    std::cout << "player x pos: " << player.getXPos() << std::endl;
    Socket socket;
    socket.connect_to("127.0.0.1", 8080);
    try
    {
        asio::io_context io_context;

        UDPServer server(io_context, 1234);
        // UDPClient client(io_context, "127.0.0.1", 1234);

        // client.Send("Hello, server!");

        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}