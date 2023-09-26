/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** StaticObject
*/

#pragma once

#include "IEntity.hpp"

class StaticObject : public IEntity
{
public:
    StaticObject(std::string path, float x, float y, int id, std::string spriteConfigJsonPath, std::string spriteConfigJsonObjectName, float angle = 0, float scaleX = 1, float scaleY = 1, int nbSprite = 1);
    ~StaticObject();
    void setPosition(float x, float y);
    void setRotation(float angle);
    void move(float x, float y);
    void rotate(float angle);
    void update();
    std::tuple<float, float> getPosition() const;
    float getRotation() const;
    void setScale(float x, float y);
    std::tuple<float, float> getScale() const;
    std::string getPath() const;
    void setPath(std::string path);
    float getSpeed() const;
    void setSpeed(float speed);
    void setOldPosition(float x, float y);
    std::tuple<float, float> getOldPosition() const;
    int getId() const;
    int getNbSprite() const;
    bool isCreated() const;
    void setCreated(bool created);
    bool isDead() const;
    void setDamage(int damage);
    int getDamage() const;
    void takeDamage(int damage);
    std::string getSpriteConfigJsonPath() const;
    std::string getSpriteConfigJsonObjectName() const;
    void kill();

private:
    std::string _path;
    float _x;
    float _y;
    float _angle;
    float _scaleX;
    float _scaleY;
    float _speed;
    int _nbSprite;
    bool _created;
    bool _isDead;
};
