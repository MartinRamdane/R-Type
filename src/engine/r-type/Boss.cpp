/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Boss
*/

#include "Boss.hpp"
#include "Wall.hpp"

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

    auto wall = RType::instance->getWalls();
    if (RType::instance->getEnemies().size() == 1 && wall.size() > 0) {
        for (auto w : wall) {
            w->setShouldMove(false);
        }
    }

    if (movementType == "Boss1" && RType::instance->getEnemies().size() == 1) {
        auto pos = getPosition();
        if (std::get<1>(pos) > 440) {
            move(0, -1);
        } else {
            const auto currentTime = std::chrono::high_resolution_clock::now();
            const auto timeElapsed =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    currentTime - _lastMoveTime)
                    .count();
            const bool needsDirectionChange = timeElapsed > 2000;

            if (needsDirectionChange) {
                _lastMove =
                    (_lastMove == NONE || _lastMove == LEFT) ? RIGHT : LEFT;
                _lastMoveTime = currentTime;
            }

            double horizontalDisplacement =
                std::sin(2 * M_PI * timeElapsed /
                         4000.0);  // Adjust the period (4000) as needed
            int horizontalDirection = (_lastMove == LEFT) ? 1 : -1;
            int verticalDirection = 0;

            move(horizontalDirection * horizontalDisplacement,
                 verticalDirection);
        }
    } else if (movementType == "Boss2" &&
               RType::instance->getEnemies().size() == 1) {
        auto pos = getPosition();
        std::cout << "Boss2" << std::endl;
        if (std::get<0>(pos) > 750) {
            move(-1, 0);
        } else {
            //move up and down for some time
            const auto currentTime = std::chrono::high_resolution_clock::now();
            const auto timeElapsed =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    currentTime - _lastMoveTime)
                    .count();
            bool needsDirectionChange;
            needsDirectionChange = timeElapsed > 2000;
            if (needsDirectionChange) {
                _lastMove = (_lastMove == NONE || _lastMove == UP) ? DOWN : UP;
                _lastMoveTime = currentTime;
            }
            double verticalDisplacement;
            if (_didOnce == false) {
                _didOnce = true;
                verticalDisplacement =
                    std::sin(2 * M_PI * timeElapsed / 3000.0);
            } else {
                verticalDisplacement =
                    std::sin(2 * M_PI * timeElapsed / 4000.0);
            }
            int verticalDirection = (_lastMove == UP) ? 1 : -1;
            int horizontalDirection = 0;
            move(horizontalDirection, verticalDirection * verticalDisplacement);
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
        EntityInfo info;
        info.name = getProjectileAsset();
        if (!info.name.find("Boss1")) {
            int random = rand() % 2;
            random == 0 ? info.x = std::get<0>(pos) + getRadius() / 2 + 55
                        : info.x = std::get<0>(pos) - getRadius() / 2 - 55;
            info.y = std::get<1>(pos) - getRadius();
            info.scaleX = 1.7;
            info.scaleY = 1.7;
        } else {
            std::cout << "Boss2" << std::endl;
            info.x = std::get<0>(pos) - 45;
            info.y = std::get<1>(pos) + 25;
        }
        info.speed = getProjectileSpeed();
        info.damage = getDamage();
        info.spriteConfigJsonObjectName = getProjectileAsset();
        info.spriteConfigJsonFileName = "rTypeAnimationConfig.json";
        std::cout << info.name << std::endl;
        info.direction = info.name.find("Boss2") ? IEntity::Direction::TRACKING
                                                 : IEntity::Direction::LEFT;
        info.relatedPlayerId = player->getId();
        RType::instance->createProjectile(info, false,
                                          IGame::ProjectileGroup::BOSS);
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