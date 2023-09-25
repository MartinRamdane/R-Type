/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(std::shared_ptr<Engine> &engine) : _engine(engine)
{
    // Create all entities
    _staticObjectsGroups = std::make_shared<EntityType<IEntity>>(0);
    _staticObjectsGroups->insert(std::make_shared<StaticObject>("background.png", 0, 0, _lastId++, 0, 1, 1));
    _playersGroups = std::make_shared<EntityType<IEntity>>(16);
    _projectilesGroups = std::make_shared<EntityType<IEntity>>(4);
    _players.push_back(std::make_shared<Player>("Spaceship1.png", 0, 50, _lastId++, 0, 1, 1, 100, 1, 1, 1));
    _playersGroups->insert(_players[0]);
    _projectiles.push_back(std::make_shared<Projectile>("shoot_type_left2.png", 500, 50, _lastId++));
    _projectilesGroups->insert(_projectiles[0]);

    // Add collision
    engine->setRelation(_playersGroups, _projectilesGroups, Player::hurtProjectile);
}

Game::~Game()
{
    // Destroy all entities
    _players.clear();
    _projectiles.clear();
}

void Game::update(Event event)
{
    switch (event) {
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
        default:
            break;
    }
}