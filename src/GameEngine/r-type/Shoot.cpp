/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shoot
*/

#include "Shoot.hpp"

Shoot::Shoot(std::string path, float x, float y, float angle, float scaleX, float scaleY, float speed)
{
}

Shoot::~Shoot()
{
}

void Shoot::setPosition(float x, float y)
{
    _x = x;
    _y = y;
}

void Shoot::setRotation(float angle)
{
    _angle = angle;
}

void Shoot::move(float x, float y)
{
    _x += x;
    _y += y;
}

void Shoot::rotate(float angle)
{
    _angle += angle;
}

void Shoot::update(std::string event)
{
}

std::tuple<float, float> Shoot::getPosition()
{
    return std::make_tuple(_x, _y);
}

float Shoot::getRotation()
{
    return _angle;
}

void Shoot::setScale(float x, float y)
{
    _scaleX = x;
    _scaleY = y;
}

std::tuple<float, float> Shoot::getScale()
{
    return std::make_tuple(_scaleX, _scaleY);
}

std::string Shoot::getPath()
{
    return _path;
}

void Shoot::setPath(std::string path)
{
    _path = path;
}

float Shoot::getSpeed()
{
    return _speed;
}

void Shoot::setSpeed(float speed)
{
    _speed = speed;
}
