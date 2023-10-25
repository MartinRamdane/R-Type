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

Entity::~Entity()
{
}

void Entity::setTexture(const std::string& path)
{
    _texture->loadFromFile(path);
    _sprite.setTexture(*_texture);
}

void Entity::setSpriteScale(float scaleX, float scaleY);
{
    _sprite.setScale(sf::Vector2f(scaleX, scaleY));
}

void Entity::setSpritePosition(float x, float y)
{
    _oldPosY = _sprite.getPosition().y;
    _sprite.setPosition(sf::Vector2f(x, y));
}


std::tuple<float, float> Entity::getSpritePosition() const;
{
    return std::make_tuple<float, float>(_sprite.getPosition().x, _sprite.getPosition().y);
}

void Entity::setSpriteRotation(const float &angle)
{
    _sprite.setRotation(angle);
}

void Entity::setRect(int nb, int initRect)
{
    _nbRect = nb;
    _initRect = initRect;
    float size = _texture->getSize().x / nb;
    sf::IntRect rect(0, 0, size, _texture->getSize().y);
    rect.left = size * initRect;
    _sprite.setTextureRect(rect);
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
                rect.left = size * _initRect;
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
            if (rect.left == size * (_nbRect - 1) || rect.left < size * _initRect)
                rect.left = size * _initRect - size;
            else
                rect.left += size;
        }
        else if (ei == 4)
        {
            if (rect.left >= size * (_nbRect - 1))
                rect.left = size * _initRect;
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
        if (rect.left > size * _initRect)
            rect.left -= size;
        else if (rect.left < size * _initRect)
            rect.left += size;

        _sprite.setTextureRect(rect);
        _clock.restart();
    }
}

void Entity::setTextString(std::string str)
{
    _text.setString(str);
}

void Entity::setType(int type)
{
    _type = type;
}

void Entity::setTextInfo(int size, std::string color)
{
    _text.setCharacterSize(size);
    _text.setFillColor(getColor(color));
}

void Entity::setSpeed(float speed)
{
    _speed = speed;
}

void Entity::setNextPos(float x, float y)
{
    _nextPos = sf::Vector2f(x, y);
}

void Entity::setDirection(std::string direction)
{
    _direction = direction;
}

void Entity::update()
{
    sf::Vector2f pos = _sprite.getPosition();
    if (pos.x == _nextPos.x && pos.y == _nextPos.y)
    {
        if (_event_form == "event")
            setInitPos();
        return;
    }
    if (pos.x < _nextPos.x)
        pos.x += _speed;
    else if (pos.x > _nextPos.x)
        pos.x -= _speed;
    if (pos.y < _nextPos.y)
    {
        pos.y += _speed;
        if (_event_form == "event")
            animateSprite(2, 100);
    }
    else if (pos.y > _nextPos.y)
    {
        pos.y -= _speed;
        if (_event_form == "event")
            animateSprite(1, 100);
    }
    if (pos.x + _speed > _nextPos.x && pos.x - _speed < _nextPos.x)
        pos.x = _nextPos.x;
    if (pos.y + _speed > _nextPos.y && pos.y - _speed < _nextPos.y)
        pos.y = _nextPos.y;
    _sprite.setPosition(pos);
}

void Entity::flip()
{
    auto scale = _sprite.getScale();
    scale.x *= -1;
    _sprite.setScale(scale);
}

void Entity::setHit(bool touch)
{
    _isHit = touch;
}

bool Entity::isDead() const
{
    if (_event_form == "once")
    {
        float size = _texture->getSize().x / _nbRect;
        sf::IntRect rect = _sprite.getTextureRect();
        if (rect.left == size * (_nbRect - 1) || rect.left < size * _initRect)
            return true;
    }
    return false;
}

void Entity::setSpriteOrigin()
{
    sf::Vector2f size = sf::Vector2f(_texture->getSize().x / _nbRect, _texture->getSize().y);
    _sprite.setOrigin(size.x / 2, size.y / 2);
}

int Entity::getRect() const
{
    return _nbRect;
}


void Entity::setFont()
{
    _text.setFont(_font);
}



sf::Color Entity::getColor(std::string color)
{
    if (color == "red")
        return sf::Color::Red;
    if (color == "blue")
        return sf::Color::Blue;
    if (color == "green")
        return sf::Color::Green;
    if (color == "white")
        return sf::Color::White;
    if (color == "black")
        return sf::Color::Black;
    if (color == "yellow")
        return sf::Color::Yellow;
    if (color == "magenta")
        return sf::Color::Magenta;
    if (color == "cyan")
        return sf::Color::Cyan;
    return sf::Color::White;
}
