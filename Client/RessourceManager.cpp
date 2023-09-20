/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RessourceManager.cpp
*/

#include "RessourceManager.hpp"

RessourceManager::RessourceManager()
{
    this->_textures["../assets/background.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/background.png"]->loadFromFile("../assets/background.png");
    this->_textures["../assets/Spaceship1.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/Spaceship1.png"]->loadFromFile("../assets/Spaceship1.png");
    this->_textures["../assets/Spaceship2.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/Spaceship2.png"]->loadFromFile("../assets/Spaceship2.png");
    this->_textures["../assets/Spaceship3.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/Spaceship3.png"]->loadFromFile("../assets/Spaceship3.png");
    this->_textures["../assets/Spaceship4.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/Spaceship4.png"]->loadFromFile("../assets/Spaceship4.png");
    this->_textures["../assets/Spaceship5.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/Spaceship5.png"]->loadFromFile("../assets/Spaceship5.png");
    this->_textures["../assets/EnemyBullet.png"] = std::make_shared<sf::Texture>();
    this->_textures["../assets/EnemyBullet.png"]->loadFromFile("../assets/EnemyBullet.png");
}

std::map<std::string, std::shared_ptr<sf::Texture>> RessourceManager::getTextures() const
{
    return _textures;
}