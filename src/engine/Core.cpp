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

std::vector<std::string> Core::mainLoop(ThreadSafeQueue<Event> &events)
{
    if (_engine->frameRateControl())
    {
        // get events
        _engine->update();
        _game->update(events);
        auto entities = _engine->getEntities();
        std::vector<std::string> protocol = Protocol::transformEntitiesToProtocol(entities);
        return protocol;
    }
    return {};
}

std::vector<std::string> Core::getAllEntitiesToCreate()
{
    auto entities = _engine->getEntities();
    std::vector<std::string> protocol = Protocol::transformAllEntitiesToCreate(entities);
    return protocol;
}