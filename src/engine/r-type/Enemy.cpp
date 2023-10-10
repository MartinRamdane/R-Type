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

void Enemy::update()
{
    if (_x != _oldX || _y != _oldY)
        setOldPosition(_x, _y);
    if (_lastMoveTime.time_since_epoch().count() == 0)
        _lastMoveTime = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - _lastMoveTime).count() > 100)
    {
        _lastMoveTime = std::chrono::high_resolution_clock::now();
        move(-1, 0);
    }
    // std::string movementType = getMovementType();
    // std::cout << movementType << std::endl;
    // if (movementType == "Horizontal") {
    //     move(-1, 0);
    // } else if (movementType == "UpAndDown") {
    //     if (_lastMove == NONE || _lastMove == DOWN) {
    //         move(-1, -1);
    //         _lastMove = UP;
    //     } else if (_lastMove == UP) {
    //         move(-1, 1);
    //         _lastMove = DOWN;
    //     }
    // }
}
