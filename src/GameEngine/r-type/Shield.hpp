/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shield
*/

#pragma once

#include "../Character.hpp"
#include <chrono>

class Shield : public Character
{
public:
    Shield(std::string path, float x, float y, int id, int nbSprite = 1, float angle = 0, float scaleX = 1, float scaleY = 1);
    ~Shield();

protected:
private:
    // bool _shieldIsUp = false;
    // bool _canActivateShield = true;

    // Shield time management
    // std::chrono::duration<double> _targetShieldDuration;
    // std::chrono::time_point<std::chrono::system_clock> _shieldStart;
    // std::chrono::time_point<std::chrono::system_clock> _shieldEnd;
};
