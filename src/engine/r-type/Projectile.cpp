/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Projectile
*/

#include "Projectile.hpp"

Projectile::Projectile(EntityInfo info) : AEntity(info)
{
    _damage = info.damage;
    _speed = info.speed;
    _direction = info.direction;
    _life = 1;
}

Projectile::~Projectile()
{
}

void Projectile::move(float x, float y)
{
    if ((_x + x * _speed) > Engine::instance->getWindowWidth() - _radius || (_x + x * _speed) < 0 + _radius || (_y + y * _speed) > Engine::instance->getWindowHeight() - (_radius / 2) || (_y + y * _speed) < 0 + (_radius / 2))
    {
        _isDead = true;
        return;
    }
    setOldPosition(_x, _y);
    _x += x * _speed;
    _y += y * _speed;
}

void Projectile::update()
{
    switch (_direction)
    {
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
    default:
        break;
    }
}

void Projectile::hurtEntity(IEntity &self, IEntity &you)
{
    if (self.isDead() || you.isDead())
        return;
    you.takeDamage(self.getDamage());
    self.takeDamage(100);
    if (you.isDead())
    {
        auto pos = you.getPosition();
        Game::instance->createExplosion(std::get<0>(pos), std::get<1>(pos));
    }
}
