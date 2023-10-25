/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** PongInitializer
*/

#pragma once

#include "../IEntity.hpp"
#include "../../global/JsonParser.hpp"

class Pong;

class PongInitializer
{
public:
    PongInitializer(Pong *game);
    ~PongInitializer();
    void loadLevel(int currentLevel);
    void loadConfig(std::string config);
    void createEntity(int cout, nlohmann::json positions);

protected:
private:
    Pong *_game;
    IEntity::EntityInfo _info;
    int _currentLevel = 1;
};
