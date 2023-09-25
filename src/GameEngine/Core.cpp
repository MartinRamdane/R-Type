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
    // auto entities = _engine->getEntities();
    // std::vector<std::string> protocol = Protocol::transformEntityInitToProtocol(entities);
    // for (auto line : protocol)
    //     std::cout << line << std::endl;
    // send protocol to client
}

std::vector<std::string> Core::getEntitiesProtocol()
{
    auto entities = _engine->getEntities();
    std::vector<std::string> protocol = Protocol::transformEntityInitToProtocol(entities);
    return protocol;
}

Core::~Core()
{
}

std::vector<std::string> Core::mainLoop()
{
    // while (_engine->isRunning())
    // {
    if (_engine->frameRateControl())
    {
        // std::cout << "update" << std::endl;
        _engine->update();
        _game->update(Game::Event::UNKNOWN);
        auto entities = _engine->getEntities();
        std::vector<std::string> protocol = Protocol::transformEntityChangeToProtocol(entities);
        // for (auto line : protocol)
        //     std::cout << line << std::endl;
        // send protocol to client
        return protocol;
    }
    // }
}
