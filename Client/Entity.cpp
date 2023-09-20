/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Sprite.cpp
*/

#include "Entity.hpp"

void Entity::setTexture(const std::string &path)
{
    if (!_texture->loadFromFile(path))
        std::cerr << "Error: could not load texture" << std::endl;
}

void Entity::setSprite(const std::string &path)
{
    setTexture(path);
    _sprite.setTexture(*_texture);
}

sf::Sprite Entity::getSprite() const
{
    return _sprite;
}

sf::Texture Entity::getTexture() const
{
    return *_texture;
}

void Entity::setSpritePosition(const sf::Vector2f &pos)
{
    _sprite.setPosition(pos);
}

sf::Vector2f Entity::getSpritePosition() const
{
    return _sprite.getPosition();
}

void Entity::setSpriteScaleToWindow(const sf::RenderWindow &window)
{
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = _texture->getSize();

    // Calculate the scaling factors for width and height
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    // Set the scale of the sprite to fit the window
    _sprite.setScale(scaleX, scaleY);
}

void Entity::setSpriteScale(const sf::Vector2f &scale)
{
    _sprite.setScale(scale);
}

void Entity::setSpriteOrigin()
{
    sf::Vector2u textureSize = _texture->getSize();
    _sprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
}

void Entity::setSpriteRotation(const float &rotation)
{
    _sprite.setRotation(rotation);
}