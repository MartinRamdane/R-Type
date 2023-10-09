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
    initializeLevel();
    std::cout << "end" << std::endl;

    // Create all entities
    // _staticObjectsGroups = std::make_shared<EntityType<IEntity>>(0);
    // _staticObjectsGroups->insert(std::make_shared<StaticObject>(_assets["Background"](), 0, 239, _lastId++, "config.json", "Background"));
    _playersGroups = std::make_shared<EntityType<IEntity>>(16);
    _projectilesGroups = std::make_shared<EntityType<IEntity>>(4);
    _players.push_back(std::make_shared<Shield>(_assets["ShieldSpaceship"](), 50, 100, _lastId++, 5));
    _playersGroups->insert(_players[0]);
    // _enemiesGroups = std::make_shared<EntityType<IEntity>>(20);
    // _enemiesGroups->insert(std::make_shared<Enemy>(_assets["Enemy1"](), 500, 100, _lastId++));
    // Add collision
    engine->setRelation(_projectilesGroups, _enemiesGroups, Projectile::hurtEntity);
}

Game::~Game()
{
    // Destroy all entities
    _players.clear();
}

void Game::initializeLevel()
{
    JsonParser parser;
    nlohmann::json levelsFile = JsonParser::readFile("rTypeLevels.json");

    int count = 0;
    _staticObjectsGroups = std::make_shared<EntityType<IEntity>>(0);
    _enemiesGroups = std::make_shared<EntityType<IEntity>>(20);

    nlohmann::json level = levelsFile["Level-" + std::to_string(currentLevel)];

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
                    _staticObjectsGroups->insert(std::make_shared<StaticObject>(_assets[key](), 425, 239, _lastId++, "config.json", "Background"));
                    std::cout << "Background" << std::endl;
                }
                else
                {
                    for (int i = 0; i < count; i++)
                    {
                        if (it3.value() == "Enemy")
                        {
                            _enemiesGroups->insert(std::make_shared<Enemy>(_assets[key](), 500 + i * 100, 100, _lastId++));
                            std::cout << key << std::endl;
                        }
                    }
                    count = 0;
                }
            }
        }
    }
}

void Game::update(ThreadSafeQueue<ACTION> &actions)
{
    while (!actions.empty()) {
        auto action = actions.pop_front();
        switch (action)
        {
            case ACTION::LEFT:
                _players[0]->move(-1, 0);
                break;
            case ACTION::RIGHT:
                _players[0]->move(1, 0);
                break;
            case ACTION::UP:
                _players[0]->move(0, -1);
                break;
            case ACTION::DOWN:
                _players[0]->move(0, 1);
                break;
            case ACTION::SHOOT:
                _players[0]->shoot();
                break;
            case ACTION::SHIELD:
            std::cout << "SHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELDSHIELD" << std::endl;
                _players[0]->action();
                break;
            default:
                break;
        }
    }
}

void Game::createExplosion(int x, int y)
{
    _staticObjectsGroups->insert(std::make_shared<StaticObject>(_assets["ExplosionSpaceship"](), x, y, _lastId++, "config.json", "ExplosionSpaceship", 0, 2, 2, 6));
}

void Game::createProjectile(int x, int y, std::string path, float scaleX, float scaleY, int speed, int damage, std::string spriteConfigJsonObjectName)
{
    _projectilesGroups->insert(std::make_shared<Projectile>(_assets[path](), x, y, _lastId++, damage, 0, scaleX, scaleY, speed, 2, spriteConfigJsonObjectName));
}

std::shared_ptr<StaticObject> Game::createShield(int x, int y)
{
    std::cout << "x la: " << x << std::endl;
    std::shared_ptr<StaticObject> _shield = std::make_shared<StaticObject>(_assets["Shield"](), x, y, _lastId++, "config.json", "Shield", 0, 1, 1, 1);
    _staticObjectsGroups->insert(_shield);
    std::cout << "SHIELD CREATED" << std::endl;
    return (_shield);
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
};
