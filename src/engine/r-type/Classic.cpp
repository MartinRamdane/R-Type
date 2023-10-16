/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Classic
*/

#include "Classic.hpp"

Classic::Classic(std::string path, float x, float y, int id, int nbSprite, float angle, float scaleX, float scaleY)
    : Character(path, x, y, id, angle, scaleX, scaleY, nbSprite, "rTypeConfig.json", "Spaceship")
{
    setSpeed(3);
}

Classic::~Classic()
{
}
