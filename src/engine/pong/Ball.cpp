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
  setDirectionVector(1, 0);
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

  std::tuple<float, float> pos = getDirectionVector();
  float dirX = std::get<0>(pos);
  float dirY = std::get<1>(pos);
  move(dirX, dirY);

  if ((_x + _radius >= Engine::instance->getWindowWidth() && dirX > 0) ||
      (_x - _radius <= 0 && dirX < 0)) {
    dirX = -dirX;
  }

  if ((_y + _radius / 2 >= Engine::instance->getWindowHeight() && dirY > 0) ||
      (_y - _radius / 2 <= 0 && dirY < 0)) {
    dirY = -dirY;
  }
  setDirectionVector(dirX, dirY);
}

void Ball::hurtPlayer(IEntity& self, IEntity& you) {

  float playerY = std::get<1>(you.getPosition());
  float ballY = std::get<1>(self.getPosition());
  float dirX = std::get<0>(self.getDirectionVector());
  float dirY = std::get<1>(self.getDirectionVector());

  float playerHeight = you.getHeight();

  float relativeY = (ballY - playerY) / playerHeight;

  float maxAngle = M_PI / 4.0;
  float reflectionAngle = maxAngle * relativeY;

  float currentSpeed = sqrt(dirX * dirX + dirY * dirY);
  dirX = -cos(reflectionAngle) * currentSpeed;

  dirY = sin(reflectionAngle) * currentSpeed;
  self.setDirectionVector(dirX, dirY);
}
