/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Speed
*/

#include "Speed.hpp"

Speed::Speed(std::string path, float x, float y, int id, float scaleX, float scaleY)
    : Character(path, x, y, id, scaleX, scaleY, "rTypeConfig.json", "Spaceship")
{
    // set special attributes
    setLife(70);
    setLifeValue(70);
    setSpeed(6);
}

Speed::~Speed()
{
}
