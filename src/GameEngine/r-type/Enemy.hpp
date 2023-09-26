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
    Enemy(std::string path, float x, float y, int id, float angle = 0, float scaleX = 1, float scaleY = 1, int life = 100, float speed = 1, int damage = 10, int fireRate = 1, int nbSprite = 1);
    ~Enemy();

protected:
private:
};
