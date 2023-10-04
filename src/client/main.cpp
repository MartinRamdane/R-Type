/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "Login.hpp"
#include "Parser.hpp"
#include <thread>

int main()
{
    struct Login login = startgame();

    std::cout << "name: " << login.name << std::endl;
    std::cout << "port: " << login.port << std::endl;
    std::cout << "ip: " << login.ip << std::endl;
    try
    {
        Game game;
        game.connectToServer(login.ip, std::atoi(login.port.c_str()));
        game.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
