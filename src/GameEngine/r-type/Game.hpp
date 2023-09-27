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
#include <map>
#include "../StaticObject.hpp"
#include "../JsonParser.hpp"

class Character;

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
        SHIELD,
        UNKNOWN
    };
    Game(std::shared_ptr<Engine> &engine);
    ~Game();
    static Game *instance;

    void update(Event event);
    void createExplosion(int x, int y);
    void createProjectile(int x, int y, std::string path, float scaleX, float scaleY, int speed, int damage, std::string spriteConfigJsonObjectName);
    std::shared_ptr<StaticObject> createShield(int x, int y);

private:
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<EntityType<IEntity>> _playersGroups;
    std::shared_ptr<EntityType<IEntity>> _projectilesGroups;
    std::shared_ptr<EntityType<IEntity>> _staticObjectsGroups;
    std::shared_ptr<EntityType<IEntity>> _enemiesGroups;
    std::vector<std::shared_ptr<Character>> _players;
    int _lastId = 0;
    static std::map<std::string, std::function<std::string()>> _assets;
};
