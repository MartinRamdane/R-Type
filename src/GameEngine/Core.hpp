/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Core
*/

#pragma once
#include <memory>
#include "Engine.hpp"
#include "Game.hpp"

class Core
{
public:
    Core();
    ~Core();

    void mainLoop();

private:
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<Game> _game;
};
