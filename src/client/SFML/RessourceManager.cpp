/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RessourceManager.cpp
*/

#include "RessourceManager.hpp"

RessourceManager::RessourceManager() {
    std::string directory = "assets";
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            std::string key = entry.path().stem().string();
            key = key + ".png";
            std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
            if (texture->loadFromFile(filePath))
                _textures[key] = texture;
            else
                std::cerr << "Impossible de charger la texture : " << key << std::endl;
        }
    }
}

std::map<std::string, std::shared_ptr<sf::Texture>> RessourceManager::getTextures() const {
    return _textures;
}