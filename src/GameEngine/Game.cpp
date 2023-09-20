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
    _playersGroups = std::make_shared<EntityType<IEntity>>(16);
    _projectilesGroups = std::make_shared<EntityType<IEntity>>(4);
    _players.push_back(std::make_shared<Player>("./assets/ship.png", 0, 50, _lastId++));
    _playersGroups->insert(_players[0]);
    _projectiles.push_back(std::make_shared<Projectile>("./assets/ship.png", 25, 50, _lastId++));
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
    // Update the game
}