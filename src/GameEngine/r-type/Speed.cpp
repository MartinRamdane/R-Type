/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Speed
*/

#include "Speed.hpp"

Speed::Speed(std::string path, float x, float y, int id, int nbSprite, float angle, float scaleX, float scaleY)
    : Character(path, x, y, id, angle, scaleX, scaleY, nbSprite, "src/GameEngine/r-type/assets/data/Sprites.json", "Spaceship")
{
    // set special attributes
    setLife(70);
    setSpeed(6);
}

Speed::~Speed()
{
}
