/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Projectile
*/

#include "Projectile.hpp"

Projectile::Projectile(EntityInfo info) : AEntity(info) {
    _damage = info.damage;
    _speed = info.speed;
    _direction = info.direction;
    _life = 1;
    _relatedPlayerId = info.relatedPlayerId;
}

Projectile::~Projectile() {}

void Projectile::move(float x, float y) {
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

void Projectile::trackPlayer() {
    auto player = RType::instance->getPlayer(_relatedPlayerId);
    if (player == nullptr) {
        //make it move in the direction of the player but not track it
        directionalMove();
        return;
    }
    auto pos = player->getPosition();
    int x = std::get<0>(pos);
    int y = std::get<1>(pos);
    int xDiff = x - _x;
    int yDiff = y - _y;
    int xAbs = std::abs(xDiff);
    int yAbs = std::abs(yDiff);
    if (x < _x && y < _y) {
        if (xAbs > yAbs)
            move(-1, 0);
        else
            move(0, -1);
    } else if (x > _x && y < _y) {
        if (xAbs > yAbs)
            move(1, 0);
        else
            move(0, -1);
    } else if (x < _x && y > _y) {
        if (xAbs > yAbs)
            move(-1, 0);
        else
            move(0, 1);
    } else if (x > _x && y > _y) {
        if (xAbs > yAbs)
            move(1, 0);
        else
            move(0, 1);
    } else if (x < _x)
        move(-1, 0);
    else if (x > _x)
        move(1, 0);
    else if (y < _y)
        move(0, -1);
    else if (y > _y)
        move(0, 1);
}

void Projectile::directionalMove()
{
    if (_oldX == 0 && _oldY == 0) {
        _oldX = _x;
        _oldY = _y;
    }
    if (_oldX < _x && _oldY < _y) {
        move(1, 1);
    } else if (_oldX > _x && _oldY < _y) {
        move(-1, 1);
    } else if (_oldX < _x && _oldY > _y) {
        move(1, -1);
    } else if (_oldX > _x && _oldY > _y) {
        move(-1, -1);
    } else if (_oldX < _x) {
        move(1, 0);
    } else if (_oldX > _x) {
        move(-1, 0);
    } else if (_oldY < _y) {
        move(0, 1);
    } else if (_oldY > _y) {
        move(0, -1);
    }
}

void Projectile::update() {
    switch (_direction) {
        case UP:
            move(0, -1);
            break;
        case DOWN:
            move(0, 1);
            break;
        case LEFT:
            move(-1, 0);
            break;
        case RIGHT:
            move(1, 0);
            break;
        case UP_LEFT:
            move(-1, -1);
            break;
        case UP_RIGHT:
            move(1, -1);
            break;
        case DOWN_LEFT:
            move(-1, 1);
            break;
        case DOWN_RIGHT:
            move(1, 1);
            break;
        case DIRECTIONAL:
            directionalMove();
            break;
        case TRACKING:
            trackPlayer();
            break;
        default:
            break;
    }
}

void Projectile::hurtEntity(IEntity& self, IEntity& you) {
    if (self.isDead() || you.isDead())
        return;
    you.takeDamage(self.getDamage());
    self.takeDamage(100);
    if (you.isDead()) {
        auto pos = you.getPosition();
        RType::instance->createExplosion(std::get<0>(pos), std::get<1>(pos));
    }
}
