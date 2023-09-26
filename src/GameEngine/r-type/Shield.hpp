/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shield
*/

#pragma once

#include "../Character.hpp"
#include <chrono>
#include <memory>

class Shield : public Character
{
public:
    Shield(std::string path, float x, float y, int id, int nbSprite = 1, float angle = 0, float scaleX = 1, float scaleY = 1);
    ~Shield();

    void activateShield();
    void deactivateShield();
    bool isShieldUp() const;
    bool canActivateShield() const;
    void update() override;
    void action() override;
    void takeDamage(int damage) override;

protected:
private:
    bool _shieldIsUp = false;
    bool _canActivateShield = true;

    std::chrono::duration<double> _targetShieldDuration;
    std::chrono::duration<double> _reloadShieldDuration;
    std::chrono::high_resolution_clock::time_point _shieldStart;
    std::chrono::high_resolution_clock::time_point _shieldEnd;
    std::shared_ptr<StaticObject> _shield;
};
