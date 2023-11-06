/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Wall
*/

#include "Wall.hpp"

Wall::Wall(EntityInfo info) : Character(info) {
    setShootAsset(info.projectileType);
    setSpeed(info.speed);
    setFireRate(info.fireRate);
    setProjectileSpeed(info.projectileSpeed);
    setDamage(info.damage);
    setLife(info.life);
    setMovementType(info.movementType);
}

Wall::~Wall() {}

void Wall::update() {
    if (_x != _oldX || _y != _oldY) {
        setOldPosition(_x, _y);
    }
    if (_shouldMove) {
        move(-1, 0);
    }
}

void Wall::move(float x, float y) {
    if ((_x + x * getSpeed()) < 0 - _radius) {
        kill();
        return;
    }
    setOldPosition(_x, _y);
    _x += x * getSpeed();
    _y += y * getSpeed();
}
