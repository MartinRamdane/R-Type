/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Projectile
*/

#pragma once

#include "../AEntity.hpp"
#include "RType.hpp"

class Projectile : public AEntity {
   public:
    Projectile(EntityInfo info);
    ~Projectile();
    void move(float x, float y);
    virtual void update() override;
    static void hurtEntity(IEntity& self, IEntity& you);
};
