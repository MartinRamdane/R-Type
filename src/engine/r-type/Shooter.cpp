/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shooter
*/

#include "Shooter.hpp"

Shooter::Shooter(std::string path, float x, float y, int id, float scaleX, float scaleY)
    : Character(path, x, y, id, scaleX, scaleY, "rTypeConfig.json", "Spaceship")
{
    // set special attributes
    setDamage(15);
    setLife(90);
    setLifeValue(90);
    setSpeed(2.5);
    setFireRate(4.5);
}

Shooter::~Shooter()
{
}
