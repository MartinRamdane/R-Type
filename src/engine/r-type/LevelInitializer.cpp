/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** LevelInitializer
*/

#include "LevelInitializer.hpp"
#include "Game.hpp"

LevelInitializer::LevelInitializer(IGame *game)
{
    _game = dynamic_cast<Game *>(game);
}

LevelInitializer::~LevelInitializer()
{
}

#include <typeinfo>

void LevelInitializer::loadLevel(int currentLevel)
{
    nlohmann::json levelsFile = JsonParser::readFile("rTypeLevels.json");
    nlohmann::json level = levelsFile["Level-" + std::to_string(currentLevel)];

    for (const auto &[key, value] : level.items())
    {
        if (value.contains("Config"))
        {
            nlohmann::json config = JsonParser::readFile(value["Config"]);
            loadConfig(config);
            if (config["Type"] == "Enemy")
            {
                createEnemy(value["Count"], value["Positions"]);
            }
        }
        else
        {
            createBackground();
        }
    }
}

void LevelInitializer::loadConfig(nlohmann::json spriteConfig)
{
    _info.name = spriteConfig["Name"];
    _info.assetFile = _game->getAssets()[spriteConfig["Name"]]();
    _info.spriteConfigJsonFileName = "rTypeConfig.json";
    _info.spriteConfigJsonObjectName = spriteConfig["Name"];
    _info.projectileSpeed = spriteConfig["ProjectileSpeed"];
    _info.projectileType = spriteConfig["ProjectileType"];
    _info.movementType = spriteConfig["MovementType"];
    _info.fireRate = spriteConfig["FireRate"];
    _info.life = spriteConfig["Life"];
    _info.damage = spriteConfig["Damage"];
    _info.speed = spriteConfig["Speed"];
}

void LevelInitializer::createEnemy(int cout, nlohmann::json positions)
{
    for (int i = 0; i < cout; i++)
    {
        _info.id = _game->getCurrentId();
        _info.x = positions[i]["X"];
        _info.y = positions[i]["Y"];
        _game->createEnemy(_info);
        _game->setCurrentId(_info.id + 1);
    }
    _info = {};
}

void LevelInitializer::createBackground()
{
    std::cout << "ID background: " << _game->getCurrentId() << std::endl;
    _info.id = _game->getCurrentId();
    _info.name = "Background";
    _info.assetFile = _game->getAssets()["Background"]();
    _info.spriteConfigJsonFileName = "rTypeConfig.json";
    _info.spriteConfigJsonObjectName = "Background";
    _info.x = 425;
    _info.y = 239;
    _game->createBackground(_info);
    _game->setCurrentId(_info.id + 1);
    _info = {};
}
