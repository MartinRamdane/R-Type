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

void Core::mainLoop(ThreadSafeQueue<Event> &events, UDPServer *server)
{
    if (_engine->frameRateControl())
    {
        // get events
        _engine->update();
        _game->update(events);
        if (_lastFrameTime.time_since_epoch().count() == 0)
            _lastFrameTime = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _lastFrameTime).count() > 10)
        {
            _lastFrameTime = std::chrono::high_resolution_clock::now();
            auto entities = _engine->getEntities();
            Protocol::transformEntitiesToProtocol(entities, server);
        }
    }
}

std::vector<std::string> Core::getAllEntitiesToCreate()
{
    auto entities = _engine->getEntities();
    std::vector<std::string> protocol = Protocol::transformAllEntitiesToCreate(entities);
    return protocol;
}