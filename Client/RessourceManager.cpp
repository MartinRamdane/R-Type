/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RessourceManager.cpp
*/

#include "RessourceManager.hpp"

RessourceManager::RessourceManager()
{
    this->_textures["../assets/cenario/background.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/cenario/background.png"]->loadFromFile("../assets/cenario/background.png");
    this->_textures["../assets/players/Spaceship1.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/players/Spaceship1.png"]->loadFromFile("../assets/players/Spaceship1.png");
    this->_textures["../assets/players/Spaceship2.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/players/Spaceship2.png"]->loadFromFile("../assets/players/Spaceship2.png");
    this->_textures["../assets/players/Spaceship3.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/players/Spaceship3.png"]->loadFromFile("../assets/players/Spaceship3.png");
    this->_textures["../assets/players/Spaceship4.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/players/Spaceship4.png"]->loadFromFile("../assets/players/Spaceship4.png");
    this->_textures["../assets/players/Spaceship5.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/players/Spaceship5.png"]->loadFromFile("../assets/players/Spaceship5.png");
}

std::map<std::string, std::shared_ptr<sf::Texture>> RessourceManager::getTextures() const
{
    return _textures;
}