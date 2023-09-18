/*
** EPITECH PROJECT, 2023
** Player.cpp
** File description:
** Player
*/

#include "Player.hpp"

Player::Player()
{
    _x = 0;
    _y = 0;
}

int Player::getXPos()
{
    return (_x);
}

int Player::getYPos()
{
    return (_y);
}

void Player::setXPos(int x)
{
    _x = x;
}

void Player::setYPos(int y)
{
    _y = y;
}

void Player::setPlayerName(std::string name)
{
    _playerName = name;
}