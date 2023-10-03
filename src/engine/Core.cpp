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
    std::string protocol = Protocol::transformWindowCreateToProtocol(_engine->getWindowTitle(), _engine->getWindowWidth(), _engine->getWindowHeight());
    // send protocol to client
    _game = std::make_shared<Game>(_engine);
}

Core::~Core()
{
}

void Core::mainLoop(std::string event)
{
    while (_engine->isRunning())
    {
        if (_engine->frameRateControl())
        {
            // get events
            _engine->update();
            auto gameEvent = Protocol::transformProtocolToEvent(event);
            _game->update(gameEvent);
            auto entities = _engine->getEntities();
            std::vector<std::string> protocol = Protocol::transformEntitiesToProtocol(entities);
            // send protocol to client
        }
    }
}