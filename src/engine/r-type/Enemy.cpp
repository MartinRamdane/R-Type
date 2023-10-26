/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Enemy
*/

#include "Enemy.hpp"

Enemy::Enemy(EntityInfo info) : Character(info) {
    setShootAsset(info.projectileType);
    setSpeed(info.speed);
    setFireRate(info.fireRate);
    setProjectileSpeed(info.projectileSpeed);
    setDamage(info.damage);
    setLife(info.life);
    setMovementType(info.movementType);
}

Enemy::~Enemy() {}

void Enemy::update() {
    if (_x != _oldX || _y != _oldY) {
        setOldPosition(_x, _y);
    }

    std::string movementType = getMovementType();

    if (movementType == "Linear") {
        move(-1, 0);
    } else if (movementType == "UpAndDown") {
        //TODO: use sinus to move up and down in a smooth way
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const auto timeElapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastMoveTime)
                .count();
        const bool needsDirectionChange = timeElapsed > 2000;

        if (needsDirectionChange) {
            _lastMove = (_lastMove == NONE || _lastMove == UP) ? DOWN : UP;
            _lastMoveTime = currentTime;
        }

        if (_lastMove == NONE || _lastMove == UP) {
            move(-1, 1);
        } else {
            move(-1, -1);
        }
    } else if (movementType == "Random") {
        int x = rand() % 3 - 1;
        int y = rand() % 3 - 1;
        auto pos = getPosition();
        int new_x = std::get<0>(pos) + x * getSpeed();
        int new_y = std::get<1>(pos) + y * getSpeed();
        int radius = getRadius();
        if (new_x > 850) {
            move(-1, 0);
        } else {
            if (new_y - radius < 0 || new_y + radius > 478) {
                y = -y;
                new_y = std::get<1>(pos) + y * getSpeed();
            }
        }
        move(x, y);
    }
    shoot();
}

void Enemy::shoot() {
    if (!canShoot())
        return;
    auto pos = getPosition();
    EntityInfo info;
    info.x = std::get<0>(pos) - 33;
    info.y = std::get<1>(pos) - 2;
    info.name = getShootAsset();
    info.scaleX = 0.25;
    info.scaleY = 0.25;
    info.speed = getProjectileSpeed();
    info.damage = getDamage();
    info.spriteConfigJsonObjectName = getShootAsset();
    info.spriteConfigJsonFileName = "rTypeAnimationConfig.json";
    info.direction = IEntity::LEFT;
    RType::instance->createProjectile(info, _direction == IEntity::LEFT ? true : false,
                                      IGame::ProjectileGroup::ENEMY);
}

void Enemy::move(float x, float y) {
    if ((_x + x * getSpeed()) < 0 - _radius) {
        kill();
        return;
    }
    setOldPosition(_x, _y);
    _x += x * getSpeed();
    _y += y * getSpeed();
}