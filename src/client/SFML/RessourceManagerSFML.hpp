/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RessourceManagerSFML.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <string>

class RessourceManagerSFML {
   public:
    RessourceManagerSFML();
    ~RessourceManagerSFML();
    std::map<std::string, std::shared_ptr<sf::Texture>> getTextures() const;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> getSounds() const;

   public:
    std::map<std::string, std::shared_ptr<sf::Texture>> _textures;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> _sounds;
};