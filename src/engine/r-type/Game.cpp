/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game
*/

#include "Game.hpp"
#include "Classic.hpp"
#include "Enemy.hpp"
#include "Speed.hpp"
#include "Shooter.hpp"
#include "Tank.hpp"
#include "Shield.hpp"

Game *Game::instance = nullptr;

Game::Game(std::shared_ptr<Engine> &engine) : _engine(engine)
{
    instance = this;
    // Create all entities groups
    _playersGroups = std::make_shared<EntityType<IEntity>>(16);
    _projectilesGroups = std::make_shared<EntityType<IEntity>>(4);
    _enemyProjectilesGroups = std::make_shared<EntityType<IEntity>>(3);
    _staticObjectsGroups = std::make_shared<EntityType<IEntity>>(0);
    _orangeRobotGroups = std::make_shared<EntityType<IEntity>>(20);
    _flyerGroups = std::make_shared<EntityType<IEntity>>(10);
    _enemie2Groups = std::make_shared<EntityType<IEntity>>(24);

    // initializeLevel();
    _levelInitializer = std::make_shared<LevelInitializer>(this);
    _levelInitializer->loadLevel(_currentLevel);

    // Add collision between entities groups
    _engine->setRelation(_projectilesGroups, _orangeRobotGroups, Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _flyerGroups, Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _playersGroups, Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _enemie2Groups, Projectile::hurtEntity);
    _engine->setRelation(_enemyProjectilesGroups, _playersGroups, Projectile::hurtEntity);
    _engine->setRelation(_playersGroups, _orangeRobotGroups, Character::hurtEnemy);
    _engine->setRelation(_playersGroups, _flyerGroups, Character::hurtEnemy);
    _engine->setRelation(_playersGroups, _enemie2Groups, Character::hurtEnemy);
}

Game::~Game()
{
    // Destroy all entities
    _players.clear();
}

int Game::getId(Event event)
{
    std::stringstream ss(event.body);
    std::string playerId;
    ss >> playerId;
    int id = std::stoi(playerId.substr(1));
    return (id);
}

std::shared_ptr<Character> Game::getRandomSpaceship()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 4);
    int random = distrib(gen);
    IEntity::EntityInfo info;
    info.x = 50;
    info.y = 100;
    info.spriteConfigJsonFileName = "rTypeConfig.json";
    info.spriteConfigJsonObjectName = "Spaceship";
    info.id = _lastId;
    _lastId++;

    switch (random)
    {
    case 0:
        info.assetFile = _assets["Classic"]();
        return (std::make_shared<Classic>(info));
    case 1:
        info.assetFile = _assets["Speed"]();
        return (std::make_shared<Speed>(info));
    case 2:
        info.assetFile = _assets["Shooter"]();
        return (std::make_shared<Shooter>(info));
    case 3:
        info.assetFile = _assets["Tank"]();
        return (std::make_shared<Tank>(info));
    case 4:
        info.assetFile = _assets["ShieldSpaceship"]();
        return (std::make_shared<Shield>(info));
    default:
        info.assetFile = _assets["Classic"]();
        return (std::make_shared<Classic>(info));
    }
}

void Game::update(ThreadSafeQueue<Event> &events)
{
    eraseDeadEntity();
    while (!events.empty())
    {
        auto event = events.pop_front();
        switch (event.ACTION_NAME)
        {
        case ACTION::LEFT:
            if (_players.size() > 0)
                _players[getId(event) - 1]->move(-1, 0);
            break;
        case ACTION::RIGHT:
            if (_players.size() > 0)
                _players[getId(event) - 1]->move(1, 0);
            break;
        case ACTION::UP:
            if (_players.size() > 0)
                _players[getId(event) - 1]->move(0, -1);
            break;
        case ACTION::DOWN:
            if (_players.size() > 0)
                _players[getId(event) - 1]->move(0, 1);
            break;
        case ACTION::SHOOT:
            _players[getId(event) - 1]->shoot();
            break;
        case ACTION::SHIELD:
            _players[getId(event) - 1]->action();
            break;
        case ACTION::FLIP:
            _players[getId(event) - 1]->flip();
            break;
        case ACTION::READY:
            _players.push_back(getRandomSpaceship());
            _playersGroups->insert(_players[_players.size() - 1]);
            setAllEntitiesToCreated();
            break;
        case ACTION::DEAD:
        {
            int id = std::stoi(event.body);
            eraseDeadEntity(id);
            break;
        }
        default:
            break;
        }
    }
    if (_enemies.size() == 0 && _currentLevel != MAX_LEVEL)
    {
        _currentLevel++;
        deleteAllEntities();
        _reset = true;
        _levelInitializer->loadLevel(_currentLevel);
        for (auto player : _players)
        {
            player->setId(_lastId);
            player->setCreated(false);
            player->resetLife();
            _lastId++;
        }
    }
}

void Game::createExplosion(int x, int y)
{
    IEntity::EntityInfo info;
    info.x = x;
    info.y = y;
    info.assetFile = _assets["ExplosionSpaceship"]();
    info.spriteConfigJsonFileName = "rTypeConfig.json";
    info.spriteConfigJsonObjectName = "ExplosionSpaceship";
    info.scaleX = 2;
    info.scaleY = 2;
    info.id = _lastId;
    _lastId++;
    std::shared_ptr<AEntity> explosion = std::make_shared<AEntity>(info);
    _staticObjectsGroups->insert(explosion);
    _staticObjects.push_back(explosion);
}

