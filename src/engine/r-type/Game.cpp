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
    _enemie1Groups = std::make_shared<EntityType<IEntity>>(20);
    _flyerGroups = std::make_shared<EntityType<IEntity>>(10);
    _enemie2Groups = std::make_shared<EntityType<IEntity>>(24);

    initializeLevel();

    // Add collision between entities groups
    _engine->setRelation(_projectilesGroups, _enemie1Groups, Projectile::hurtEntity);
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

void Game::initializeLevel()
{
    _lastId = 0;
    JsonParser parser;
    nlohmann::json levelsFile = JsonParser::readFile("rTypeLevels.json");

    int count = 0;
    nlohmann::json level = levelsFile["Level-" + std::to_string(_currentLevel)];
    std::vector<std::tuple<int, int>> positions;
    std::string movementType;
    std::string bulletType;
    float fireRate = 0;
    float speed = 0;
    float bulletSpeed = 0;
    int damage = 0;
    int life = 0;


    //TODO: replace the parsing by this one
    // for (const auto& [key, value] : level.items())
    // {
    //     std::cout << key << " " << value << std::endl;
    //     std::cout << "---------------------" << std::endl;
    //     if (value.contains("Count")) {
    //         std::cout << "Count: " << value["Count"] << std::endl;
    //     }
    // }

    for (auto it2 = level.begin(); it2 != level.end(); it2++)
    {
        std::string key = it2.key();
        auto value = it2.value();

        for (auto it3 = value.begin(); it3 != value.end(); it3++)
        {
            if (it3.key() == "Count")
            {
                count = *it3;
            }
            else if (it3.key() == "Type")
            {
                if (count == 0)
                {
                    std::cout << "Background initialized" << std::endl;
                    std::shared_ptr<StaticObject> background = std::make_shared<StaticObject>(_assets[key](), 425, 239, _lastId++, "rTypeConfig.json", "Background");
                    _staticObjects.push_back(background);
                    _staticObjectsGroups->insert(background);
                    std::cout << "Background " << _staticObjects.size() << std::endl;
                }
                else
                {
                    for (int i = 0; i < count; i++)
                    {
                        if (it3.value() == "Enemy1")
                        {
                            std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(_assets[key](), std::get<0>(positions[i]), std::get<1>(positions[i]), _lastId++, it3.value(), bulletType, fireRate, speed, bulletSpeed, damage, life);
                            enemy->setMovementType(movementType);
                            _enemies.push_back(enemy);
                            _enemie1Groups->insert(enemy);
                        }
                        else if (it3.value() == "Flyer")
                        {
                            std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(_assets[key](), std::get<0>(positions[i]), std::get<1>(positions[i]), _lastId++, it3.value(), bulletType, fireRate, speed, bulletSpeed, damage, life);
                            enemy->setMovementType(movementType);
                            _enemies.push_back(enemy);
                            _flyerGroups->insert(enemy);
                        }
                        else if (it3.value() == "Enemy2")
                        {
                            std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(_assets[key](), std::get<0>(positions[i]), std::get<1>(positions[i]), _lastId++, it3.value(), bulletType, fireRate, speed, bulletSpeed, damage, life);
                            enemy->setMovementType(movementType);
                            _enemies.push_back(enemy);
                            _enemie2Groups->insert(enemy);
                        }
                    }
                    count = 0;
                }
            }
            else if (it3.key() == "Positions")
            {
                positions.clear();
                auto position = it3.value();
                for (int i = 0; i < count; i++)
                {
                    if (it2.key() == "Enemy1" || it2.key() == "Flyer" || it2.key() == "Enemy2")
                    {
                        nlohmann::json pos = position[i];
                        // std::cout << pos.at("X") << " " << pos.at("Y") << std::endl;
                        positions.push_back(std::make_tuple(pos.at("X"), pos.at("Y")));
                    }
                }
            }
            else if (it3.key() == "MovementType")
            {
                movementType = it3.value();
            }
            else if (it3.key() == "BulletType")
            {
                bulletType = it3.value();
            }
            else if (it3.key() == "FireRate")
            {
                fireRate = it3.value();
            }
            else if (it3.key() == "Speed")
            {
                speed = it3.value();
            }
            else if (it3.key() == "BulletSpeed")
            {
                bulletSpeed = it3.value();
            }
            else if (it3.key() == "Damage")
            {
                damage = it3.value();
            }
            else if (it3.key() == "Life")
            {
                life = it3.value();
            }
        }
    }
    for (auto player : _players)
    {
        player->setId(_lastId++);
        player->setCreated(false);
        player->resetLife();
    }
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
        return (std::make_shared<Classic>(_assets["Classic"](), 50, 100, _lastId++, 5));
    case 1:
        return (std::make_shared<Speed>(_assets["Speed"](), 50, 100, _lastId++, 5));
    case 2:
        return (std::make_shared<Shooter>(_assets["Shooter"](), 50, 100, _lastId++, 5));
    case 3:
        return (std::make_shared<Tank>(_assets["Tank"](), 50, 100, _lastId++, 5));
    case 4:
        return (std::make_shared<Shield>(_assets["ShieldSpaceship"](), 50, 100, _lastId++, 5));
    default:
        return (std::make_shared<Classic>(_assets["Classic"](), 50, 100, _lastId++, 5));
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
        initializeLevel();
    }
}

void Game::createExplosion(int x, int y)
{
    std::shared_ptr<StaticObject> explosion = std::make_shared<StaticObject>(_assets["ExplosionSpaceship"](), x, y, _lastId++, "rTypeConfig.json", "ExplosionSpaceship", 0, 2, 2, 6);
    _staticObjectsGroups->insert(explosion);
    _staticObjects.push_back(explosion);
}

void Game::createProjectile(int x, int y, std::string path, float scaleX, float scaleY, int speed, int damage, std::string spriteConfigJsonObjectName, std::string groupName, bool flip, IEntity::Direction direction)
{
    std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(_assets[path](), x, y, _lastId++, damage, 0, scaleX, scaleY, speed, 2, spriteConfigJsonObjectName, direction);
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

std::shared_ptr<StaticObject> Game::createShield(int x, int y)
{
    std::shared_ptr<StaticObject> _shield = std::make_shared<StaticObject>(_assets["Shield"](), x, y, _lastId++, "rTypeConfig.json", "Shield", 0, 1, 1, 1);
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
            (*it)->setDead(true);
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
    for (auto staticObject : _staticObjects)
        staticObject->kill();
    for (auto enemy : _enemies)
        enemy->kill();
    for (auto projectile : _projectiles)
        projectile->kill();

    _staticObjects.clear();
    _enemies.clear();
    _projectiles.clear();
}

bool Game::isReset()
{
    return (_reset);
}

void Game::setReset(bool reset)
{
    _reset = reset;
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
    {"Enemy1", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.Enemy1");
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
    {"BulletSpaceship", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.BulletSpaceship");
     }},
    {"BulletEnemy1", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.BulletEnemy1");
     }},
    {"BulletEnemy2", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.BulletEnemy2");
     }},
    {"Flyer", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("rTypeSetup.json"), "Game.Assets.Images.Flyer");
     }}};
