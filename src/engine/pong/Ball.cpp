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
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 1);
  int random = distrib(gen);
  setDirectionVector(random == 0 ? -1 : 1, 0);
}

Ball::~Ball() {}

void Ball::move(float x, float y) {
  if (((_y + y * _speed) < 10 + _radius / 2) && dirY < 0) {
    y = -y;    // Inverser la direction en Y
    dirY = -dirY;
  }
  if (((_y + y * _speed) >
       Engine::instance->getWindowHeight() - 10 - _radius) &&
      dirY > 0) {
    y = -y;    // Inverser la direction en Y
    dirY = -dirY;
  }
  if (((_x + x * _speed) < _radius / 2) ||
      ((_x + x * _speed) > Engine::instance->getWindowWidth() - _radius / 2)) {
    kill();
  }
  setOldPosition(_x, _y);
  _x += x * _speed;
  _y += y * _speed;
}

void Ball::update() {
  move(dirX, dirY);
}

void Ball::hurtPlayer(IEntity& self, IEntity& you) {
  // Obtenir les positions du joueur et de la balle
  float playerY = std::get<1>(you.getPosition());
  float ballY = std::get<1>(self.getPosition());
  float dirX = std::get<0>(self.getDirectionVector());
  float dirY = std::get<1>(self.getDirectionVector());
  float currentSpeed = self.getSpeed();

  float playerHeight = you.getHeight();

  // Calculer la position relative de la collision par rapport au joueur
  float relativeY = (ballY - playerY) / playerHeight;

  // Calculer l'angle d'impact en radians
  float maxAngle = M_PI / 2.0;    // Angle maximal de réflexion (45 degrés)
  float reflectionAngle = maxAngle * relativeY;

  // Inverser la direction en X si la balle se déplace vers la gauche (dirX < 0)
  if (dirX < 0) {
    dirX = cos(reflectionAngle) * currentSpeed;
  } else {
    dirX = -cos(reflectionAngle) * currentSpeed;
  }

  // Calculer la nouvelle direction en Y en fonction de l'angle de réflexion
  dirY = sin(reflectionAngle) * currentSpeed;

  // Normaliser le vecteur direction
  float length = std::sqrt(dirX * dirX + dirY * dirY);
  if (length != 0) {
    dirX /= length;
    dirY /= length;
  }

  self.setDirectionVector(dirX, dirY);
}
