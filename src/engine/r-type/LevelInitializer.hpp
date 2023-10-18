/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LevelInitializer
*/

#pragma once

#include "../IGame.hpp"
#include "../../global/JsonParser.hpp"

class Game;

class LevelInitializer
{
public:
    LevelInitializer(IGame *game);
    ~LevelInitializer();
    void createEnemy(nlohmann::json spriteConfig);

protected:
private:
    Game *_game;
    Enemy_t _enemy_t;
};
