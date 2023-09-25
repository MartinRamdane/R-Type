/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Core
*/

#pragma once
#include "Engine.hpp"
#include "r-type/Game.hpp"
#include "Protocol.hpp"

class Core
{
public:
    Core();
    ~Core();

    std::vector<std::string> mainLoop(std::string event);

private:
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<Game> _game;
};