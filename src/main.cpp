#include <iostream>
#include "Player.hpp"
#include "server/UDPServer.hpp"
#include <asio.hpp>
#include "server/UDPClient.hpp"
#include <thread>
#include <chrono>
#include "server/Server.hpp"
#include "server/TCPClient.hpp"
#include "server/TCPServer.hpp"
#include "server/Instance.hpp"

int main(int ac, char **av)
{
    if (ac == 1)
    {
        ServerClass server;
    }
    else
    {
        boost::asio::io_service io_service;
        tcp::endpoint endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4244);
        TCPClient client(io_service, endpoint);
        io_service.run();

        // UDPClient client;
        // client.connect_to("127.0.0.1", 4211);
        // std::cout << "Client is launched" << std::endl;
        // while (1)
        // {
        //     std::string received_data = client.receive_data(); // TODO: foutre ça dans un thread non ??? Parce que c'est bloquant
        //     std::cout << "Received: " << received_data << std::endl;
        // }
        return 0;
    }
}