/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Character
*/

#pragma once

#include "IEntity.hpp"
#include "r-type/Game.hpp"
#include <chrono>
#include <thread>
#include <iostream>

class Character : public IEntity
{
public:
    Character(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY, int nbSprite, std::string spriteConfigJsonPath, std::string spriteConfigJsonObjectName);
    ~Character();
    void setPosition(float x, float y);
    void setRotation(float angle);
    void move(float x, float y);
    void rotate(float angle);
    virtual void update();
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
    void setDead(bool dead);
    void setCreated(bool created);
    bool isDead() const;
    bool canShoot();
    void setLife(int life);
    int getLife() const;
    void setDamage(int damage);
    int getDamage() const;
    void setFireRate(float fireRate);
    float getFireRate() const;
    virtual void takeDamage(int damage);
    virtual void shoot();
    std::string getSpriteConfigJsonPath() const;
    std::string getSpriteConfigJsonObjectName() const;
    virtual void action(){};
    void kill();
    void setShootAsset(std::string shootAsset);
    void setRadius(float radius);
    float getRadius() const;
    bool getIsPositionSeted() const;
    void setIsPositionSeted();

private:
    bool _positionSeted = false;
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
    float _fireRate;
    int _life;
    int _damage;
    std::chrono::duration<double> _targetFrameDuration;
    std::chrono::high_resolution_clock::time_point _lastShootTime;
    std::chrono::high_resolution_clock::time_point _currentTime;
    std::string _shootAsset = "BulletSpaceship";
};
