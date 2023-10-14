/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Enemy
*/

#include "Enemy.hpp"

Enemy::Enemy(std::string path, float x, float y, int id, std::string enemyConfig, std::string bulletType, float fireRate, float speed, int nbSprite, float angle, float scaleX, float scaleY)
    : Character(path, x, y, id, angle, scaleX, scaleY, nbSprite, "config.json", enemyConfig)
{
    setShootAsset("BulletEnemy2");
    setSpeed(speed);
    setFireRate(fireRate);
}

Enemy::~Enemy()
{
}

void Enemy::update()
{
    if (_x != _oldX || _y != _oldY)
    {
        setOldPosition(_x, _y);
    }

    std::string movementType = getMovementType();

    if (movementType == "Horizontal")
    {
        move(-1, 0);
    }
    else if (movementType == "UpAndDown")
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastMoveTime).count();
        const bool needsDirectionChange = timeElapsed > 450;

        if (needsDirectionChange)
        {
            _lastMove = (_lastMove == NONE || _lastMove == UP) ? DOWN : UP;
            _lastMoveTime = currentTime;
        }

        if (_lastMove == NONE || _lastMove == UP)
        {
            move(-1, 1);
        }
        else
        {
            move(-1, -1);
        }
    }
    shoot();
}

void Enemy::shoot()
{
    if (!canShoot())
        return;
    auto pos = getPosition();
    Game::instance->createProjectile(std::get<0>(pos) - 33, std::get<1>(pos) - 2, getShootAsset(), 0.25, 0.25, 5, getDamage(), getShootAsset(), "_enemyProjectilesGroups");
}
