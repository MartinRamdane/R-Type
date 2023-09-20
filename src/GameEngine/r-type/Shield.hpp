/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shield
*/

#pragma once

#include "Player.hpp"
#include <chrono>

class Shield : public Player
{
public:
    Shield(std::string path, float x, float y, int id, float angle = 0, float scaleX = 1, float scaleY = 1, int life = 100, float speed = 1, int damage = 10, int fireRate = 1);
    ~Shield();

protected:
private:
    bool _shieldIsUp = false;
    bool _canActivateShield = true;

    // Shield time management
    std::chrono::duration<double> _targetShieldDuration;
    std::chrono::time_point<std::chrono::system_clock> _shieldStart;
    std::chrono::time_point<std::chrono::system_clock> _shieldEnd;
};
