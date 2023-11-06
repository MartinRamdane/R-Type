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
    } else if (movementType == "Wave") {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const auto timeElapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(currentTime -
                                                                  _lastMoveTime)
                .count();
        const bool needsDirectionChange = timeElapsed > 2000;

        if (needsDirectionChange) {
            _lastMove = (_lastMove == NONE || _lastMove == UP) ? DOWN : UP;
            _lastMoveTime = currentTime;
        }

        double verticalDisplacement = std::sin(2 * M_PI * timeElapsed / 4000.0);
        int verticalDirection = (_lastMove == UP) ? 1 : -1;
        int horizontalDirection = -1;

        move(horizontalDirection, verticalDirection * verticalDisplacement);
    } else if (movementType == "Random") {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const auto timeElapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(currentTime -
                                                                  _lastMoveTime)
                .count();
        const bool needsDirectionChange = timeElapsed > 2000;

        if (needsDirectionChange) {
            _lastMove = static_cast<LastMove>(rand() % 4);
            _lastMoveTime = currentTime;
        }

        int verticalDirection = 0;
        int horizontalDirection = 0;

        if (_x < 0 - _radius) {
            _lastMove = RIGHT;
            _lastMoveTime = currentTime;
        } else if (_x > 700 + _radius) {
            _lastMove = LEFT;
            _lastMoveTime = currentTime;
        } else if (_y < 130 - _radius) {
            _lastMove = UP;
            _lastMoveTime = currentTime;
        } else if (_y > 300 + _radius) {
            _lastMove = DOWN;
            _lastMoveTime = currentTime;
        } else if (_x < 200) {
            _lastMove = RIGHT;
            _lastMoveTime = currentTime;
        }

        switch (_lastMove) {
            case UP:
                verticalDirection = 1;
                break;
            case DOWN:
                verticalDirection = -1;
                break;
            case LEFT:
                horizontalDirection = -1;
                break;
            case RIGHT:
                horizontalDirection = 1;
                break;
            default:
                break;
        }

        move(horizontalDirection, verticalDirection);
    } else if (movementType == "UpAndDown") {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const auto timeElapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(currentTime -
                                                                  _lastMoveTime)
                .count();
        const bool needsDirectionChange = timeElapsed > 2000;

        if (needsDirectionChange) {
            _lastMove = (_lastMove == NONE || _lastMove == UP) ? DOWN : UP;
            _lastMoveTime = currentTime;
        }

        int verticalDirection = (_lastMove == UP) ? 1 : -1;

        move(-1, verticalDirection);
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
    info.name = getProjectileAsset();
    info.scaleX = 0.25;
    info.scaleY = 0.25;
    info.speed = getProjectileSpeed();
    info.damage = getDamage();
    info.spriteConfigJsonObjectName = getProjectileAsset();
    info.spriteConfigJsonFileName = "rTypeAnimationConfig.json";
    if (getProjectileAsset() == "Bomb") {
        info.scaleX = 0.75;
        info.scaleY = 0.75;
        info.x = std::get<0>(pos) + 10;
        info.y = std::get<1>(pos) + 5;
    }
    info.direction = IEntity::LEFT;

    RType::instance->createProjectile(
        info, _direction == IEntity::LEFT ? true : false,
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