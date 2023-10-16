/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Enemy
*/

#include "Enemy.hpp"

Enemy::Enemy(std::string path, float x, float y, int id, std::string enemyConfig, std::string bulletType, float fireRate, float speed, float bulletSpeed, int damage, int nbSprite, float angle, float scaleX, float scaleY)
    : Character(path, x, y, id, angle, scaleX, scaleY, nbSprite, "config.json", enemyConfig)
{
    setShootAsset(bulletType);
    setSpeed(speed);
    setFireRate(fireRate);
    setBulletSpeed(bulletSpeed);
    setDamage(damage);
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
        const bool needsDirectionChange = timeElapsed > 2000;

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
    else if (movementType == "Random")
    {
        srand(time(NULL));
        int x = rand() % 3 - 1;
        int y = rand() % 3 - 1;
        auto pos = getPosition();
        int new_x = std::get<0>(pos) + x * getSpeed();
        int new_y = std::get<1>(pos) + y * getSpeed();
        int radius = getRadius();
        if (new_x > 850)
        {
            move(-1, 0);
        }
        else
        {
            if (new_y - radius < 0 || new_y + radius > 478)
            {
                y = -y;
                new_y = std::get<1>(pos) + y * getSpeed();
            }
        }
        move(x, y);
    }
    shoot();
}

void Enemy::shoot()
{
    if (!canShoot())
        return;
    auto pos = getPosition();
    Game::instance->createProjectile(std::get<0>(pos) - 33, std::get<1>(pos) - 2, getShootAsset(), 0.25, 0.25, getBulletSpeed(), getDamage(), getShootAsset(), "_enemyProjectilesGroups", _direction == IEntity::LEFT ? true : false, Direction::LEFT);
}

void Enemy::move(float x, float y)
{
    if ((_x + x * getSpeed()) < 0 - _radius)
    {
        kill();
        return;
    }
    setOldPosition(_x, _y);
    _x += x * getSpeed();
    _y += y * getSpeed();
}