/*
** EPITECH PROJECT, 2023
** IEntity.hpp
** File description:
** IEntity
*/

#pragma once

#include <string>
#include <tuple>

class IEntity
{
public:
    virtual ~IEntity() = default;
    virtual void setPosition(float x, float y) = 0;
    virtual void setRotation(float angle) = 0;
    virtual void move(float x, float y) = 0;
    virtual void rotate(float angle) = 0;
    virtual void update() = 0;
    virtual std::tuple<float, float> getPosition() const = 0;
    virtual float getRotation() const = 0;
    virtual void setScale(float x, float y) = 0;
    virtual std::tuple<float, float> getScale() const = 0;
    virtual std::string getPath() const = 0;
    virtual void setPath(std::string path) = 0;
    virtual float getSpeed() const = 0;
    virtual void setSpeed(float speed) = 0;
    virtual void setOldPosition(float x, float y) = 0;
    virtual std::tuple<float, float> getOldPosition() const = 0;
    virtual int getId() const = 0;
    virtual int getNbSprite() const = 0;
    virtual bool isCreated() const = 0;
    virtual void setCreated(bool created) = 0;
    virtual bool isDead() const = 0;
    virtual void setDamage(int damage) = 0;
    virtual int getDamage() const = 0;
    virtual void takeDamage(int damage) = 0;
    virtual std::string getSpriteConfigJsonPath() const = 0;
    virtual std::string getSpriteConfigJsonObjectName() const = 0;
    virtual void kill() = 0;

protected:
    float _oldX;
    float _oldY;
    int _id;
    std::string _spriteConfigJsonPath;
    std::string _spriteConfigJsonObjectName;

private:
};
