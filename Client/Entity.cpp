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

void Entity::setSprite()
{
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

void Entity::setSpriteScale(const sf::Vector2f &scale)
{
    _sprite.setScale(scale);
}

void Entity::setSpriteOrigin()
{
    // sf::Vector2u textureSize = this->_texture->getSize();
    // _sprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
    ;
}

void Entity::setSpriteRotation(const float &rotation)
{
    _sprite.setRotation(rotation);
}

void Entity::animateSprite(sf::Clock clock)
{
    float size = _texture->getSize().x / _nbRect;
    sf::IntRect rect = _sprite.getTextureRect();
    if (clock.getElapsedTime().asMilliseconds() > 500)
    {
        sleep(sf::milliseconds(100));
        if (rect.left == size * (_nbRect - 1))
            rect.left = 0;
        else
            rect.left += size;
        _sprite.setTextureRect(rect);
        clock.restart();
    }

}

void Entity::setRect(int nb)
{
    _nbRect = nb;
    float size = _texture->getSize().x / nb;
    sf::IntRect rect(0, 0, size, _texture->getSize().y);
    _sprite.setTextureRect(rect);
}