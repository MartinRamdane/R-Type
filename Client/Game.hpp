/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.hpp
*/

#pragma once
#include <map>
#include <sstream>
#include "Entity.hpp"
#include "RessourceManager.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run(std::map<int, Entity> entities);
    void handleEvent();
    void update();
    void updateEntities(std::map<int, Entity> entities);

public:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Event _event;
    RessourceManager _ressourceManager;
    std::map<int, Entity> _entities;
};

std::map<int, Entity> parseMessage(std::string message, std::map<int, Entity> &entities, RessourceManager &ressourceManager);