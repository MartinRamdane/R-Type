/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Core
*/

#pragma once
#include "Engine.hpp"
#include "IGame.hpp"
#include "Protocol.hpp"

class Core
{
public:
    Core();
    ~Core();

    void mainLoop(std::string event);
    std::shared_ptr<Engine> getEngine() { return _engine; }
    std::shared_ptr<IGame> getGame() { return _game; }

private:
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<IGame> _game;
};