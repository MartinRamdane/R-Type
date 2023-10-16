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
#include <sstream>
#include <vector>
#include <map>
#include "../StaticObject.hpp"
#include "../../global/JsonParser.hpp"
#include "../IGame.hpp"
#include <random>
#include <tuple>

class Character;
class Enemy;
class Projectile;

class Game : public IGame
{
public:
    Game(std::shared_ptr<Engine> &engine);
    ~Game();
    static Game *instance;

    void update(ThreadSafeQueue<Event> &events);
    void createExplosion(int x, int y);
    void createProjectile(int x, int y, std::string path, float scaleX, float scaleY, int speed, int damage, std::string spriteConfigJsonObjectName, std::string groupName, bool flip, IEntity::Direction direction = IEntity::RIGHT);
    std::shared_ptr<StaticObject> createShield(int x, int y);
    void initializeLevel();
    int getId(Event event);
    std::shared_ptr<Character> getRandomSpaceship();
    void eraseDeadEntity(int id);

private:
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<EntityType<IEntity>> _playersGroups;
    std::shared_ptr<EntityType<IEntity>> _projectilesGroups;
    std::shared_ptr<EntityType<IEntity>> _enemyProjectilesGroups;
    std::shared_ptr<EntityType<IEntity>> _staticObjectsGroups;
    std::shared_ptr<EntityType<IEntity>> _enemie1Groups;
    std::shared_ptr<EntityType<IEntity>> _enemie2Groups;
    std::shared_ptr<EntityType<IEntity>> _flyerGroups;
    std::vector<std::shared_ptr<Character>> _players;
    std::vector<std::shared_ptr<Projectile>> _projectiles;
    std::vector<std::shared_ptr<StaticObject>> _staticObjects;
    std::vector<std::shared_ptr<Enemy>> _enemies;
    int _lastId = 0;
    static std::map<std::string, std::function<std::string()>> _assets;
    int currentLevel = 1;
};
