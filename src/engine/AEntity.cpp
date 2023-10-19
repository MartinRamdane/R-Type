/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** AEntity
*/

#include "AEntity.hpp"

AEntity::AEntity(std::string path, float x, float y, int id, std::string spriteConfigJsonPath, std::string spriteConfigJsonObjectName, float scaleX, float scaleY)
{
    _path = path;
    _x = x;
    _y = y;
    _scaleX = scaleX;
    _scaleY = scaleY;
    _speed = 1;
    _id = id;
    _oldX = x;
    _oldY = y;
    _created = false;
    _isDead = false;
    _damage = 10;
    _life = 100;
    _flip = false;
    _spriteConfigJsonPath = spriteConfigJsonPath;
    _spriteConfigJsonObjectName = spriteConfigJsonObjectName;
    _direction = RIGHT;
}

AEntity::~AEntity()
{
}

void AEntity::setPosition(float x, float y)
{
    setOldPosition(_x, _y);
    _x = x;
    _y = y;
}

void AEntity::update()
{
    if (_x != _oldX || _y != _oldY)
        setOldPosition(_x, _y);
}

std::tuple<float, float> AEntity::getPosition() const
{
    return std::make_tuple(_x, _y);
}

void AEntity::setScale(float x, float y)
{
    _scaleX = x;
    _scaleY = y;
}

std::tuple<float, float> AEntity::getScale() const
{
    return std::make_tuple(_scaleX, _scaleY);
}

std::string AEntity::getPath() const
{
    return _path;
}

void AEntity::setPath(std::string path)
{
    _path = path;
}

void AEntity::setSpeed(float speed)
{
    _speed = speed;
}

float AEntity::getSpeed() const
{
    return _speed;
}

void AEntity::setOldPosition(float x, float y)
{
    _oldX = x;
    _oldY = y;
}

std::tuple<float, float> AEntity::getOldPosition() const
{
    return std::make_tuple(_oldX, _oldY);
}

int AEntity::getId() const
{
    return _id;
}

bool AEntity::isCreated() const
{
    return _created;
}

void AEntity::setCreated(bool created)
{
    _created = created;
}

bool AEntity::isDead() const
{
    return _isDead;
}

void AEntity::kill()
{
    _isDead = true;
}

void AEntity::setDamage(int damage)
{
    _damage = damage;
}

int AEntity::getDamage() const
{
    return _damage;
}

void AEntity::takeDamage(int damage)
{
    _life -= damage;
    if (_life <= 0)
        _isDead = true;
}

std::string AEntity::getSpriteJsonFileName() const
{
    return _spriteConfigJsonPath;
}

std::string AEntity::getSpriteConfigJsonObjectName() const
{
    return _spriteConfigJsonObjectName;
}

void AEntity::setRadius(float radius)
{
    _radius = radius;
}

float AEntity::getRadius() const
{
    return _radius;
}

void AEntity::flip()
{
    _flip = true;
    if (_direction == RIGHT)
        _direction = LEFT;
    else
        _direction = RIGHT;
}

bool AEntity::isFlip() const
{
    return _flip;
}

void AEntity::setFlip(bool flip)
{
    _flip = flip;
}

AEntity::Direction AEntity::getDirection() const
{
    return _direction;
}

void AEntity::setLife(int life)
{
    _life = life;
}
