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
    Player(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY, int life, float speed, int damage, int fireRate);
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
