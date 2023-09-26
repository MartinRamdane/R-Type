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

Game *Game::instance = nullptr;

Game::Game(std::shared_ptr<Engine> &engine) : _engine(engine)
{
    instance = this;
    // Create all entities
    _staticObjectsGroups = std::make_shared<EntityType<IEntity>>(0);
    _staticObjectsGroups->insert(std::make_shared<StaticObject>(_assets["Background"](), 0, 239, _lastId++));
    _playersGroups = std::make_shared<EntityType<IEntity>>(16);
    _projectilesGroups = std::make_shared<EntityType<IEntity>>(4);
    _players.push_back(std::make_shared<Tank>(_assets["Tank"](), 50, 100, _lastId++, 5));
    _playersGroups->insert(_players[0]);
    _enemiesGroups = std::make_shared<EntityType<IEntity>>(20);
    _enemiesGroups->insert(std::make_shared<Enemy>(_assets["Enemy1"](), 500, 100, _lastId++, 0, 1, 1, 100, 1, 1, 3, 2));
    // Add collision
    engine->setRelation(_playersGroups, _projectilesGroups, Character::hurtProjectile);
    engine->setRelation(_projectilesGroups, _enemiesGroups, Projectile::hurtEntity);
}

Game::~Game()
{
    // Destroy all entities
    _players.clear();
}

void Game::update(Event event)
{
    switch (event)
    {
    case LEFT:
        _players[0]->move(-1, 0);
        break;
    case RIGHT:
        _players[0]->move(1, 0);
        break;
    case UP:
        _players[0]->move(0, -1);
        break;
    case DOWN:
        _players[0]->move(0, 1);
        break;
    case SHOOT:
        _players[0]->shoot();
        break;
    default:
        break;
    }
}

void Game::createExplosion(int x, int y)
{
    _staticObjectsGroups->insert(std::make_shared<StaticObject>(_assets["ExplosionSpaceship"](), x, y, _lastId++, 0, 1, 1, 6));
}

void Game::createProjectile(int x, int y, std::string path, float scaleX, float scaleY, int speed, int damage)
{
    _projectilesGroups->insert(std::make_shared<Projectile>(path, x, y, _lastId++, damage, 0, scaleX, scaleY, speed, 2));
}

std::map<std::string, std::function<std::string()>> Game::_assets = {

    {"Classic", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("src/GameEngine/r-type/assets/Setup.json"), "Game.Assets.Images.Classic");
     }},
    {"Speed", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("src/GameEngine/r-type/assets/Setup.json"), "Game.Assets.Images.Speed");
     }},
    {"Shooter", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("src/GameEngine/r-type/assets/Setup.json"), "Game.Assets.Images.Shooter");
     }},
    {"Tank", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("src/GameEngine/r-type/assets/Setup.json"), "Game.Assets.Images.Shooter");
     }},
    {"Shield", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("src/GameEngine/r-type/assets/Setup.json"), "Game.Assets.Images.Shooter");
     }},
    {"Enemy1", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("src/GameEngine/r-type/assets/Setup.json"), "Game.Assets.Images.Enemy");
     }},
    {"Background", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("src/GameEngine/r-type/assets/Setup.json"), "Game.Assets.Images.Background");
     }},
    {"ExplosionSpaceship", []()
     {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("src/GameEngine/r-type/assets/Setup.json"), "Game.Assets.Images.Explosion");
     }},
};
