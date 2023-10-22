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
    void loadLevel(int currentLevel);
    void loadConfig(nlohmann::json spriteConfig);
    // void createEnemy(int count, auto positions);
    void createEnemy(int count);
    void createBackground();

protected:
private:
    Game *_game;
    IEntity::EntityInfo _info;
    int _currentLevel = 1;
};
