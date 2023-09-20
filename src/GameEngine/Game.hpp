/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game
*/

#pragma once
#include "Engine.hpp"
#include "IEntity.hpp"
#include "r-type/Player.hpp"
#include "r-type/Projectile.hpp"
#include <iostream>
#include <vector>

class Game
{
public:
    enum Event
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE,
        ENTER,
        ESCAPE,
        UNKNOWN
    };
    Game(std::shared_ptr<Engine> &engine);
    ~Game();

    void update(Event event);

private:
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<EntityType<IEntity>> _playersGroups;
    std::shared_ptr<EntityType<IEntity>> _projectilesGroups;
    std::vector<std::shared_ptr<Player>> _players;
    std::vector<std::shared_ptr<Projectile>> _projectiles;
};
