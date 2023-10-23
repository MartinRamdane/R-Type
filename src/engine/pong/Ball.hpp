/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Ball
*/

#pragma once

#include "../AEntity.hpp"
#include "../IEntity.hpp"
#include "../Engine.hpp"

class Ball : public AEntity
{
public:
    Ball(EntityInfo info);
    ~Ball();
    void move(float x, float y);
    virtual void update() override;
};
