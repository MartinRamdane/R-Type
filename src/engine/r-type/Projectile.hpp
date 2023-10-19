/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Projectile
*/

#pragma once

#include "../AEntity.hpp"
#include "Game.hpp"

class Projectile : public AEntity
{
public:
    Projectile(std::string path, float x, float y, int id, int damage, float scaleX, float scaleY, float speed, std::string spriteConfigJsonObjectName, Direction direction = RIGHT);
    ~Projectile();
    void move(float x, float y);
    virtual void update() override;
    static void hurtEntity(IEntity &self, IEntity &you);
};
