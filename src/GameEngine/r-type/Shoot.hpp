/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shoot
*/

#pragma once

#include "../IEntity.hpp"

class Shoot : public IEntity
{
public:
    Shoot(std::string path, float x, float y, float angle = 0, float scaleX = 1, float scaleY = 1, float speed = 1);
    ~Shoot();
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
    float getSpeed();
    void setSpeed(float speed);

protected:
private:
    std::string _path;
    float _x;
    float _y;
    float _angle;
    float _scaleX;
    float _scaleY;
    float _speed;
};
