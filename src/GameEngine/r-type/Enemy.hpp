/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Enemy
*/

#pragma once

#include "../Character.hpp"

class Enemy : public Character
{
public:
    Enemy(std::string path, float x, float y, float angle = 0, float scaleX = 1, float scaleY = 1, int life = 100, float speed = 1, int damage = 10, int fireRate = 1);
    ~Enemy();
    void setLife(int life);
    int getLife() const;
    void setDamage(int damage);
    int getDamage() const;
    void setFireRate(int fireRate);
    int getFireRate() const;

protected:
private:
    int _life;
    int _damage;
    int _fireRate;
};
