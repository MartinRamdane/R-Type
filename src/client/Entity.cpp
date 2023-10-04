/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Sprite.cpp
*/

#include "Entity.hpp"

Entity::Entity()
{
    _clock.restart();
}

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
    _oldPosY = _sprite.getPosition().y;
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
    std::cout << "texture size: " << _texture->getSize().x << _texture->getSize().y << std::endl;
    std::cout << "nb rect: " << _nbRect << std::endl;
    sf::Vector2f size = sf::Vector2f(_texture->getSize().x / _nbRect, _texture->getSize().y);
    _sprite.setOrigin(size.x / 2, size.y / 2);
}

void Entity::setSpriteRotation(const float &rotation)
{
    _sprite.setRotation(rotation);
}

void Entity::animateSprite(const int ei, const int framerate)
{
    float size = _texture->getSize().x / _nbRect;
    sf::IntRect rect = _sprite.getTextureRect();
    if (_clock.getElapsedTime().asMilliseconds() > framerate)
    {
        if (ei == 0)
        {
            if (rect.left == size * (_nbRect - 1))
                rect.left = size * _init_rect;
            else
                rect.left += size;
        }
        else if (ei == 1)
        {
            if (rect.left != size * (_nbRect - 1))
                rect.left += size;
        }
        else if (ei == 2)
        {
            if (rect.left != 0)
                rect.left -= size;
        }
        else if (ei == 3)
        {
            if (rect.left == size * (_nbRect - 1) || rect.left < size * _init_rect)
                rect.left = size * _init_rect - size;
            else
                rect.left += size;
        }
        else if (ei == 4)
        {
            if (rect.left >= size * (_nbRect - 1))
                rect.left = size * _init_rect;
            else
                rect.left += 1;
        }
        _sprite.setTextureRect(rect);
        _clock.restart();
    }
}

void Entity::setInitPos()
{
    float size = _texture->getSize().x / _nbRect;
    sf::IntRect rect = _sprite.getTextureRect();
    if (_clock.getElapsedTime().asMilliseconds() > 100)
    {
        if (rect.left > size * _init_rect)
            rect.left -= size;
        else if (rect.left < size * _init_rect)
            rect.left += size;

        _sprite.setTextureRect(rect);
        _clock.restart();
    }
}

void Entity::setRect(int nb, int init_rect)
{
    _nbRect = nb;
    _init_rect = init_rect;
    float size = _texture->getSize().x / nb;
    sf::IntRect rect(0, 0, size, _texture->getSize().y);
    rect.left = size * init_rect;
    _sprite.setTextureRect(rect);
}

int Entity::getRect() const
{
    return _nbRect;
}