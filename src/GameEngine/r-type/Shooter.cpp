/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shooter
*/

#include "Shooter.hpp"

Shooter::Shooter(std::string path, float x, float y, int id, int nbSprite, float angle, float scaleX, float scaleY)
    : Character(path, x, y, id, angle, scaleX, scaleY, nbSprite, "src/GameEngine/r-type/assets/data/Sprites.json", "Spaceship")
{
    // set special attributes
    setDamage(15);
    setLife(90);
    setSpeed(2.5);
    setFireRate(4.5);
}

Shooter::~Shooter()
{
}
