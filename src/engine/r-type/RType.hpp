/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RType
*/

#pragma once
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <tuple>
#include <vector>
#include "../../global/JsonParser.hpp"
#include "../AEntity.hpp"
#include "../Engine.hpp"
#include "../IEntity.hpp"
#include "../IGame.hpp"
#include "LevelInitializer.hpp"
#include "Projectile.hpp"

class Character;
class Enemy;
class Projectile;
class SupportShip;
class Dropper;
class Boss;

class RType : public IGame {
   public:
    RType(std::shared_ptr<Engine>& engine);
    ~RType();
    static RType* instance;

    void update(ThreadSafeQueue<Event>& events);
    void createExplosion(int x, int y);
    void createProjectile(IEntity::EntityInfo info, bool flip, IGame::ProjectileGroup group);
    std::shared_ptr<AEntity> createShield(int x, int y, float speed);
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
    std::map<std::string, std::string> getAssets();
    void createEnemy(IEntity::EntityInfo info);
    void createBackground(IEntity::EntityInfo info);
    void createDropper(IEntity::EntityInfo info);
    void createBoss(IEntity::EntityInfo info);
    void createWall(IEntity::EntityInfo info);
    void clearLevel();
    std::shared_ptr<AEntity> createSupportShip(int x, int y);
    std::shared_ptr<AEntity> getPlayer(int id);
    std::vector<std::shared_ptr<AEntity>> getPlayers();
    void setPlayerHasSupport(int id, bool support);
    void createAssetList();
    std::vector<std::shared_ptr<AEntity>> getEnemies();
    void createSound(std::string path);
    void createMusic(std::string path);
    int _maxLevel = 1;

   private:
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<EntityType<IEntity>> _playersGroups;
    std::shared_ptr<EntityType<IEntity>> _supportShipGroups;
    std::shared_ptr<EntityType<IEntity>> _projectilesGroups;
    std::shared_ptr<EntityType<IEntity>> _supportProjectilesGroups;
    std::shared_ptr<EntityType<IEntity>> _enemyProjectilesGroups;
    std::shared_ptr<EntityType<IEntity>> _staticObjectsGroups;
    std::shared_ptr<EntityType<IEntity>> _orangeRobotGroups;
    std::shared_ptr<EntityType<IEntity>> _greenRobotGroups;
    std::shared_ptr<EntityType<IEntity>> _wormGroups;
    std::shared_ptr<EntityType<IEntity>> _flyerGroups;
    std::shared_ptr<EntityType<IEntity>> _dropperGroups;
    std::shared_ptr<EntityType<IEntity>> _bombermanGroups;
    std::shared_ptr<EntityType<IEntity>> _bossGroups;
    std::shared_ptr<EntityType<IEntity>> _bombGroups;
    std::shared_ptr<EntityType<IEntity>> _circularRobotGroups;
    std::shared_ptr<EntityType<IEntity>> _wallGroups;
    std::vector<std::shared_ptr<Character>> _players;
    std::vector<std::shared_ptr<Projectile>> _projectiles;
    std::vector<std::shared_ptr<AEntity>> _staticObjects;
    std::vector<std::shared_ptr<AEntity>> _enemies;
    std::vector<std::shared_ptr<SupportShip>> _supportShips;
    std::vector<std::shared_ptr<Dropper>> _dropper;
    std::vector<std::shared_ptr<AEntity>> _musics;
    int _lastId = 0;
    std::map<std::string, std::string> _assets;
    int _currentLevel = 1;
    bool _reset = false;
    std::unique_ptr<LevelInitializer> _levelInitializer;
};
