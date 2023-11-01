/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RessourceManagerSFML.cpp
*/

#include "RessourceManagerSFML.hpp"

RessourceManagerSFML::RessourceManagerSFML() {
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
    directory = "sounds";
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            std::string key = entry.path().stem().string();
            key = key + ".ogg";
            std::shared_ptr<sf::SoundBuffer> sound = std::make_shared<sf::SoundBuffer>();
            if (sound->loadFromFile(filePath))
                _sounds[key] = sound;
            else
                std::cerr << "Impossible de charger le son : " << key << std::endl;
        }
    }
}

RessourceManagerSFML::~RessourceManagerSFML() {
    _textures.clear();
}

std::map<std::string, std::shared_ptr<sf::Texture>> RessourceManagerSFML::getTextures() const {
    return _textures;
}

std::map<std::string, std::shared_ptr<sf::SoundBuffer>> RessourceManagerSFML::getSounds() const {
    return _sounds;
}