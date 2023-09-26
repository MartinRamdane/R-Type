/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Tank
*/

#include "Tank.hpp"

Tank::Tank(std::string path, float x, float y, int id, int nbSprite, float angle, float scaleX, float scaleY)
    : Character(path, x, y, id, angle, scaleX, scaleY, nbSprite)
{
    // set special attributes
}

Tank::~Tank()
{
}
