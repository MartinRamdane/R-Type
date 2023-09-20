/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Core
*/

#pragma once
#include "Engine.hpp"
#include "Game.hpp"

class Core
{
public:
    enum Event
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE,
        ENTER,
        ESCAPE,
        UNKNOWN
    };
    Core();
    ~Core();

    void mainLoop();

private:
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<Game> _game;
};
