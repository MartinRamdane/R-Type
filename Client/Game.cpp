/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.cpp
*/

#include "Game.hpp"

Game::Game()
{
    _window.create(sf::VideoMode(1920, 1080), "R-TYPE");
    _window.setFramerateLimit(60);
    _view = _window.getDefaultView();
}

Game::~Game()
{
}

void Game::run(std::map<int, Entity> entities)
{
    while (_window.isOpen())
    {
        updateEntities(entities);
        handleEvent();
        update();
    }
}

void Game::handleEvent()
{
    while (_window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
            _window.close();
    }
}

void Game::update()
{
    std::map<int, Entity>::iterator it = _entities.begin();
    while (it != _entities.end())
    {
        // it->second.animateSprite(1, 100, 100, clock);
        _window.draw(it->second.getSprite());
        it++;
    }
    _window.display();
}

void Game::updateEntities(std::map<int, Entity> entities)
{
    _entities = entities;
}