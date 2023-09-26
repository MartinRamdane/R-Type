#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include "GameEngine/JsonParser.hpp"

int main()
{
    // Ler o JSON do arquivo
    JsonParser config;
    nlohmann::json jsonData = config.readFile("../src/GameEngine/r-type/assets/Setup.json");

    std::string title = config.get<std::string>(jsonData, "Game.Title");
    // int width = config.get<int>(jsonData, "Game.Width");
    // int height = config.get<int>(jsonData, "Game.Height");

    std::cout << "Title: " << title << std::endl;
    // std::cout << "Width: " << width << std::endl;
    // std::cout << "Height: " << height << std::endl;

    return 0;
}
