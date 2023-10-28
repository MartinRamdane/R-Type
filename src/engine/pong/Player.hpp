/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Player
*/

#pragma once

#include "../Character.hpp"
#include "../Engine.hpp"
#include "../IEntity.hpp"

class Player : public Character {
   public:
    Player(EntityInfo info);
    ~Player();
    void move(float x, float y) override;
};
