/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Speed
*/

#pragma once

#include "../Character.hpp"
#include <chrono>

class Speed : public Character
{
public:
    Speed(std::string path, float x, float y, int id, int nbSprite = 1, float angle = 0, float scaleX = 1, float scaleY = 1);
    ~Speed();

protected:
private:
};
