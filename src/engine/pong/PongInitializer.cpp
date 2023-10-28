/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** PongInitializer
*/

#include "PongInitializer.hpp"
#include "Pong.hpp"

PongInitializer::PongInitializer(Pong* game) {
    _game = game;
}

PongInitializer::~PongInitializer() {}

#include <typeinfo>

void PongInitializer::loadLevel(int currentLevel) {
    nlohmann::json levelsFile = JsonParser::readFile("pongLevels.json");
    nlohmann::json level = levelsFile["Level-" + std::to_string(currentLevel)];

    for (const auto& [key, value] : level.items()) {
        if (value.contains("Config")) {
            loadConfig(value["Config"]);
            createEntity(value["Count"], value["Positions"]);
        }
    }
}

void PongInitializer::loadConfig(std::string config) {
    _info.name = config;
    _info.assetFile = _game->getAssets()[config]();
    _info.spriteConfigJsonFileName = "pongConfig.json";
    _info.spriteConfigJsonObjectName = config;
}

void PongInitializer::createEntity(int cout, nlohmann::json positions) {
    for (int i = 0; i < cout; i++) {
        _info.x = positions[i]["X"];
        _info.y = positions[i]["Y"];
        _game->createEntity(_info);
    }
    _info = {};
}