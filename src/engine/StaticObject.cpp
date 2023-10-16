/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** StaticObject
*/

#include "StaticObject.hpp"

StaticObject::StaticObject(std::string path, float x, float y, int id, std::string spriteConfigJsonPath, std::string spriteConfigJsonObjectName, float angle, float scaleX, float scaleY, int nbSprite)
{
    _path = path;
    _x = x;
    _y = y;
    _angle = angle;
    _scaleX = scaleX;
    _scaleY = scaleY;
    _speed = 0;
    _id = id;
    _oldX = x;
    _oldY = y;
    _nbSprite = nbSprite;
    _created = false;
    _isDead = false;
    _spriteConfigJsonPath = spriteConfigJsonPath;
    _spriteConfigJsonObjectName = spriteConfigJsonObjectName;
}

StaticObject::~StaticObject()
{
}

void StaticObject::setPosition(float x, float y)
{
    setOldPosition(_x, _y);
    _x = x;
    _y = y;
}

void StaticObject::setRotation(float angle)
{
    _angle = angle;
}

void StaticObject::move(float x, float y)
{
    if ((_x + x * _speed) > Engine::instance->getWindowWidth() - _radius || (_x + x * _speed) < 0 + _radius || (_y + y * _speed) > Engine::instance->getWindowHeight() - (_radius / 2) || (_y + y * _speed) < 0 + (_radius / 2))
        return;
    setOldPosition(_x, _y);
    _x += x;
    _y += y;
}

void StaticObject::rotate(float angle)
{
    _angle += angle;
}

void StaticObject::update()
{
    if (_x != _oldX || _y != _oldY)
        setOldPosition(_x, _y);
}

std::tuple<float, float> StaticObject::getPosition() const
{
    return std::make_tuple(_x, _y);
}

float StaticObject::getRotation() const
{
    return _angle;
}

void StaticObject::setScale(float x, float y)
{
    _scaleX = x;
    _scaleY = y;
}

std::tuple<float, float> StaticObject::getScale() const
{
    return std::make_tuple(_scaleX, _scaleY);
}

std::string StaticObject::getPath() const
{
    return _path;
}

void StaticObject::setPath(std::string path)
{
    _path = path;
}

void StaticObject::setSpeed(float speed)
{
    _speed = speed;
}

float StaticObject::getSpeed() const
{
    return _speed;
}

void StaticObject::setOldPosition(float x, float y)
{
    _oldX = x;
    _oldY = y;
}

std::tuple<float, float> StaticObject::getOldPosition() const
{
    return std::make_tuple(_oldX, _oldY);
}

int StaticObject::getId() const
{
    return _id;
}

int StaticObject::getNbSprite() const
{
    return _nbSprite;
}

bool StaticObject::isCreated() const
{
    return _created;
}

void StaticObject::setCreated(bool created)
{
    _created = created;
}

bool StaticObject::isDead() const
{
    return _isDead;
}

void StaticObject::setDamage(int damage)
{
    _damage = damage;
}

int StaticObject::getDamage() const
{
    return 0;
}

void StaticObject::takeDamage(int damage)
{
    _life -= damage;
}

std::string StaticObject::getSpriteJsonFileName() const
{
    return _spriteConfigJsonPath;
}

std::string StaticObject::getSpriteConfigJsonObjectName() const
{
    return _spriteConfigJsonObjectName;
}
void StaticObject::kill()
{
    _isDead = true;
}

void StaticObject::setDead(bool dead)
{
    _isDead = dead;
}

void StaticObject::setRadius(float radius)
{
    _radius = radius;
}

float StaticObject::getRadius() const
{
    return _radius;
}
