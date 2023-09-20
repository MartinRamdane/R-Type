/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Tank
*/

#pragma once

#include "Player.hpp"
#include <chrono>

class Tank : public Player
{
public:
    Tank(std::string path, float x, float y, int id, float angle = 0, float scaleX = 1, float scaleY = 1, int life = 250, float speed = 0.6, int damage = 25, int fireRate = 0.8);
    ~Tank();

protected:
private:
};
