/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Speed
*/

#include "Speed.hpp"

Speed::Speed(EntityInfo info) : Character(info) {
    // set special attributes
    setLife(70);
    setLifeValue(70);
    setSpeed(6);
}

Speed::~Speed() {}
