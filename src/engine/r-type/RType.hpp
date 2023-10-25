/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RType
*/

#pragma once
#include "../Engine.hpp"
#include "../IEntity.hpp"
#include "Projectile.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "../AEntity.hpp"
#include "../../global/JsonParser.hpp"
#include "../IGame.hpp"
#include <random>
#include <tuple>
#include "LevelInitializer.hpp"

class Character;
class Enemy;
class Projectile;
class SupportShip ;

#define MAX_LEVEL 1

class RType : public IGame
{
public:
    RType(std::shared_ptr<Engine> &engine);
    ~RType();
    static RType *instance;

    void update(ThreadSafeQueue<Event> &events);
    void createExplosion(int x, int y);
    void createProjectile(IEntity::EntityInfo info, bool flip, IGame::ProjectileGroup group);
    std::shared_ptr<AEntity> createShield(int x, int y);
    int getId(Event event);
    std::shared_ptr<Character> getRandomSpaceship();
    void eraseDeadEntity(int id);
    void eraseDeadEntity();
    void setAllEntitiesToCreated();
    void deleteAllEntities();
    bool isReset();
    void setReset(bool reset);
    int getCurrentId();
    int getCurrentLevel();
    void setCurrentId(int id);
    std::map<std::string, std::function<std::string()>> getAssets();
    void createEnemy(IEntity::EntityInfo info);
    void createBackground(IEntity::EntityInfo info);
    void clearLevel();
    std::shared_ptr<AEntity> createSupportShip(int x, int y, int playerId);
    std::shared_ptr<AEntity> getPlayer(int id);

private:
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<EntityType<IEntity>> _playersGroups;
    std::shared_ptr<EntityType<IEntity>> _supportShipGroups;
    std::shared_ptr<EntityType<IEntity>> _projectilesGroups;
    std::shared_ptr<EntityType<IEntity>> _supportProjectilesGroups;
    std::shared_ptr<EntityType<IEntity>> _enemyProjectilesGroups;
    std::shared_ptr<EntityType<IEntity>> _staticObjectsGroups;
    std::shared_ptr<EntityType<IEntity>> _orangeRobotGroups;
    std::shared_ptr<EntityType<IEntity>> _enemie2Groups;
    std::shared_ptr<EntityType<IEntity>> _flyerGroups;
    std::vector<std::shared_ptr<Character>> _players;
    std::vector<std::shared_ptr<Projectile>> _projectiles;
    std::vector<std::shared_ptr<AEntity>> _staticObjects;
    std::vector<std::shared_ptr<Enemy>> _enemies;
    std::vector<std::shared_ptr<SupportShip>> _supportShips;
    int _lastId = 0;
    static std::map<std::string, std::function<std::string()>> _assets;
    int _currentLevel = 1;
    bool _reset = false;
    std::shared_ptr<LevelInitializer> _levelInitializer;
};
