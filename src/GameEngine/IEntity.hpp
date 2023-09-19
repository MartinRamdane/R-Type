/*
** EPITECH PROJECT, 2023
** IEntity.hpp
** File description:
** IEntity
*/

#pragma once

#include <string>

class IEntity
{
public:
    virtual ~IEntity() = default;
    virtual void setPosition(float x, float y) = 0;
    virtual void setRotation(float angle) = 0;
    virtual void move(float x, float y) = 0;
    virtual void rotate(float angle) = 0;
    virtual void update(std::string event) = 0;
    virtual std::tuple<float, float> getPosition() const = 0;
    virtual float getRotation() const = 0;
    virtual void setScale(float x, float y) = 0;
    virtual std::tuple<float, float> getScale() const = 0;
    virtual std::string getPath() const = 0;
    virtual void setPath(std::string path) = 0;
    virtual float getSpeed() const = 0;
    virtual void setSpeed(float speed) = 0;

protected:
private:
};
