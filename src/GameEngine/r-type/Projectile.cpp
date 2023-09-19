/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Projectile
*/

#include "Projectile.hpp"

Projectile::Projectile(std::string path, float x, float y, float angle, float scaleX, float scaleY, float speed)
{
}

Projectile::~Projectile()
{
}

void Projectile::setPosition(float x, float y)
{
    _x = x;
    _y = y;
}

void Projectile::setRotation(float angle)
{
    _angle = angle;
}

void Projectile::move(float x, float y)
{
    _x += x;
    _y += y;
}

void Projectile::rotate(float angle)
{
    _angle += angle;
}

void Projectile::update(std::string event)
{
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
