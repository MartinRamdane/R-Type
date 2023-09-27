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
    Enemy(std::string path, float x, float y, int id, int nbSprite = 1, float angle = 0, float scaleX = 1, float scaleY = 1);
    ~Enemy();

protected:
private:
};
