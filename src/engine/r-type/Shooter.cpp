/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shooter
*/

#include "Shooter.hpp"

Shooter::Shooter(EntityInfo info) : Character(info) {
    // set special attributes
    setDamage(15);
    setLife(90);
    setLifeValue(90);
    setSpeed(2.5);
    setFireRate(4.5);
}

Shooter::~Shooter() {}
