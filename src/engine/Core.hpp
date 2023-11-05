/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Core
*/

#pragma once
#include "../server/ThreadSafeQueue.hpp"
#include "Engine.hpp"
#include "Protocol.hpp"
#include "pong/Pong.hpp"
#include "r-type/RType.hpp"

class Core {
   public:
    Core(std::string gameName);
    ~Core();

    std::vector<std::string> mainLoop(ThreadSafeQueue<Event>& events);
    std::shared_ptr<Engine> getEngine() { return _engine; }
    std::vector<std::string> getCreateEntities();
    std::vector<std::string> getAllEntitiesToCreate();
    bool isReset() { return _game->isReset(); }
    void setReset(bool reset) { _game->setReset(reset); }
   private:
    std::shared_ptr<Engine> _engine;
    std::unique_ptr<IGame> _game;
    std::chrono::high_resolution_clock::time_point _lastFrameTime;
    bool loopRunning = false;
};