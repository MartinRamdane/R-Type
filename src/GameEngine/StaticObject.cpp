/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** StaticObject
*/

#include "StaticObject.hpp"

StaticObject::StaticObject(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY)
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
