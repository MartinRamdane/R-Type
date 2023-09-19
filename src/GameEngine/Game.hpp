/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game
*/

#pragma once
#include "Engine.hpp"

class Game
{
public:
    Game(std::shared_ptr<Engine> &engine);
    ~Game();

    void update();

private:
    std::shared_ptr<Engine> _engine;
};
