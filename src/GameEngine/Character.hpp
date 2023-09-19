/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Character
*/

#pragma once

#include "IEntity.hpp"

class Character : public IEntity
{
public:
    Character(std::string path, float x, float y, float angle = 0, float scaleX = 1, float scaleY = 1, float speed = 1);
    ~Character();
    void setPosition(float x, float y);
    void setRotation(float angle);
    void move(float x, float y);
    void rotate(float angle);
    void update(std::string event);
    std::tuple<float, float> getPosition();
    float getRotation();
    void setScale(float x, float y);
    std::tuple<float, float> getScale();
    std::string getPath();
    void setPath(std::string path);
    float setSpeed(int speed);
    float getSpeed() const;

private:
    std::string _path;
    float _x;
    float _y;
    float _angle;
    float _scaleX;
    float _scaleY;
    float _speed;
};
