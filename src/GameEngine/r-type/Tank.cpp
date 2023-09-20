/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Tank
*/

#include "Tank.hpp"

Tank::Tank(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY, int life, float speed, int damage, int fireRate)
    : Player(path, x, y, id, angle, scaleX, scaleY, life, speed, damage, fireRate)
{
}

Tank::~Tank()
{
}
