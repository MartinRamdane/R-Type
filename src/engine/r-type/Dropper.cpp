/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Dropper
*/

#include "Dropper.hpp"

Dropper::Dropper(EntityInfo info) : Character(info) {
    setLife(info.life);
}

Dropper::~Dropper() {}

void Dropper::update()
{
    if (_x != _oldX || _y != _oldY) {
        setOldPosition(_x, _y);
    }
    move(-1, 0);
}
