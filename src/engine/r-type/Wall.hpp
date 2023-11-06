/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Enemy
*/

#pragma once

#include "../Character.hpp"

class Wall : public Character {
   public:
    Wall(EntityInfo info);
    ~Wall();
    void update() override;
    void move(float x, float y) override;
    void setShouldMove(bool shouldMove) { _shouldMove = shouldMove; }

   protected:
   private:
    bool _shouldMove = true;
};
