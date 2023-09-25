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
    _ressourceManager = RessourceManager();
    _parser = Parser();
    _parser.parseMessage("ecreate 1 100 100 Spaceship1.png 0 1 1 5", _ressourceManager);
}

Game::~Game()
{
}

void Game::run()
{
    while (_window.isOpen())
    {
        // getinfos -> appel de parseMessage
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
        if (_event.type == sf::Event::KeyPressed)
        {
            switch (_event.key.code)
            {
            case sf::Keyboard::Left:
                // send left;
                break;
            case sf::Keyboard::Right:
                // send right
                break;
            case sf::Keyboard::Up:
                // send up
                break;
            case sf::Keyboard::Down:
                // send down
                break;
            default:
                break;
            }
        }
    }
}

void Game::update()
{
    _window.clear();
    std::map<int, Entity>::iterator it = _parser._entities.begin();
    while (it != _parser._entities.end())
    {
        it->second.animateSprite(_clock);
        _window.draw(it->second.getSprite());
        it++;
    }
    _window.setView(_view);
    _window.display();
}
