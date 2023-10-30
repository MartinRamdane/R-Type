/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Boss
*/

#include "Boss.hpp"

Boss::Boss(EntityInfo info) : Character(info) {
    setShootAsset(info.projectileType);
    setSpeed(info.speed);
    setFireRate(info.fireRate);
    setProjectileSpeed(info.projectileSpeed);
    setDamage(info.damage);
    setLife(info.life);
    setMovementType(info.movementType);
}

Boss::~Boss() {}

void Boss::update() {
    if (_x != _oldX || _y != _oldY) {
        setOldPosition(_x, _y);
    }

    std::string movementType = getMovementType();

    if (movementType == "Boss1" && RType::instance->getEnemies().size() == 1) {
        auto pos = getPosition();
        if (std::get<1>(pos) > 468 - getRadius()) {
            move(0, -1);
        } else {
            const auto currentTime = std::chrono::high_resolution_clock::now();
            const auto timeElapsed =
                std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastMoveTime)
                    .count();
            const bool needsDirectionChange = timeElapsed > 2000;

            if (needsDirectionChange) {
                _lastMove = (_lastMove == NONE || _lastMove == LEFT) ? RIGHT : LEFT;
                _lastMoveTime = currentTime;
            }

            double horizontalDisplacement =
                std::sin(2 * M_PI * timeElapsed / 4000.0);    // Adjust the period (4000) as needed
            int horizontalDirection = (_lastMove == LEFT) ? 1 : -1;
            int verticalDirection = 0;

            move(horizontalDirection * horizontalDisplacement, verticalDirection);
        }
    }
    shoot();
}

void Boss::shoot() {
    if (!canShoot())
        return;
    auto players = RType::instance->getPlayers();
    for (auto player : players) {
        auto pos = getPosition();
        auto playerPos = player->getPosition();
        EntityInfo info;
        info.x = std::get<0>(pos) - 33;
        info.y = std::get<1>(pos) - 2;
        info.name = getShootAsset();
        info.scaleX = 2;
        info.scaleY = 2;
        info.speed = getProjectileSpeed();
        info.damage = getDamage();
        info.spriteConfigJsonObjectName = getShootAsset();
        info.spriteConfigJsonFileName = "rTypeAnimationConfig.json";
        info.direction = TRACKING;
        info.relatedPlayerId = player->getId();
        RType::instance->createProjectile(info, false, IGame::ProjectileGroup::BOSS);
    }
}

void Boss::move(float x, float y) {
    if ((_x + x * getSpeed()) < 0 - _radius) {
        kill();
        return;
    }
    setOldPosition(_x, _y);
    _x += x * getSpeed();
    _y += y * getSpeed();
}