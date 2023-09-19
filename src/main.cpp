#include <iostream>
#include "Player.hpp"
#include "server/Socket.hpp"
#include "server/UDPServer.hpp"
#include <asio.hpp>
#include "server/UDPClient.hpp"
int main(int ac, char **av)
{
    if (ac == 1) {
        asio::io_context io_context;
        Player player;
        player.setXPos(5);
        std::cout << "player x pos: " << player.getXPos() << std::endl;
        Socket socket(io_context);
        socket.Bind(4545);
        while (1) {
            if (socket.receive_data_blocking() > 0) {
                socket.send_data("Salut ça va ?");
            }
        }
        return (0);
    } else {
        UDPClient client;
        client.send_data("Salut ça va ?", "127.0.0.1", 4545);
        std::string received_data = client.receive_data();
        std::cout << "Received: " << received_data << std::endl;
        return 0;
    }
}