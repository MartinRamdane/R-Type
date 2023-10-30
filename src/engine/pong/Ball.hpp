/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Ball
*/

#pragma once

#include <cmath>
#include <random>
#include "../AEntity.hpp"
#include "../Engine.hpp"
#include "../IEntity.hpp"
#ifdef WIN32
#define M_PI 3.14159265358979323846
#endif
class Ball : public AEntity {
   public:
    Ball(EntityInfo info);
    ~Ball();
    void move(float x, float y);
    virtual void update() override;
    static void hurtPlayer(IEntity& self, IEntity& you);

   private:
    float initialSpeed;
};
