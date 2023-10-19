/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Character
*/

#pragma once

#include "AEntity.hpp"
#include "r-type/Game.hpp"
#include <chrono>
#include <thread>
#include <iostream>

class Character : public AEntity
{
public:
    Character(std::string path, float x, float y, int id, float scaleX, float scaleY, std::string spriteConfigJsonPath, std::string spriteConfigJsonObjectName);
    ~Character();
    virtual void move(float x, float y);
    virtual void update();
    bool canShoot();
    void setFireRate(float fireRate);
    float getFireRate() const;
    virtual void takeDamage(int damage);
    virtual void shoot();
    virtual void action(){};
    void setShootAsset(std::string shootAsset);
    void setMovementType(std::string movementType);
    std::string getMovementType() const;
    std::string getShootAsset() const;
    void setBulletSpeed(float bulletSpeed);
    float getBulletSpeed() const;
    void resetLife();
    void setId(int id);
    void setLifeValue(int lifeValue);

private:
    float _bulletSpeed = 5;
    std::chrono::duration<double> _targetFrameDuration;
    std::chrono::high_resolution_clock::time_point _lastShootTime;
    std::chrono::high_resolution_clock::time_point _currentTime;
    std::string _shootAsset = "BulletSpaceship";
    std::string _movementType;
    int _lifeValue;
    int _fireRate;
};
