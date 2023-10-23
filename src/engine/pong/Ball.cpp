/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Ball
*/

#include "Ball.hpp"

Ball::Ball(EntityInfo info) : AEntity(info) {
  _damage = info.damage;
  _speed = info.speed;
  _direction = info.direction;
  _life = 1;
}

Ball::~Ball() {}

void Ball::move(float x, float y) {
  if ((_x + x * _speed) > Engine::instance->getWindowWidth() - _radius ||
      (_x + x * _speed) < 0 + _radius ||
      (_y + y * _speed) > Engine::instance->getWindowHeight() - (_radius / 2) ||
      (_y + y * _speed) < 0 + (_radius / 2)) {
    _isDead = true;
    return;
  }
  setOldPosition(_x, _y);
  _x += x * _speed;
  _y += y * _speed;
}

void Ball::update() {
  ;
}
