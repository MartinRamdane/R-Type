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
    initialSpeed = info.speed;
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
    if (((_y + y * _speed) < _radius / 2) && dirY < 0) {
        y = -y;
        dirY = -dirY;
        Pong::instance->createSound("pongBallHitWall.ogg");
    }
    if (((_y + y * _speed) > Engine::instance->getWindowHeight() - _radius) &&
        dirY > 0) {
        y = -y;
        dirY = -dirY;
        Pong::instance->createSound("pongBallHitWall.ogg");
    }
    if (((_x + x * _speed) < _radius / 2) ||
        ((_x + x * _speed) >
         Engine::instance->getWindowWidth() - _radius / 2)) {
        Pong::instance->createSound("pongBallOut.ogg");
        kill();
    }
    setOldPosition(_x, _y);
    _x += x * _speed;
    _y += y * _speed;
}

void Ball::update() {
    if (getSpeed() > initialSpeed) {
        const float decayRate = 0.98;
        setSpeed(getSpeed() * decayRate);
    }
    move(dirX, dirY);
}

void Ball::hurtPlayer(IEntity& self, IEntity& you) {
    float playerY = std::get<1>(you.getPosition());
    float ballY = std::get<1>(self.getPosition());
    float dirX = std::get<0>(self.getDirectionVector());
    float dirY = std::get<1>(self.getDirectionVector());
    float currentSpeed = self.getSpeed();

    float playerHeight = you.getHeight();

    float relativeY = (ballY - playerY) / playerHeight;

    float maxAngle = M_PI / 2.0;
    float reflectionAngle = maxAngle * relativeY;

    if (dirX < 0) {
        dirX = cos(reflectionAngle) * currentSpeed;
    } else {
        dirX = -cos(reflectionAngle) * currentSpeed;
    }

    dirY = sin(reflectionAngle) * currentSpeed;

    float length = std::sqrt(dirX * dirX + dirY * dirY);
    if (length != 0) {
        dirX /= length;
        dirY /= length;
    }

    const float boostFactor = 1.75;
    self.setSpeed(currentSpeed * boostFactor);

    self.setDirectionVector(dirX, dirY);
    Pong::instance->createSound("pongBallhitPlayer.ogg");
}