void Game::createProjectile(IEntity::EntityInfo info, bool flip, IGame::ProjectileGroup group)
{
    info.assetFile = _assets[info.name]();
    info.id = _lastId;
    _lastId++;
    std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(info);
    if (group == ProjectileGroup::PLAYER)
    {
        _projectilesGroups->insert(projectile);
        _projectiles.push_back(projectile);
    }
    else if (group == ProjectileGroup::ENEMY)
    {
        _enemyProjectilesGroups->insert(projectile);
        _projectiles.push_back(projectile);
    }
    if (flip)
        projectile->setFlip(flip);
}

std::shared_ptr<AEntity> Game::createShield(int x, int y)
{
    IEntity::EntityInfo info;
    info.x = x;
    info.y = y;
    info.assetFile = _assets["Shield"]();
    info.spriteConfigJsonFileName = "rTypeConfig.json";
    info.spriteConfigJsonObjectName = "Shield";
    info.id = _lastId;
    _lastId++;
    std::shared_ptr<AEntity> _shield = std::make_shared<AEntity>(info);
    _staticObjectsGroups->insert(_shield);
    _staticObjects.push_back(_shield);
    return (_shield);
}

void Game::eraseDeadEntity(int id)
{
    for (auto it = _staticObjects.begin(); it != _staticObjects.end(); it++)
    {
        if ((*it)->getId() == id)
        {
            (*it)->kill();
            _staticObjects.erase(it);
            break;
        }
    }
}

void Game::eraseDeadEntity()
{
    for (auto it = _staticObjects.begin(); it != _staticObjects.end(); it++)
    {
        if ((*it)->isDead())
        {
            _staticObjects.erase(it);
            break;
        }
    }
    for (auto it = _enemies.begin(); it != _enemies.end(); it++)
    {
        if ((*it)->isDead())
        {
            _enemies.erase(it);
            break;
        }
    }
    for (auto it = _players.begin(); it != _players.end(); it++)
    {
        if ((*it)->isDead())
        {
            _players.erase(it);
            break;
        }
    }
    for (auto it = _projectiles.begin(); it != _projectiles.end(); it++)
    {
        if ((*it)->isDead())
        {
            _projectiles.erase(it);
            break;
        }
    }
}

void Game::setAllEntitiesToCreated()
{
    for (auto staticObject : _staticObjects)
    {
        staticObject->setCreated(false);
    }
    for (auto enemy : _enemies)
    {
        enemy->setCreated(false);
    }
    for (auto player : _players)
    {
        player->setCreated(false);
    }
    for (auto projectile : _projectiles)
    {
        projectile->setCreated(false);
    }
}

void Game::deleteAllEntities()
{
    _lastId = 0;
    for (auto staticObject : _staticObjects)
        staticObject->kill();
    for (auto enemy : _enemies)
        enemy->kill();
    for (auto projectile : _projectiles)
        projectile->kill();
    _staticObjects.clear();
    _enemies.clear();
    _projectiles.clear();
    _staticObjectsGroups->clear();
    _enemie2Groups->clear();
    _flyerGroups->clear();
    _orangeRobotGroups->clear();
    _projectilesGroups->clear();
}

bool Game::isReset()
{
    return (_reset);
}

void Game::setReset(bool reset)
{
    _reset = reset;
}

int Game::getCurrentId()
{
    return (_lastId);
}

int Game::getCurrentLevel()
{
    return (_currentLevel);
}

std::map<std::string, std::function<std::string()>> Game::getAssets()
{
    return (_assets);
}

void Game::setCurrentId(int id)
{
    _lastId = id;
}

void Game::createEnemy(IEntity::EntityInfo info)
{
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(info);
    enemy->setMovementType(info.movementType);
    _enemies.push_back(enemy);
    if (info.name == "OrangeRobot")
        _orangeRobotGroups->insert(enemy);
    else if (info.name == "Flyer")
        _flyerGroups->insert(enemy);
    else if (info.name == "Enemy2")
        _enemie2Groups->insert(enemy);
}

void Game::createBackground(IEntity::EntityInfo info)
{
    std::shared_ptr<AEntity> background = std::make_shared<AEntity>(info);
    _staticObjects.push_back(background);
    _staticObjectsGroups->insert(background);
}

void Game::clearLevel()
{
    _lastId = 0;
    for (auto player : _players)
    {
        player->setId(_lastId++);
        player->setCreated(false);
        player->resetLife();
    }
    _orangeRobotGroups->clear();
    _flyerGroups->clear();
    _enemie2Groups->clear();
    _projectilesGroups->clear();
    _enemyProjectilesGroups->clear();
    _staticObjectsGroups->clear();
    _enemies.clear();
    _projectiles.clear();
    _staticObjects.clear();
}

std::map<std::string, std::function<std::string()>> Game::_assets = {

    {"Classic", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.Classic");
     }},
    {"Speed", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.Speed");
     }},
    {"Shooter", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.Shooter");
     }},
    {"Tank", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.Tank");
     }},
    {"ShieldSpaceship", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.ShieldSpaceship");
     }},
    {"OrangeRobot", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.OrangeRobot");
     }},
    {"Enemy2", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.Enemy2");
     }},
    {"Background", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.Background");
     }},
    {"ExplosionSpaceship", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.ExplosionSpaceShip");
     }},
    {"Shield", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.Shield");
     }},
    {"PlayerProjectile", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.PlayerProjectile");
     }},
    {"DiskProjectile", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.DiskProjectile");
     }},
    {"OrangeProjectile", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.OrangeProjectile");
     }},
    {"Flyer", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.Flyer");
     }}};
