/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game
*/

#pragma once
#include "../Engine.hpp"
#include "../IEntity.hpp"
#include "Projectile.hpp"
#include <iostream>
#include <vector>
#include "../StaticObject.hpp"

class Player;

class Game
{
public:
    enum Event
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        SHOOT,
        QUIT,
        UNKNOWN
    };
    Game(std::shared_ptr<Engine> &engine);
    ~Game();
    static Game *instance;

    void update(Event event);
    void createExplosion(int x, int y);

private:
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<EntityType<IEntity>> _playersGroups;
    std::shared_ptr<EntityType<IEntity>> _projectilesGroups;
    std::shared_ptr<EntityType<IEntity>> _staticObjectsGroups;
    std::vector<std::shared_ptr<Player>> _players;
    std::vector<std::shared_ptr<Projectile>> _projectiles;
    int _lastId = 0;
};
