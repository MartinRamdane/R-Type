/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** main.cpp
*/

#include "include.hpp"
// #include "Entity.hpp"


int main()
{
    struct Login login = startgame();
    // sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    // // add connexion to server

    std::map<int, Entity> entities;
    // parseMessage("pup n X Y", entities);

    // open window si la connexion est valide
    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //         {
    //             window.close();
    //         }
    //     }

    //     window.clear();
    //     window.display();
    // }

    return 0;
}
