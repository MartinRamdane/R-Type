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
    // if (ac == 1)
    // {
    //     try
    //     {
    //         Server server;
    //         while (1)
    //         {
    //             std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // debug pour tester les 2 threads
    //         }
    //     }
    //     catch (const std::exception &e)
    //     {
    //         std::cerr << "Error: " << e.what() << std::endl;
    //     }
    // }
    // else
    // {
    //     boost::asio::io_service io_service;
    //     tcp::endpoint endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4242);
    //     TCPClient client(io_service, endpoint);
    //     io_service.run();
    //     return 0;
    // }
    if (ac == 1)
    {
        try
        {
            Instance instance(1);
            while (1)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // debug pour tester les 2 threads
                std::cout << "nb players: " << instance.getNbPlayers() << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    else
    {
        UDPClient client;
        client.connect_to("127.0.0.1", 4211);
        std::cout << "Client is launched" << std::endl;
        while (1)
        {
            std::string received_data = client.receive_data(); // TODO: foutre ça dans un thread non ??? Parce que c'est bloquant
            std::cout << "Received: " << received_data << std::endl;
        }
        return 0;
    }
}