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
    std::map<int, Entity> _entities;
};