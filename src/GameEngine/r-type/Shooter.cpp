/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shooter
*/

#include "Shooter.hpp"

Shooter::Shooter(std::string path, float x, float y, int id, int nbSprite, float angle, float scaleX, float scaleY)
    : Character(path, x, y, id, angle, scaleX, scaleY, nbSprite)
{
    // set special attributes
}

Shooter::~Shooter()
{
}
