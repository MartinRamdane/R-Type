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
    // struct Login login = startgame();
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // // add connexion to server

    std::map<int, Entity> entities;
    parseMessage("ecreate 1 100 100 ../sprites/button.png 0 1\n", entities);
    parseMessage("pup 1 190 356", entities);

    // open window si la connexion est valide

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        std::map<int, Entity>::iterator it = entities.begin();
        while (it != entities.end())
        {
            window.draw(it->second.getSprite());
            it++;
        }
        window.display();
    }

    return 0;
}
