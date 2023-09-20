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
    auto entities = _engine->getEntities();
    std::vector<std::string> protocol = Protocol::transformEntityInitToProtocol(entities);
    for (auto line : protocol)
        std::cout << line << std::endl;
}

Core::~Core()
{
}

void Core::mainLoop()
{
    while (_engine->isRunning())
    {
        if (_engine->frameRateControl())
        {
            _engine->update();
            _game->update(Game::Event::UNKNOWN);
        }
    }
}
