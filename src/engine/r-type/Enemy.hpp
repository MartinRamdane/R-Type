/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Enemy
*/

#pragma once

#include "../Character.hpp"
class Enemy : public Character
{
public:
    enum LastMove
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };
    Enemy(std::string path, float x, float y, int id, std::string enemyConfig, int nbSprite = 1, float angle = 0, float scaleX = 1, float scaleY = 1);
    ~Enemy();
    void update() override;

protected:
private:
    LastMove _lastMove = NONE;
    std::chrono::high_resolution_clock::time_point _lastMoveTime;
};
