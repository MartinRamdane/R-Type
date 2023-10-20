/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LevelInitializer
*/

#pragma once

#include "../IGame.hpp"
#include "../IEntity.hpp"
#include "../../global/JsonParser.hpp"

class Game;

class LevelInitializer
{
public:
    LevelInitializer(IGame *game);
    ~LevelInitializer();
    void loadConfig(nlohmann::json spriteConfig);
    void createEnemy(int count, auto positions);

protected:
private:
    Game *_game;
    IEntity::EntityInfo _info;
};
