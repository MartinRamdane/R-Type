/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(EntityInfo info) : Character(info) {}

Player::~Player() {}

void Player::move(float x, float y) {
  if ((_y + y * _speed) >
          Engine::instance->getWindowHeight() - (getHeight() / 2) - 10 ||
      (_y + y * _speed) < 10 + getHeight() / 2)
    return;
  setOldPosition(_x, _y);
  _x += x * _speed;
  _y += y * _speed;
}
