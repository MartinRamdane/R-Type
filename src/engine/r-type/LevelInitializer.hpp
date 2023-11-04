/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LevelInitializer
*/

#pragma once

#include "../../global/JsonParser.hpp"
#include "../IEntity.hpp"
#include "../IGame.hpp"

class RType;

class LevelInitializer {
   public:
    LevelInitializer(IGame* game);
    ~LevelInitializer();
    void loadLevel(int currentLevel);
    void loadConfig(nlohmann::json spriteConfig);
    void createEnemy(int cout, nlohmann::json positions);
    void createBoss(int cout, nlohmann::json positions);
    void createBackground();
    void createDropper(int cout, nlohmann::json positions);
    void createWall(int cout, nlohmann::json positions);

   protected:
   private:
    RType* _game;
    IEntity::EntityInfo _info;
};
