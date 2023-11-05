/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Boss
*/

#pragma once

#include <cstdlib>
#include <ctime>
#include "../Character.hpp"
#ifdef WIN32
#define M_PI 3.14159265358979323846
#endif

class Boss : public Character {
   public:
    enum LastMove { UP, DOWN, LEFT, RIGHT, NONE };
    Boss(EntityInfo info);
    ~Boss();
    void update() override;
    void shoot() override;
    void move(float x, float y) override;

   protected:
   private:
    LastMove _lastMove = NONE;
    std::chrono::high_resolution_clock::time_point _lastMoveTime;
};
