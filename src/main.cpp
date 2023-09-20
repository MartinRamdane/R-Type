#include <iostream>
#include "Player.hpp"
#include "server/UDPServer.hpp"
#include <asio.hpp>
#include "server/UDPClient.hpp"
#include <thread>
#include <chrono>
#include "server/ServerClass.hpp"

int main(int ac, char **av)
{
    if (ac == 1) {
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
        try {
            ServerClass server;
            while (1) {
                std::this_thread::sleep_for(std::chrono::milliseconds(2000)); //debug pour tester les 2 threads
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    } else {
        UDPClient client;
        client.connect_to("127.0.0.1", 4241);
        while (1) {
        std::string received_data = client.receive_data(); //TODO: foutre ça dans un thread non ??? Parce que c'est bloquant
        std::cout << "Received: " << received_data << std::endl;
        }
        return 0;
    }
}