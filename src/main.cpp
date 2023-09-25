#include <iostream>
#include "Player.hpp"
#include "server/UDPServer.hpp"
#include <asio.hpp>
#include "server/UDPClient.hpp"
#include <thread>
#include <chrono>
#include "server/ServerClass.hpp"
#include "server/TCPClient.hpp"
#include "server/TCPServer.hpp"

int main(int ac, char **av)
{
    if (ac == 1)
    {
        // try {
        //     asio::io_service io_service;
        //     UDPServer server(io_service, 4241);
        //     std::thread serverThread([&io_service]() { //todo: implémenter ça proprement, voir avec @fgrimaepitech la threadpool & la gestion des mutex
        //         io_service.run(); //threadpool vrmt utile pour un seul thread ?
        //     });
        //     while (1) {
        //         std::this_thread::sleep_for(std::chrono::milliseconds(2000)); //debug pour tester les 2 threads
        //     }
        // } catch (const std::exception& e) {
        //     std::cerr << "Error: " << e.what() << std::endl;
        // }
        try
        {
            // boost::asio::io_context io_context;
            // TCPServer server(io_context, 4242);
            // io_context.run();
            ServerClass server;
            while (1)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // debug pour tester les 2 threads
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    else
    {
        boost::asio::io_service io_service;
        tcp::endpoint endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4242);
        TCPClient client(io_service, endpoint);
        io_service.run();
        return 0;
    }
}