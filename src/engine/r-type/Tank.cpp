/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Tank
*/

#include "Tank.hpp"

Tank::Tank(std::string path, float x, float y, int id, float scaleX, float scaleY)
    : Character(path, x, y, id, scaleX, scaleY, "rTypeConfig.json", "Spaceship")
{
    // set special attributes
    setLife(200);
    setLifeValue(200);
    setSpeed(1.5);
    setFireRate(1.5);
    setDamage(20);
}

Tank::~Tank()
{
}
