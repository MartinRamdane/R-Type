/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Character
*/

#include "Character.hpp"

Character::Character(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY, float speed, int nbSprite)
{
    _path = path;
    _x = x;
    _y = y;
    _angle = angle;
    _scaleX = scaleX;
    _scaleY = scaleY;
    _speed = speed;
    _id = id;
    _oldX = x;
    _oldY = y;
    _nbSprite = nbSprite;
    _created = false;
}

Character::~Character()
{
}

void Character::setPosition(float x, float y)
{
    setOldPosition(_x, _y);
    _x = x;
    _y = y;
}

void Character::setRotation(float angle)
{
    _angle = angle;
}

void Character::move(float x, float y)
{
    setOldPosition(_x, _y);
    _x += x;
    _y += y;
}

void Character::rotate(float angle)
{
    _angle += angle;
}

void Character::update()
{
}

std::tuple<float, float> Character::getPosition() const
{
    return std::make_tuple(_x, _y);
}

float Character::getRotation() const
{
    return _angle;
}

void Character::setScale(float x, float y)
{
    _scaleX = x;
    _scaleY = y;
}

std::tuple<float, float> Character::getScale() const
{
    return std::make_tuple(_scaleX, _scaleY);
}

std::string Character::getPath() const
{
    return _path;
}

void Character::setPath(std::string path)
{
    _path = path;
}

void Character::setSpeed(float speed)
{
    _speed = speed;
}

float Character::getSpeed() const
{
    return _speed;
}

void Character::setOldPosition(float x, float y)
{
    _oldX = x;
    _oldY = y;
}

std::tuple<float, float> Character::getOldPosition() const
{
    return std::make_tuple(_oldX, _oldY);
}

int Character::getId() const
{
    return _id;
}

int Character::getNbSprite() const
{
    return _nbSprite;
}

bool Character::isCreated() const
{
    return _created;
}

void Character::setCreated(bool created)
{
    _created = created;
}