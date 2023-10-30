/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Character
*/

#pragma once

#include <chrono>
#include <iostream>
#include <thread>
#include "AEntity.hpp"
#include "r-type/RType.hpp"

class Character : public AEntity {
   public:
    Character(EntityInfo info);
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
    void setProjectileSpeed(float projectileSpeed);
    float getProjectileSpeed() const;
    void resetLife();
    void setId(int id);
    void setLifeValue(int lifeValue);
    static void hurtEnemy(IEntity& self, IEntity& you);
    static void alliesTouched(IEntity& self, IEntity& you);
    bool getAlliesTouched() const;

   private:
    float _projectileSpeed = 5;
    std::chrono::duration<double> _targetFrameDuration;
    std::chrono::high_resolution_clock::time_point _lastShootTime;
    std::chrono::high_resolution_clock::time_point _currentTime;
    std::string _shootAsset = "PlayerProjectile";
    std::string _movementType;
    int _lifeValue;
    int _fireRate;
};
