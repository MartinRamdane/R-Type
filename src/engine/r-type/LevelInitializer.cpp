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
    _game = static_cast<Game *>(game);

    int lastId = _game->getCurrentId();
    int currLevel = _game->getCurrentLevel();
    JsonParser parser;
    nlohmann::json levelsFile = JsonParser::readFile("rTypeLevels.json");
    nlohmann::json level = levelsFile["Level-" + std::to_string(currLevel)];

    for (const auto &[key, value] : level.items())
    {
        std::cout << key << " " << value << std::endl;
        std::cout << "---------------------" << std::endl;
        if (value.contains("Config"))
        {
            nlohmann::json config = JsonParser::readFile(value["Config"]);
            if (config["Type"] == "Enemy")
            {
                createEnemy(config);
                exit(0);
            }
        }
    }
}

LevelInitializer::~LevelInitializer()
{
}

void LevelInitializer::createEnemy(nlohmann::json spriteConfig)
{
    // Enemyconfig.
}
