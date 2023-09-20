/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Speed
*/

#pragma once

#include "Player.hpp"
#include <chrono>

class Speed : public Player
{
public:
    Speed(std::string path, float x, float y, int id, float angle = 0, float scaleX = 1, float scaleY = 1, int life = 100, float speed = 2, int damage = 10, int fireRate = 1);
    ~Speed();

protected:
private:
};
