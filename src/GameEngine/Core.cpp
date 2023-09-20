/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Core
*/

#include "Core.hpp"

Core::Core()
{
    _engine = std::make_shared<Engine>();
    _game = std::make_shared<Game>(_engine);
}

Core::~Core()
{
}

void Core::mainLoop()
{
    while (_engine->isRunning()) {
        _engine->update();
        _game->update(Game::Event::UNKNOWN);
    }
}
