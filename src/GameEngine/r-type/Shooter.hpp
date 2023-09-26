/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shooter
*/

#pragma once

#include "Player.hpp"
#include <chrono>

class Shooter : public Player
{
public:
    Shooter(std::string path, float x, float y, int id, float angle = 0, float scaleX = 1, float scaleY = 1, int life = 100, float speed = 1, int damage = 10, float fireRate = 2.5, int nbSprite = 1);
    ~Shooter();

protected:
private:
};
