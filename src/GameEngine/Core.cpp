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
    Protocol::transformWindowCreateToProtocol(_engine->getWindowTitle(), _engine->getWindowWidth(), _engine->getWindowHeight());
    _game = std::make_shared<Game>(_engine);
}

Core::~Core()
{
}

std::vector<std::string> Core::mainLoop(std::string event)
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
            // for (auto line : protocol)
            //     std::cout << line << std::endl;
            // send protocol to client
            // return protocol;
        }
    }
    return {};
}