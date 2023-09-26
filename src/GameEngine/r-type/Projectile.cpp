/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Projectile
*/

#include "Projectile.hpp"

Projectile::Projectile(std::string path, float x, float y, int id, int damage, float angle, float scaleX, float scaleY, float speed, int nbSprite, std::string spriteConfigJsonObjectName)
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
    _isDead = false;
    _damage = damage;
}

Projectile::~Projectile()
{
}

void Projectile::setPosition(float x, float y)
{
    setOldPosition(_x, _y);
    _x = x;
    _y = y;
}

void Projectile::setRotation(float angle)
{
    _angle = angle;
}

void Projectile::move(float x, float y)
{
    setOldPosition(_x, _y);
    _x += x;
    _y += y;
}

void Projectile::rotate(float angle)
{
    _angle += angle;
}

void Projectile::update()
{
    setPosition(_x + _speed, _y);
    if (_x > 850)
        _isDead = true;
}

std::tuple<float, float> Projectile::getPosition() const
{
    return std::make_tuple(_x, _y);
}

float Projectile::getRotation() const
{
    return _angle;
}

void Projectile::setScale(float x, float y)
{
    _scaleX = x;
    _scaleY = y;
}

std::tuple<float, float> Projectile::getScale() const
{
    return std::make_tuple(_scaleX, _scaleY);
}

std::string Projectile::getPath() const
{
    return _path;
}

void Projectile::setPath(std::string path)
{
    _path = path;
}

float Projectile::getSpeed() const
{
    return _speed;
}

void Projectile::setSpeed(float speed)
{
    _speed = speed;
}

void Projectile::setOldPosition(float x, float y)
{
    _oldX = x;
    _oldY = y;
}

std::tuple<float, float> Projectile::getOldPosition() const
{
    return std::make_tuple(_oldX, _oldY);
}

int Projectile::getId() const
{
    return _id;
}

int Projectile::getNbSprite() const
{
    return _nbSprite;
}

bool Projectile::isCreated() const
{
    return _created;
}

void Projectile::setCreated(bool created)
{
    _created = created;
}

bool Projectile::isDead() const
{
    return _isDead;
}

void Projectile::setDamage(int damage)
{
    _damage = damage;
}

int Projectile::getDamage() const
{
    return _damage;
}

void Projectile::takeDamage(int damage)
{
    _damage -= damage;
    if (_damage <= 0)
        _isDead = true;
}

void Projectile::hurtEntity(IEntity &self, IEntity &you)
{
    if (self.isDead() || you.isDead())
        return;
    you.takeDamage(self.getDamage());
    self.takeDamage(100);
    if (you.isDead())
    {
        auto pos = you.getPosition();
        Game::instance->createExplosion(std::get<0>(pos), std::get<1>(pos));
    }
}

std::string Projectile::getSpriteConfigJsonPath() const
{
    return _spriteConfigJsonPath;
}

std::string Projectile::getSpriteConfigJsonObjectName() const
{
    return _spriteConfigJsonObjectName;
}
void Projectile::kill()
{
    _isDead = true;
}
