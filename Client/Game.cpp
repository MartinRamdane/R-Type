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
    _view = sf::View(sf::FloatRect(0, 0, 850, 478));
    _ressourceManager = RessourceManager();
    _parser = Parser();
    _parser.parseMessage("ecreate 1 0 0 background.png 0 1 1 1", _ressourceManager);
    _parser.parseMessage("ecreate 2 100 100 Spaceship1.png 0 1 1 5", _ressourceManager);
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
                animate();
                break;
            case sf::Keyboard::Down:
                // send down
                break;
            case sf::Keyboard::Space:
                // send space
                break;
            case sf::Keyboard::Escape:
                _window.close();
                break;
            default:
                break;
            }
        }
    }
}

void Game::animate()
{
    std::map<int, Entity>::iterator it = _parser._entities.begin();
    while (it != _parser._entities.end())
    {
        // add condition for animation
        it->second.animateSprite();
        it++;
    }
}

void Game::draw()
{
    std::map<int, Entity>::iterator it = _parser._entities.begin();
    while (it != _parser._entities.end())
    {
        _window.draw(it->second.getSprite());
        it++;
    }
}

void Game::update()
{
    _window.clear();
    // animate();
    draw();
    _window.setView(_view);
    _window.display();
}
