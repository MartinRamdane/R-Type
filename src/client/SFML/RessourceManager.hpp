/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RessourceManager.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <string>

class RessourceManager {
   public:
    RessourceManager();
    ~RessourceManager(){};
    std::map<std::string, std::shared_ptr<sf::Texture>> getTextures() const;

   public:
    std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
};