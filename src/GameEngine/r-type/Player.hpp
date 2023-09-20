/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Player
*/

#pragma once

#include "../Character.hpp"
#include <iostream>

class Player : public Character
{
public:
    Player(std::string path, float x, float y, int id, float angle = 0, float scaleX = 1, float scaleY = 1, int life = 100, float speed = 1, int damage = 10, int fireRate = 1);
    ~Player();
    void setLife(int life);
    int getLife() const;
    void setDamage(int damage);
    int getDamage() const;
    void setFireRate(int fireRate);
    int getFireRate() const;
    static void hurtProjectile(IEntity &self, IEntity &you);

protected:
private:
    int _life;
    int _damage;
    int _fireRate;
};
