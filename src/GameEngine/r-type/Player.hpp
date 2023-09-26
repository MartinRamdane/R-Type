/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Player
*/

#pragma once

#include "../Character.hpp"
#include <iostream>
#include "Game.hpp"

class Player : public Character
{
public:
    Player(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY, int life, float speed, int damage, int fireRate, int nbSprite);
    ~Player();
    void shoot();
    static void hurtProjectile(IEntity &self, IEntity &you);

protected:
private:
};
