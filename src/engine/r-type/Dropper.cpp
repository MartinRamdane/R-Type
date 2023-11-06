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

void Dropper::update() {
    if (_x != _oldX || _y != _oldY) {
        setOldPosition(_x, _y);
    }
    if (isDead())
        RType::instance->createSupportShip(_x, _y);
    move(-1, 0);
}

void Dropper::move(float x, float y) {
    if ((_x + x * getSpeed()) < 0 - _radius) {
        kill();
        return;
    }
    setOldPosition(_x, _y);
    _x += x * getSpeed();
    _y += y * getSpeed();
}
