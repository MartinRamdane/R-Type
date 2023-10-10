/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Enemy
*/

#include "Enemy.hpp"

Enemy::Enemy(std::string path, float x, float y, int id, std::string enemyConfig, int nbSprite, float angle, float scaleX, float scaleY)
    : Character(path, x, y, id, angle, scaleX, scaleY, nbSprite, "config.json", enemyConfig)
{
    setShootAsset("BulletEnemy1");
}

Enemy::~Enemy()
{
}

// TODO: add chrono to move up and down for a period of time
void Enemy::update()
{
    // Check if the position has changed and update the old position if needed
    if (_x != _oldX || _y != _oldY)
    {
        setOldPosition(_x, _y);
    }

    std::string movementType = getMovementType();

    if (movementType == "Horizontal")
    {
        move(-1, 0); // Horizontal movement
    }
    else if (movementType == "UpAndDown")
    {
        const auto currentTime = std::chrono::high_resolution_clock::now();
        const auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _lastMoveTime).count();
        const bool needsDirectionChange = timeElapsed > 600;

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
}
