/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Enemy
*/

#include "Enemy.hpp"

Enemy::Enemy(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY, int life, float speed, int damage, int fireRate)
    : Character(path, x, y, id, angle, scaleX, scaleY, speed)
{
    _life = life;
    _damage = damage;
    _fireRate = fireRate;
}

Enemy::~Enemy()
{
}

void Enemy::setLife(int life)
{
    _life = life;
}

int Enemy::getLife() const
{
    return _life;
}

void Enemy::setDamage(int damage)
{
    _damage = damage;
}

int Enemy::getDamage() const
{
    return _damage;
}

void Enemy::setFireRate(int fireRate)
{
    _fireRate = fireRate;
}

int Enemy::getFireRate() const
{
    return _fireRate;
}
