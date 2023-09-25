/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "include.hpp"

int main()
{
    // struct Login login = startgame();

    // // add connexion to server

    RessourceManager ressourceManager;
    std::map<int, Entity> entities;
    parseMessage("ecreate 1 100 100 Spaceship1.png 0 1 1", entities, ressourceManager);
    // parseMessage("emove 1 190 356", entities, ressourceManager);
    // parseMessage("dead 1\n", entities, ressourceManager);

    // // open window si la connexion est valide

    Game game;
    game.run(entities);

    return 0;
}
