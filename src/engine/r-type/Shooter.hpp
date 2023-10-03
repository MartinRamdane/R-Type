/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shooter
*/

#pragma once

#include "../Character.hpp"
#include <chrono>

class Shooter : public Character
{
public:
    Shooter(std::string path, float x, float y, int id, int nbSprite = 1, float angle = 0, float scaleX = 1, float scaleY = 1);
    ~Shooter();

protected:
private:
};
