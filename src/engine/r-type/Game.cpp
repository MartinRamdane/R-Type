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

    switch (random)
    {
    case 0:
        return (std::make_shared<Classic>(_assets["Classic"](), 50, 100, _lastId++));
    case 1:
        return (std::make_shared<Speed>(_assets["Speed"](), 50, 100, _lastId++));
    case 2:
        return (std::make_shared<Shooter>(_assets["Shooter"](), 50, 100, _lastId++));
    case 3:
        return (std::make_shared<Tank>(_assets["Tank"](), 50, 100, _lastId++));
    case 4:
        return (std::make_shared<Shield>(_assets["ShieldSpaceship"](), 50, 100, _lastId++));
    default:
        return (std::make_shared<Classic>(_assets["Classic"](), 50, 100, _lastId++));
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
        std::cout << "Level " << _currentLevel << " finished" << std::endl;
        _currentLevel++;
        deleteAllEntities();
        _reset = true;
        _levelInitializer->loadLevel(_currentLevel);
        std::cout << "Last1 id: " << _lastId << std::endl;
        for (auto player : _players)
        {
            player->setId(_lastId);
            player->setCreated(false);
            player->resetLife();
            _lastId++;
        }
        std::cout << "Last2 id: " << _lastId << std::endl;
    }
}

void Game::createExplosion(int x, int y)
{
    std::shared_ptr<AEntity> explosion = std::make_shared<AEntity>(_assets["ExplosionSpaceship"](), x, y, _lastId++, "rTypeConfig.json", "ExplosionSpaceship", 2, 2);
    _staticObjectsGroups->insert(explosion);
    _staticObjects.push_back(explosion);
}

void Game::createProjectile(int x, int y, std::string path, float scaleX, float scaleY, int speed, int damage, std::string spriteConfigJsonObjectName, std::string groupName, bool flip, IEntity::Direction direction)
{
    std::cout << "asset path: " << _assets[path]() << std::endl;
    std::cout << "spriteConfigJsonObjectName: " << spriteConfigJsonObjectName << std::endl;
    std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(_assets[path](), x, y, _lastId++, damage, scaleX, scaleY, speed, spriteConfigJsonObjectName, direction);
    if (groupName == "_projectilesGroups")
    {
        _projectilesGroups->insert(projectile);
        _projectiles.push_back(projectile);
    }
    else if (groupName == "_enemyProjectilesGroups")
    {
        _enemyProjectilesGroups->insert(projectile);
        _projectiles.push_back(projectile);
    }
    if (flip)
        projectile->setFlip(flip);
}

std::shared_ptr<AEntity> Game::createShield(int x, int y)
{
    std::shared_ptr<AEntity> _shield = std::make_shared<AEntity>(_assets["Shield"](), x, y, _lastId++, "rTypeConfig.json", "Shield");
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
    std::cout << info.assetFile << std::endl;
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(info.assetFile, info.x, info.y, info.id, info.name, info.projectileType, info.fireRate, info.speed, info.projectileSpeed, info.damage, info.life);
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
    std::shared_ptr<AEntity> background = std::make_shared<AEntity>(info.assetFile, info.x, info.y, info.id, info.spriteJsonFileName, info.spriteConfigJsonObjectName);
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
