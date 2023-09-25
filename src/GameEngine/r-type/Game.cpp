/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game
*/

#include "Game.hpp"
#include "Player.hpp"

Game *Game::instance = nullptr;

Game::Game(std::shared_ptr<Engine> &engine) : _engine(engine)
{
    instance = this;
    // Create all entities
    _staticObjectsGroups = std::make_shared<EntityType<IEntity>>(0);
    _staticObjectsGroups->insert(std::make_shared<StaticObject>("background.png", 0, 0, _lastId++));
    _playersGroups = std::make_shared<EntityType<IEntity>>(16);
    _projectilesGroups = std::make_shared<EntityType<IEntity>>(4);
    _players.push_back(std::make_shared<Player>("Spaceship1.png", 0, 50, _lastId++, 0, 1, 1, 100, 1, 1, 1, 5));
    _playersGroups->insert(_players[0]);
    // Add collision
    engine->setRelation(_playersGroups, _projectilesGroups, Player::hurtProjectile);
}

Game::~Game()
{
    // Destroy all entities
    _players.clear();
}

void Game::update(Event event)
{
    switch (event) {
        case LEFT:
            _players[0]->move(-3, 0);
            break;
        case RIGHT:
            _players[0]->move(3, 0);
            break;
        case UP:
            _players[0]->move(0, -3);
            break;
        case DOWN:
            _players[0]->move(0, 3);
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
    _staticObjectsGroups->insert(std::make_shared<StaticObject>("explosion_type_left1.png", x, y, _lastId++, 0, 1, 1, 6));
}

void Game::createProjectile(int x, int y, std::string path, float scaleX, float scaleY, int speed)
{
    _projectilesGroups->insert(std::make_shared<Projectile>(path, x, y, _lastId++, 0, scaleX, scaleY, speed, 2));
}