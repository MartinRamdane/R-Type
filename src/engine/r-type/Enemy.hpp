/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Enemy
*/

#pragma once

#include "../Character.hpp"
#include <cstdlib>
#include <ctime>
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
    Enemy(EntityInfo info);
    ~Enemy();
    void update() override;
    void shoot() override;
    void move(float x, float y) override;

protected:
private:
    LastMove _lastMove = NONE;
    std::chrono::high_resolution_clock::time_point _lastMoveTime;
};
