/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** AEntity
*/

#include "AEntity.hpp"

AEntity::AEntity(std::string path, float x, float y, float angle, float scaleX, float scaleY) : refX(_x), refY(_y)
{
    _path = path;
    _x = x;
    _y = y;
    _angle = angle;
    _scaleX = scaleX;
    _scaleY = scaleY;
}

AEntity::~AEntity()
{
}

void AEntity::setPosition(float x, float y)
{
    _x = x;
    _y = y;
}

void AEntity::setRotation(float angle)
{
    _angle = angle;
}

void AEntity::move(float x, float y)
{
    _x += x;
    _y += y;
}

void AEntity::rotate(float angle)
{
    _angle += angle;
}

void AEntity::update(std::string event)
{
}

std::tuple<float, float> AEntity::getPosition()
{
    return std::make_tuple(_x, _y);
}

float AEntity::getRotation()
{
    return _angle;
}

void AEntity::setScale(float x, float y)
{
    _scaleX = x;
    _scaleY = y;
}

std::tuple<float, float> AEntity::getScale()
{
    return std::make_tuple(_scaleX, _scaleY);
}

std::string AEntity::getPath()
{
    return _path;
}

void AEntity::setPath(std::string path)
{
    _path = path;
}