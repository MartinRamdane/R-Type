/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Core
*/

#include "Core.hpp"

Core::Core(std::string gameName) {
    _engine = std::make_shared<Engine>();
    std::string protocol = Protocol::transformWindowCreateToProtocol(
        _engine->getWindowTitle(), _engine->getWindowWidth(),
        _engine->getWindowHeight());
    // send protocol to client
    if (gameName == "pong")
        _game = std::make_unique<Pong>(_engine);
    else
        _game = std::make_unique<RType>(_engine);
}

Core::~Core() {
    while (loopRunning) {
        std::cout << "loop is running" << std::endl;
    }
}

std::vector<std::string> Core::mainLoop(ThreadSafeQueue<Event>& events) {
    loopRunning = true;
    if (_engine->frameRateControl()) {
        // get events
        _engine->update();
        _game->update(events);
        if (_lastFrameTime.time_since_epoch().count() == 0)
            _lastFrameTime = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - _lastFrameTime)
                .count() > 10) {
            _lastFrameTime = std::chrono::high_resolution_clock::now();
            auto entities = _engine->getEntities();
            std::vector<std::string> protocol =
                Protocol::transformEntitiesToProtocol(entities);
            loopRunning = false;
            return protocol;
        }
    }
    loopRunning = false;
    return {};
}

std::vector<std::string> Core::getAllEntitiesToCreate() {
    auto entities = _engine->getEntities();
    std::vector<std::string> protocol =
        Protocol::transformAllEntitiesToCreate(entities);
    return protocol;
}

std::vector<std::string> Core::getCreateEntities() {
    std::vector<std::string> entitiesList;
    auto entities = _engine->getEntities();
    for (auto entityType : entities) {
        for (auto entity : entityType->getEntities()) {
            entitiesList.push_back(
                Protocol::transformEntityCreateToProtocol(entity));
        }
    }
    return entitiesList;
}