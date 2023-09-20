/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Sprite.hpp
*/

#pragma once
// #include "include.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

class Entity
{
public:
    Entity(){};
    ~Entity(){};
    void setTexture(const std::string &path);
    void setSprite(const std::string &path);
    void setSpriteScaleToWindow(const sf::RenderWindow &window);
    void setSpriteScale(const sf::Vector2f &scale);
    sf::Sprite getSprite() const;
    sf::Texture getTexture() const;
    void setSpritePosition(const sf::Vector2f &pos);
    sf::Vector2f getSpritePosition() const;
    void setSpriteOrigin();

public:
    sf::Sprite _sprite;
    sf::Texture _texture;
};
