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
    // struct Login login = startgame();                         start login menu !!!!!
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::View view(sf::FloatRect(0, 0, 800, 600));


    // // add connexion to server

    RessourceManager ressourceManager;
    std::map<int, Entity> entities;
    parseMessage("ecreate 1 100 100 Spaceship1.png 0 1", entities, ressourceManager);
    parseMessage("pmove 1 190 356", entities, ressourceManager);
    // parseMessage("dead 1\n", entities, ressourceManager);

    // // open window si la connexion est valide

    // // sf::Clock clock;
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
            // it->second.animateSprite(1, 100, 100, clock);
            window.draw(it->second.getSprite());
            it++;
        }
        window.setView(view);
        window.display();
    }

    return 0;
}
