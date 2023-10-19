/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Classic
*/

#pragma once

#include "../Character.hpp"
#include <iostream>
#include "Game.hpp"

class Classic : public Character
{
public:
    Classic(std::string path, float x, float y, int id, float scaleX = 1, float scaleY = 1);
    ~Classic();

protected:
private:
};
